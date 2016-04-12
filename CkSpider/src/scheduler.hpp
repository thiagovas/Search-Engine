#ifndef _scheduler_hpp
#define _scheduler_hpp

#include <map>
#include <set>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>
#include "utils.hpp"

typedef long long int ll;

class QueueComparison {
  public:
    QueueComparison(){}
    bool operator()(const std::pair<std::string, ll>& lhs, const std::pair<std::string, ll>& rhs)
    {
      return lhs.second > rhs.second;
    }
};

class Scheduler
{
  public:
    
    Scheduler();
    
    // Adds a new well-formed url to the scheduler
    static bool AddURL(std::string url);
    
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
    static void ForceAddURL(std::string url);
    
  private:
    
    static std::queue<std::string> dumpUrls;
    static std::string dumpFilename;
    static std::set<std::string> visited;
    static std::priority_queue<std::pair<std::string, ll>, std::vector<std::pair<std::string, ll> >, QueueComparison > pq_urls;
    static std::priority_queue<std::pair<std::string, ll>, std::vector<std::pair<std::string, ll> >, QueueComparison > pq_bkp;
    static std::vector<std::string> vDomains;
    static std::filebuf fbInDump;
    static std::filebuf fbOutDump;
    
    // A map that keeps how many links the crawler collected for each domain
    // It's used as a weight at the scheduler
    static std::map<short, long long int> weights;

    static void AddDump(std::string &url);
    
    static void DumpUrls();    
};

#endif
