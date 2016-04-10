#ifndef _scheduler_hpp
#define _scheduler_hpp

#include <set>
#include <queue>
#include <string>
#include <vector>
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
    static bool AddURL(std::string url, ll weight);
    
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
    static std::priority_queue<std::pair<std::string, ll>, std::vector<std::pair<std::string, ll> >, QueueComparison > pq_urls;
};

#endif
