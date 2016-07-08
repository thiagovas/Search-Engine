#include <iostream>
#include <vector>
#include <fstream>
#include "../base/document.hpp"
#include "retriever.hpp"
using namespace std;

int main()
{
  string query, index, urls, vocabulary;
  
  filebuf fb;
  fb.open("CONFIG", std::ios::in);
  istream is(&fb);
  
  getline(is, index);
  getline(is, urls);
  getline(is, vocabulary);
  
  fb.close();
  
  retriever::vectormodel::Retriever robj(index, urls, vocabulary);
  
  
  cout << "Query: ";
  // Reading query...
  getline(std::cin, query);
  
  vector<base::Document> result = robj.Retrieve(query);
  for(base::Document d : result)
  {
    cout << d.GetDocId() << ": " << d.GetUrl() << endl;
  }
  
  return 0;
}
