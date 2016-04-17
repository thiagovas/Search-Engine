#include "scheduler.hpp"
using namespace std;


string Scheduler::dumpFilename;
set<long long int> Scheduler::visited;
BinaryHeap Scheduler::pq_urls;
vector<pair<string, int> > Scheduler::pq_bkp;
list<string> Scheduler::vDomains, Scheduler::forbidden;
int Scheduler::weights[256];


Scheduler::Scheduler()
{
  Scheduler::Initialize("tmpScheduler");
}

void Scheduler::Initialize(string filename)
{
  Scheduler::vDomains.push_back(".br");
  Scheduler::vDomains.push_back("mulher");
  Scheduler::vDomains.push_back("uol");
  Scheduler::vDomains.push_back("globo");
  Scheduler::vDomains.push_back("vida");
  
  Scheduler::forbidden.push_back("xvideos");
  Scheduler::forbidden.push_back("porno");
  Scheduler::forbidden.push_back("redtube");
  Scheduler::forbidden.push_back("xxx");
  
  Scheduler::SetDumpFilename(filename);
  
  memset(Scheduler::weights, 0, sizeof(Scheduler::weights));
  
  Scheduler::pq_urls.Initialize(Scheduler::max_size);
}

void Scheduler::SetDumpFilename(string filename)
{
  Scheduler::dumpFilename = filename;
}

long long int Scheduler::VisitedHash(string &url)
{
  long long int hash=0;
  for(unsigned i = 0; i < url.size(); i++)
    if(isalpha(url[i]))
      hash ^= ((url[i]-'A')<<(i%('z'-'A'+2)));
  return hash;
}

// Adds a new well-formed url to the scheduler
bool Scheduler::AddURL(string &url)
{
  if(url.size() > 200) return false;
  
  // Making sure the url doesn't have any of the forbidden keywords
  for(list<string>::iterator it = Scheduler::forbidden.begin(); it != Scheduler::forbidden.end(); it++)
    if(url.find(*it) != string::npos) return false;
  
  // Here, I'm making sure the scheduler just adds urls that has a .br
  // or any keyword present at vDomains
  bool add=false;
  string domain = Utils::GetDomain(url);
  for(list<string>::iterator it = Scheduler::vDomains.begin(); it != Scheduler::vDomains.end(); it++)
  {
    // Ignoring dynamic urls
    if(Utils::FindAny(url, "{}@")) return false;
    if(domain.find(*it) != string::npos)
    {
      add=true;
      break;
    }
  }
  
  if(add)
  {
    long long int vhash=Scheduler::VisitedHash(url);
    if(Scheduler::visited.find(vhash) == Scheduler::visited.end())
    {
      Scheduler::ForceAddURL(url);
      return true;
    }
  }
  return false;
}

// Adds the url to the scheduler without making any verification
void Scheduler::ForceAddURL(string &url)
{
  if(url.size() < 3) return;
  
  url.shrink_to_fit();
  if(Scheduler::pq_urls.Size() > Scheduler::max_size)
    return;
  
  long long int vhash = Scheduler::VisitedHash(url);
  string domain = Utils::GetDomain(url);
  unsigned char hash = Utils::GetURLHash(domain);
  int newWeight = ++Scheduler::weights[hash];
  Scheduler::visited.insert(vhash);
  newWeight = 100*newWeight + Utils::CountComponents(url);
  Scheduler::pq_urls.Push(make_pair(url, newWeight));
}

void Scheduler::PreProcessBackup()
{
  Scheduler::pq_bkp = Scheduler::pq_urls.GetElements();
}

void Scheduler::Backup(string filename)
{
  filebuf fb;
  if(fb.open(filename, ios::out))
  {
    ostream os(&fb);
    os.sync_with_stdio(false);
    
    for(unsigned i = 0; i < pq_bkp.size(); i++)
      os << pq_bkp[i].first << "\n";
    pq_bkp.clear();
    os.flush();
    fb.close();
  }
}

// It returns the next url available on the scheduler
// If there is none, it returns an empty string
string Scheduler::GetNext()
{
  if(Scheduler::pq_urls.Empty()) return "";
  return Scheduler::pq_urls.Top().first;
}

// This method removes the url from the top of the scheduler
// If there is no url, nothing happens
void Scheduler::RemoveTop()
{
  if(!Scheduler::pq_urls.Empty())
    Scheduler::pq_urls.Pop();
}

// It returns if the scheduler has no more urls
bool Scheduler::IsEmpty()
{
  return Scheduler::pq_urls.Empty();
}
