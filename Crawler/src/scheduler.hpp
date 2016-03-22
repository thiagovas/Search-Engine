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
    
    Scheduler(std::string seeds_filename);
    
    // This function loads the scheduler with the urls present on the [seeds_filename] file
    void loadScheduler(std::string seeds_filename);
    
    // Adds a new well-formed url to the scheduler
    void addURL(std::string url);
    
    // It returns the next url available on the scheduler
    // If there is none, it returns an empty string
    std::string getNext();
    
    // This method removes the url from the top of the scheduler
    // If there is no url, nothing happens
    void removeTop();
    
    // It returns if the scheduler has no more urls
    bool isEmpty();
    
  private:

    std::priority_queue<std::string> pq_urls;
    
    // This function returns the number of components the url has.
    int countComponents(std::string url);
};

#endif
