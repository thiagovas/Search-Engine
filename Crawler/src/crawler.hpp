#ifndef _crawler_hpp
#define _crawler_hpp

#include <string>
#include <csignal>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <curl/curl.h>
#include "scheduler.hpp"

class Crawler
{
  public:
    
    Crawler();
    
    // Starts to crawl
    void Start(std::string pseedFilename, int pnThreads, int pnFiles);
    
    // It sets the name of the folder that will keep the pages crawled
    void SetOutputFolder(std::string pfolderName);
    
    void Stop();
    
    static size_t WriteOnString(void *content, size_t size, size_t nmembytes, void *userp);

  private:
    
    // Name of the folder that will keep the pages crawled
    std::string folderName;
    
    std::string seedFilename;
    
    // Number of threads the crawler will create in order to collect the pages
    int nThreads;
    
    int nFiles;
    
    Scheduler _scheduler;
    
    // Loads
    void LoadScheduler();
};


#endif
