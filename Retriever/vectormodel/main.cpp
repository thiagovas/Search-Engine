#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "../base/document.hpp"
#include "retriever.hpp"
using namespace std;

void run(bool verbose)
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
  
  if(verbose) cout << "Query: ";
  // Reading query...
  getline(std::cin, query);
  
  vector<base::Document> result = robj.Retrieve(query);
  for(base::Document d : result)
  {
    cout << d.GetDocId() << ": " << d.GetUrl() << endl;
  }
}

int main(int argc, char *argv[])
{
  bool verbose=true;
  if(argc == 3)
  {
    if(strcmp(argv[1], "-o") != 0) goto invalid_arguments;
    
    verbose=false;
    if(freopen(argv[2], "w", stdout) == NULL)
    {
      cout << "Error opening the output file!\n";
      return 1;
    }
  }
  else if(argc != 1)
  {
    goto invalid_arguments;
  }

  run(verbose);
  
  return 0;
  
invalid_arguments:
  cout << "Invalid Arguments.\n";
  cout << "Usage: ./" << argv[0] << " [OPTIONS]\n\n";
  cout << "Options:\n\t -o [Output filename]\n\n";
  return 1;
}
