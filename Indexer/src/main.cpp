#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include "indexer.hpp"
using namespace std;

int main()
{
  // The name of the files with the html source code of the crawled pages.
  filebuf fb;
  fb.open("DOCFILENAMES", std::ios::in);
  istream is(&fb);
  
  string newFilename;
  vector<string> vFilenames;
  Indexer indexerobj;
  
  while(true)
  {
    getline(is, newFilename);
    if(not is) break;
    vFilenames.push_back(newFilename);
  }
  fb.close();

  cout << "Indexing pages...\n";
  indexerobj.Index(vFilenames);
  cout << "Finished indexing.\n";

  return 0;
}
