#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include "indexer.hpp"
using namespace std;

int main()
{
  // The name of the files with the html source code of the crawled pages.
  vector<string> vFilenames;
  Indexer indexerobj;
  
  vFilenames.push_back("./documents/tst_pages_1");
  
  cout << "Indexing pages...\n";
  indexerobj.Index(vFilenames);
  cout << "Finished indexing.\n";
  return 0;
}
