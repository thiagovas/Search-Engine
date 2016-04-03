#include <iostream>
#include <csignal>
#include "crawler.hpp"
using namespace std;

Crawler _crawler;

void stop(int signum)
{
  _crawler.Stop();
}

int main()
{
  _crawler.SetOutputFolder("./documents/");
  signal(SIGINT, stop);
   
  cout << "\nTo Stop, press Ctrl-C\nStarting the crawler...\n";
  // 20 threads and 50 different files to keep the pages crawled
  _crawler.Start("seeds", 20, 50);
    
  return 0;
}
