#ifndef _scheduler_hpp
#define _scheduler_hpp

#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "utils.hpp"

class Scheduler
{
  public:
    
    Scheduler();
    
    // Adds a new well-formed url to the scheduler
    static void AddURL(std::string url);
    
    // It returns the next url available on the scheduler
    // If there is none, it returns an empty string
    static std::string GetNext();
    
    // This method removes the url from the top of the scheduler
    // If there is no url, nothing happens
    static void RemoveTop();
    
    // It returns if the scheduler has no more urls
    static bool IsEmpty();
    
  private:
    
    static std::priority_queue<std::string> pq_urls;
};

#endif
