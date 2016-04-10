#ifndef _crawler_hpp
#define _crawler_hpp

#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <locale>
#include <cstring>
#include <sstream>
#include <csignal>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "CkSpider.h"
#include "CkString.h"
#include "scheduler.hpp"
#include "utils.hpp"
#include "dumper.hpp"

class Crawler
{
  public:
    
    Crawler();
    
    // Starts to crawl
    void Start(std::string pseedFilename, int pnThreads);
    
    // It sets the name of the folder that will keep the pages crawled
    void SetOutputFolder(std::string pfolderName);
    
    void Stop();
    
    
  private:
    
    // Name of the folder that will keep the pages crawled
    static std::string folderName;
    
    static std::mutex scheduler_mutex;
    
    static bool stopping;

    static int crawlCount;
    
    static std::map<std::string, long long int> weights;
    
    // Integer used as a url weight for the scheduler
    int urlWeight;

    std::string seedFilename;
    
    // Number of threads the crawler will create in order to collect the pages
    int nThreads;
    
    // Loads
    void LoadScheduler();
    
    // Function executed by each thread
    void Crawl();

    void Log();
};


#endif
