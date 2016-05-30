#include "externalsorter.hpp"
using namespace std;


ExternalSorter::ExternalSorter()
{
  this->triplesFilename = ".tmp/triples.txt";
  this->numberChunks = 0;

  // Setting memory limit to 128Mb.
  this->SetMemoryLimit(128000000);
}

// Sets a new memory limit.
// Memory Limit represented in bytes.
void ExternalSorter::SetMemoryLimit(int newLimit)
{
  this->memoryLimit = newLimit;
  
  // The maximum number of triples allowed to be represented on primary memory
  // depends on the size of the size of a Triple object plus the size of the
  // pointer to it.
  this->maxTriples = newLimit/(sizeof(Triple)+4);
}

// Function that sorts [filename] using a multiway sorting algorithm.
void ExternalSorter::Sort(string filename)
{
  this->triplesFilename = filename;
  this->GenerateSortedChunks();
  
  int termid, docid, frequency;
  vector<filebuf*> vfb;
  vector<istream*> vins;
  filebuf sortedTriples;
  
  sortedTriples.open("./.tmp/sortedTriples", std::ios::out);
  ostream out(&sortedTriples);
  
  priority_queue<pair<Triple, int> > pq;
  for(int i = 0; i < this->numberChunks; i++)
  {
    filebuf *fb = new filebuf();
    stringstream ss;
    ss << "./.tmp/chunk";
    ss << i;
    fb->open(ss.str(), std::ios::in);
    
    istream *ins = new istream(fb);
    (*ins) >> termid >> docid >> frequency;
    
    if(not (*ins)) fb->close();
    else
    {
      vfb.push_back(fb);
      vins.push_back(ins);
      pq.push(make_pair(Triple(termid, docid, frequency), i));
    }
  }
  vfb.shrink_to_fit();
  vins.shrink_to_fit();
  
  while(not pq.empty())
  {
    pair<Triple, int> current = pq.top();
    pq.pop();
    int termid = current.first.GetTermId();
    int docid = current.first.GetDocId();
    int frequency = current.first.GetFrequency();
    out << termid << " " << docid << " " << frequency << endl;
    
    (*vins[current.second]) >> termid >> docid >> frequency;
    if(not (*vins[current.second]))
    {
      // There is anything else to read on this file...
      vfb[current.second]->close();
    }
    else
    {
      pq.push(make_pair(Triple(termid, docid, frequency), current.second));
    }
  }
  sortedTriples.close();
}

void ExternalSorter::GenerateSortedChunks()
{
  int termid, docid, frequency;
  priority_queue<Triple> pq;
  
  filebuf fb;
  fb.open(this->triplesFilename, std::ios::in);
  istream is(&fb);
  
  this->numberChunks=0;
  while(true)
  {
    is >> termid >> docid >> frequency;
    if(not is) break;
    
    pq.push(Triple(termid, docid, frequency));
    if((int)pq.size() == this->maxTriples)
      this->DumpChunk(pq);
  }
  fb.close();
  this->DumpChunk(pq);
}

// Method to dump the priority queue in the next chunk file.
// This method is called whenever the priority queue gets full.
void ExternalSorter::DumpChunk(priority_queue<Triple> &pq)
{
  if(pq.size()==0) return;
  
  filebuf fb;
  stringstream name;
  name << "./.tmp/chunk";
  name << this->numberChunks++;
  fb.open(name.str(), std::ios::out);
  
  ostream os(&fb);
  
  while(not pq.empty())
  {
    Triple current = pq.top();
    pq.pop();
    os << current.GetTermId() << " " << current.GetDocId();
    os << " " << current.GetFrequency() << endl;
  }
  fb.close();
}
