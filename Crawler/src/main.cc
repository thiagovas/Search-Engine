#include <iostream>
#include "crawler.hpp"
using namespace std;

int main()
{
  Crawler _crawler;
  
  _crawler.SetOutputFolder("./documents/");
  
  // 20 threads and 50 different files to keep the pages crawled
  _crawler.Start("seeds", 20, 50);
  
  return 0;
}
