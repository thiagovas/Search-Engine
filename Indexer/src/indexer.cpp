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
}


void Indexer::GenerateTriples(vector<string> &vFilenames)
{
  this->frequency.clear();
  this->OpenTriplesFile();
  
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
          AddTriples(page, url, docid);
        
        getline(ifs, url);
        getline(ifs, delimiter);
        page.clear();
        docid++;
      }
      else page.append(s);
    }
    
    if(page != "")
      AddTriples(page, url, docid);
    
    ifs.close();
  }
  this->CloseTriplesFile();
}

void Indexer::SortTriples()
{
  ExternalSorter es;
  es.Sort(this->triplesFilename);
}

void Indexer::AddTriples(string &html, string &url, int docid)
{
  Parser parser;
  vector<string> terms = parser.GetWords(html);
  
  for(string s : terms)
  {
    int neueid = Vocabulary::AddWord(s);
    this->frequency[neueid]++;
  }
  ostream osUrl(&this->urlFile);
  osUrl << docid << " " << url << endl;
  
  ostream os(&this->fb);
  for(pair<int, int> it : this->frequency)
  {
    this->WriteTriple(os, it.first, docid, it.second);
  }
  this->frequency.clear();
}

void Indexer::WriteTriple(ostream &os, int termid, int docid, int frequency)
{
  os << termid << " " << docid << " " << frequency << endl;
}

void Indexer::OpenTriplesFile()
{
  this->urlFile.open("./.tmp/urls", std::ios::out);
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

