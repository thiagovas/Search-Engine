#ifndef _scheduler_hpp
#define _scheduler_hpp

#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include "utils.hpp"
#include "binaryheap.hpp"

typedef long long int ll;

class Scheduler
{
  public:
    
    Scheduler();
    
    // Adds a new well-formed url to the scheduler
    static bool AddURL(std::string &url);
    
    // It returns the next url available on the scheduler
    // If there is none, it returns an empty string
    static std::string GetNext();
    
    // This method removes the url from the top of the scheduler
    // If there is no url, nothing happens
    static void RemoveTop();
    
    // It returns if the scheduler has no more urls
    static bool IsEmpty();
    
    // Function that copies the urls to another data structure used to 
    // save the urls at a file
    static void PreProcessBackup();
    
    // Initialize the scheduler
    static void Initialize(std::string filename);

    // This function saves the urls at the [filename] file
    static void Backup(std::string filename);
    
    // This method sets the name of the file used as a temporary file
    // to keep urls to be crawled.
    static void SetDumpFilename(std::string filename);
    
    // This function loads some urls from the temporary file of urls
    static bool LoadFromDump();
    
    // Adds the url to the scheduler without making any verification
    static void ForceAddURL(std::string &url);
    
  private:
    
    static const int max_size=5000;
    static int dumpCount;
    static std::string dumpFilename;
    static std::set<long long int> visited;
    static BinaryHeap pq_urls;
    static std::vector<std::pair<std::string, int> > pq_bkp;
    static std::list<std::string> vDomains;
    static std::filebuf fbInDump;
    static std::filebuf fbOutDump;
    static std::ostream *dumpos;

    static std::list<std::string> forbidden;
    
    // A map that keeps how many links the crawler collected for each domain
    // It's used as a weight at the scheduler
    static int weights[256];
    
    static void DumpUrl(std::string &url);
    
    static long long int VisitedHash(std::string &url);
};

#endif
