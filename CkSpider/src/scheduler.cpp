#include "scheduler.hpp"
using namespace std;


priority_queue<string, vector<string>, QueueComparison> Scheduler::pq_urls;
set<string> Scheduler::visited;

Scheduler::Scheduler()
{}

// Adds a new well-formed url to the scheduler
void Scheduler::AddURL(string url)
{
  // Here, I'm just adding url's that has a .br
  if(Utils::Exists(Utils::GetDomain(url), ".br"))
  {
    if(Scheduler::visited.find(url) == Scheduler::visited.end())
    {
      Scheduler::visited.insert(url);
      pq_urls.push(url);
    }
  }
}

// It returns the next url available on the scheduler
// If there is none, it returns an empty string
string Scheduler::GetNext()
{
  if(pq_urls.empty()) return "";
  return pq_urls.top();
}

// This method removes the url from the top of the scheduler
// If there is no url, nothing happens
void Scheduler::RemoveTop()
{
  if(!pq_urls.empty())
    pq_urls.pop();
}

// It returns if the scheduler has no more urls
bool Scheduler::IsEmpty()
{
  return pq_urls.empty();
}

