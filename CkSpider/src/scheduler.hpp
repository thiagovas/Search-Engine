#ifndef _scheduler_hpp
#define _scheduler_hpp

#include <set>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "utils.hpp"

class QueueComparison {
  public:
    QueueComparison(){}
    bool operator()(const std::string& lhs, const std::string& rhs)
    {
      return Utils::CountComponents(lhs) < Utils::CountComponents(rhs);
    }
};

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
    
    static std::set<std::string> visited;
    static std::priority_queue<std::string, std::vector<std::string>, QueueComparison > pq_urls;
};

#endif
