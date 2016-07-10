#include <list>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "retriever.hpp"
#include "../base/util.hpp"
using namespace std;


namespace retriever
{
namespace vectormodel
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
  // TODO:
  // 
  // Implement the Retrieve function using:
  // 1) Cosine function --> DONE
  // 2) PageRank
  // 3) Anchor Text
  // 
  
  vector<base::Document> vDocuments = this->GetTopKCosine(query, 20);
  return vDocuments;
}

void Retriever::LoadVocabulary(string filename)
{
  FILE *pfile = fopen(filename.c_str(), "r");
  char term[2048];
  int termid;
  
  while(fscanf(pfile, "%s %d", term, &termid) != EOF)
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


vector<base::Document> Retriever::GetTopKCosine(string &query, unsigned k)
{
  base::Util util;
  vector<string> queryElements = util.SplitStr(query, " ");
  map<int, int> queryvec;
  map<int, long long int> documentsz;
  map<int, long long int> documentweight;
  long long int queryvecsz=0;
  string line;
  int index, docid, frequency;

  
  for(const string &elem : queryElements)
  {
    if(this->vocabulary.find(elem) != this->vocabulary.end())
      queryvec[this->vocabulary[elem]]++;
  }
  
  for(const pair<int, int> &value : queryvec)
  {
    queryvecsz += value.second*value.second;
  }
  
  
  filebuf fb;
  fb.open(this->indexFilename, std::ios::in);
  istream is(&fb);
  
  while(true)
  {
    is >> index;
    if(not is) break;
    
    // Ignoring lines of terms that are not present on the query.
    if(queryvec.find(index) == queryvec.end())
    {
      is.ignore(200000, '\n');
    }
    else
    {
      std::getline(is, line);
      std::istringstream iss(line);
      while(iss >> docid >> frequency)
      {
        documentweight[docid] += frequency*queryvec[index];
        documentsz[docid] += frequency*frequency;
      }
    }
  }
  fb.close();
  
  vector<pair<long double, int> > result;
  for(const pair<int, long long int> &value : documentsz)
  {
    long double docValue = documentweight[value.first];
    long long int docsz = value.second;
    string url = this->murls[value.first];
    for(const string &elem : queryElements)
    {
      if(url.find(elem) != std::string::npos)
      {
        docsz++;
        docValue += 1;
      }
    }
    
    result.push_back(make_pair((docValue*docValue)/(queryvecsz*docsz), value.first));
  }
  sort(result.begin(), result.end());
  reverse(result.begin(), result.end());
  
  if(result.size() > k)
    result.erase(result.begin()+k, result.end());

  std::vector<base::Document> vDoc;
  for(unsigned i = 0; i < result.size(); i++)
    vDoc.push_back(base::Document(result[i].second,
                                  this->murls[result[i].second]));
  return vDoc;
}


} // namespace vectormodel
} // namespace retriever
