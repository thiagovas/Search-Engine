#include <iostream>
#include "externalsorter.hpp"
using namespace std;

int main()
{
  int memoryLimit;
  
  string filename;
  ExternalSorter es;
  
  cin >> memoryLimit;
  cin >> filename;
  
  es.SetMemoryLimit(100000);
  es.Sort(filename);
  
  return 0;
}
