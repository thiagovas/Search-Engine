#include "indexer.hpp"
using namespace std;

Indexer::Indexer()
{
  this->triplesFilename = ".tmp/triples.txt";
}

void Indexer::Index(vector<string> &vFilenames)
{
  // 1) Read the crawled pages.
  // 2) Foreach document read, send to the parser the string of the
  //    document with its id.
  // 3) Save the parser's result in a file.
  // 4) Sort the file.
  // 5) Create the index using the sorted file.
  // 6) Save the vocabulary with the ids in a file.
  
  // Each line of the index file will represent a term of the vocabulary.
  // A line will have a set of pairs
  // <DocumentID, Term Frequency of the document>
  
  
  this->GenerateTriples(vFilenames);
  this->SortTriples();
  Vocabulary::Dump();
  
  this->WriteFinalIndexFile();
}

// Function that reads the sorted triples file and write the index.
void Indexer::WriteFinalIndexFile() const
{
  int termid, docid, frequency;
  filebuf sortedFile, indexFile;
  sortedFile.open("./.tmp/sortedTriples", std::ios::in);
  indexFile.open("output/index", std::ios::out);
  
  
  istream is(&sortedFile);
  ostream os(&indexFile);
  
  int lastTermId=-1;
  while(true)
  {
    is >> termid >> docid >> frequency;
    if(not is) break;

    if(lastTermId == -1)
    {
      lastTermId = termid;
      os << termid;
    }
    
    if(lastTermId != termid) os << endl << termid;
    os << " " << docid << " " << frequency;
    lastTermId = termid;
  }
  os << endl;
  
  sortedFile.close();
  indexFile.close();
}


void Indexer::GenerateTriples(vector<string> &vFilenames)
{
  this->OpenTriplesFile();
  this->maxWriteThreads = 0;
  std::thread *t1 = NULL, *t2 = NULL;
  
  // docid keep the id of the current document being indexed.
  int docid=1;
  for(vector<string>::iterator it = vFilenames.begin();
                               it != vFilenames.end(); it++)
  {
    ifstream ifs (*it, std::ifstream::in);
    
    string page = "", url = "", delimiter = "";
    while(ifs.good())
    {
      string s;
      getline(ifs, s);
      
      if(s=="|||")
      {
        if(page != "")
        {
          this->AddTriples(&t1, &t2, page, url, docid);
          docid++;
        }
        
        getline(ifs, url);
        getline(ifs, delimiter);
        page.clear();
      }
      else page.append(s);
    }
    
    if(page != "")
      this->AddTriples(&t1, &t2, page, url, docid);
    
    ifs.close();
  }
  
  if(t1 != NULL)
  {
    t1->join();
    delete t1;
  }
  
  if(t2 != NULL)
  {
    t2->join();
    delete t2;
  }
  
  this->CloseTriplesFile();
}

void Indexer::SortTriples() const
{
  ExternalSorter es;
  es.Sort(this->triplesFilename);
}

void Indexer::AddTriples(thread **t1, thread **t2, string &html, string &url,
                         int docid)
{
  while(true)
  {
    this->mutexCheck.lock();
    if(this->maxWriteThreads == 3)
    {
      this->mutexCheck.unlock();
      
      // Sleep for 0.1 milisecond...
      usleep(100);
    }
    else if(this->maxWriteThreads == 1)
    {
      this->mutexCheck.unlock();
      if((*t2) != NULL)
      {
        (*t2)->join();
        delete (*t2);
      }
      (*t2) = new thread(&Indexer::AddTriplesThread, this, html, url, docid, 2);
      break;
    }
    else
    {
      this->mutexCheck.unlock();
      if((*t1) != NULL)
      {
        (*t1)->join();
        delete (*t1);
      }
      (*t1) = new thread(&Indexer::AddTriplesThread, this, html, url, docid, 1);
      break;
    }
  }
}

void Indexer::AddTriplesThread(string html, string url, int docid, int key)
{
  this->mutexCheck.lock();
  this->maxWriteThreads |= key;
  this->mutexCheck.unlock();
  
  Parser parser;
  vector<string> terms = parser.GetWords(html);
  
  // Map used to count the frequency of each term in a document.
  std::map<int, int> frequency;
  
  for(string s : terms)
  {
    if(s.size() > 127) continue;
    int neueid = Vocabulary::AddWord(s);
    frequency[neueid]++;
  }
  
  this->mutexWrite.lock();
  ostream osUrl(&this->urlFile);
  osUrl << docid << " " << url << endl;
        
  ostream os(&this->fb);
  for(pair<int, int> it : frequency)
  {
    this->WriteTriple(os, it.first, docid, it.second);
  }
  os.flush();
  this->mutexWrite.unlock();
  
  this->mutexCheck.lock();
  this->maxWriteThreads ^= key;
  this->mutexCheck.unlock();
}

inline void Indexer::WriteTriple(ostream &os, int termid, int docid,
                                 int frequency) const
{
  os << termid << " " << docid << " " << frequency << endl;
}

void Indexer::OpenTriplesFile()
{
  this->urlFile.open("output/urls", std::ios::out);
  this->fb.open(this->triplesFilename, std::ios::out);
}

void Indexer::CloseTriplesFile()
{
  this->fb.close();
  this->urlFile.close();
}

void Indexer::SetTriplesFilename(string pfilename)
{
  this->triplesFilename = pfilename;
}

