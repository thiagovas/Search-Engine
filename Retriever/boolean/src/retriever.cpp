#include "retriever.hpp"
#include <list>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../../base/util.hpp"
using namespace std;


namespace retriever
{
namespace boolean
{

Retriever::Retriever(string pIndexFilename, string urlsFilename,
                     string vocabularyFilename)
{
  this->LoadVocabulary(vocabularyFilename);
  this->LoadUrls(urlsFilename);
  this->indexFilename = pIndexFilename;
}

vector<base::Document> Retriever::Retrieve(string &query)
{
  // 1) Read the query.
  // 2) Get the ids of the words of the query from the vocabulary.
  // 3) Walk by the index
  // 3.1) At each line of the index, if the term is present at the query
  //      add the documents listed on the line on a
  //      dictionary <document id, number of query terms present>.
  // 
  
  
  // from document id to number of matches.
  map<int, int> result;
  base::Util util;
  vector<string> terms = util.SplitStr(query, " ");
  list<int> termids;
  string line;
  int index, docid, frequency;
  
  for(string t : terms)
  {
    if(vocabulary[t] != 0)
      termids.push_back(this->vocabulary[t]);
  }
  
  filebuf fb;
  fb.open(this->indexFilename, std::ios::in);
  istream is(&fb);
  
  while(true)
  {
    is >> index;
    if(not is) break;
    bool found=false;
    for(list<int>::iterator it = termids.begin(); it != termids.end(); it++)
    {
      if(*it==index)
      {
        found=true;
        break;
      }
    }
    
    if(not found)
    {
      is.ignore(200000, '\n');
    }
    else
    {
      std::getline(is, line);
      std::istringstream iss(line);
      while(iss >> docid >> frequency)
      {
        result[docid]++;
      }
    }
  }
  fb.close();
  
  vector<pair<int, int> > sortedDoc;
  for(pair<int, int> p : result)
  {
    // Adding frequency and document id, in that order, to sort by frequency.
    sortedDoc.push_back(make_pair(p.second, p.first));
  }
  sort(sortedDoc.begin(), sortedDoc.end());
  reverse(sortedDoc.begin(), sortedDoc.end());
  
  vector<base::Document> vdoc;
  for(pair<int, int> p : sortedDoc)
  {
    vdoc.push_back(base::Document(p.second, this->murls[p.second]));
  }
  return vdoc;
}

void Retriever::LoadVocabulary(string filename)
{
  FILE *pfile = fopen(filename.c_str(), "r");
  char term[2048];
  int termid;
  
  while(fscanf(pfile, "%d: %s", &termid, term) != EOF)
  {
    string neueTerm(term);
    this->vocabulary[neueTerm] = termid;
  }
  fclose(pfile);
}


void Retriever::LoadUrls(std::string filename)
{
  int docid;
  string url;
  filebuf fb;
  fb.open(filename, std::ios::in);
  istream is(&fb);
  
  while(true)
  {
    is >> docid;
    getline(is, url);
    if(not is) break;
    this->murls[docid] = url;
  }
  fb.close();
}

} // namespace Boolean
} // namespace retriever
