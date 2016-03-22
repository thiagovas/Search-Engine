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
    void AddURL(std::string url);
    
    // It returns the next url available on the scheduler
    // If there is none, it returns an empty string
    std::string GetNext();
    
    // This method removes the url from the top of the scheduler
    // If there is no url, nothing happens
    void RemoveTop();
    
    // It returns if the scheduler has no more urls
    bool IsEmpty();
    
  private:

    std::priority_queue<std::string> pq_urls;
    
    // This function returns the number of components the url has.
    int CountComponents(std::string url);
};

#endif
