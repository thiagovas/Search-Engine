#include "scheduler.hpp"
using namespace std;


priority_queue<string> Scheduler::pq_urls;


Scheduler::Scheduler()
{}

// Adds a new well-formed url to the scheduler
void Scheduler::AddURL(string url)
{
  pq_urls.push(url);
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

// This function returns the number of components the url has.
int Scheduler::CountComponents(string url)
{
  int c=1;
  unsigned i, j=0;
  const string http = "https";
  
  // Ignoring the http in front of the url
  // If the url doesnt start with http:// it does nothing
  for(i=0; i < url.size() && j < http.size(); i++)
  {
    if(url[i]==http[j]) j++;
    else break;
  }
  if(j >= http.size()-1) i+=3;
  
  for(;i < url.size()-1; i++)
    if(url[i]=='.' || url[i]=='/') c++;
  
  return c;
}
