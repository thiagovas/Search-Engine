#include "scheduler.hpp"
using namespace std;


priority_queue<pair<string, ll>, vector<pair<string, ll> >, QueueComparison> Scheduler::pq_urls;
set<string> Scheduler::visited;

Scheduler::Scheduler()
{}

// Adds a new well-formed url to the scheduler
bool Scheduler::AddURL(string url, ll weight)
{
  // Here, I'm making sure the scheduler just adds urls that has a .br
  if(Utils::Exists(Utils::GetDomain(url), ".br"))
  {
    if(Scheduler::visited.find(url) == Scheduler::visited.end())
    {
      Scheduler::visited.insert(url);
      weight = 100000000ll*weight + Utils::CountComponents(url);
      pq_urls.push(make_pair(url, weight));
      return true;
    }
  }
  else return false;
  return true;
}

// It returns the next url available on the scheduler
// If there is none, it returns an empty string
string Scheduler::GetNext()
{
  if(pq_urls.empty()) return "";
  return pq_urls.top().first;
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

