#include "scheduler.hpp"
using namespace std;


queue<string> Scheduler::dumpUrls;
string Scheduler::dumpFilename;
set<long long int> Scheduler::visited;
priority_queue<pair<string, ll>, vector<pair<string, ll> >, QueueComparison > Scheduler::pq_urls;
priority_queue<pair<string, ll>, vector<pair<string, ll> >, QueueComparison > Scheduler::pq_bkp;
vector<string> Scheduler::vDomains, Scheduler::forbidden;
filebuf Scheduler::fbInDump;
filebuf Scheduler::fbOutDump;
map<short, long long int> Scheduler::weights;



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
  Scheduler::fbOutDump.open(Scheduler::dumpFilename, ios::out);
  Scheduler::fbInDump.open(Scheduler::dumpFilename, ios::in);
}

void Scheduler::SetDumpFilename(string filename)
{
  Scheduler::dumpFilename = filename;
}

void Scheduler::AddDump(string &url)
{
  Scheduler::dumpUrls.push(url);
  if(Scheduler::dumpUrls.size() > 2000)
    Scheduler::DumpUrls();
}

void Scheduler::DumpUrls()
{
  ostream os(&Scheduler::fbOutDump);
  while(not Scheduler::dumpUrls.empty())
  {
    os << Scheduler::dumpUrls.front() << endl;
    Scheduler::dumpUrls.pop();
  }
  os.flush();
}

long long int Scheduler::VisitedHash(string url)
{
  long long int hash=0;
  for(int i = 0; i < (int)url.size(); i++)
    if(isalpha(url[i]))
      hash ^= ((url[i]-'A')<<(i%('z'-'A'+2)));
  return hash;
}

bool Scheduler::LoadFromDump()
{
  istream is(&Scheduler::fbInDump);
  string url;
  bool added=false;
  while(Scheduler::pq_urls.size() < 1000)
  {
    getline(is, url);
    if(not is)
    {
      Scheduler::fbOutDump.close();
      Scheduler::fbInDump.close();
      Scheduler::fbOutDump.open(Scheduler::dumpFilename, ios::out);
      Scheduler::fbInDump.open(Scheduler::dumpFilename, ios::in);
      break;
    }
    added=true;
    Scheduler::AddURL(url);
  }
  return added || (Scheduler::pq_urls.size() > 0);
}

// Adds a new well-formed url to the scheduler
bool Scheduler::AddURL(string url)
{
  if(url.size() > 200) return false;
  
  // Making sure the url doesn't have any of the forbidden keywords
  for(unsigned i = 0; i < Scheduler::forbidden.size(); i++)
    if(url.find(Scheduler::forbidden[i]) != string::npos) return false;
  
  // Here, I'm making sure the scheduler just adds urls that has a .br
  // or any keyword present at vDomains
  bool add=false;
  string domain = Utils::GetDomain(url);
  for(unsigned i = 0; i < Scheduler::vDomains.size(); i++)
  {
    // Ignoring dynamic urls
    if(Utils::FindAny(url, "{}@")) return false;
    if(domain.find(Scheduler::vDomains[i]) != string::npos)
    {
      add=true;
      break;
    }
  }
  
  if(add)
  {
    long long int hash=Scheduler::VisitedHash(url);
    if(Scheduler::visited.find(hash) == Scheduler::visited.end())
    {
      Scheduler::ForceAddURL(url);
      return true;
    }
  }
  return false;
}

// Adds the url to the scheduler without making any verification
void Scheduler::ForceAddURL(string url)
{
  if(url.size() < 3) return;
  if(Scheduler::pq_urls.size() > 10000)
  {
    Scheduler::AddDump(url);
  }
  else
  {
    long long int vhash = Scheduler::VisitedHash(url);
    short hash = Utils::GetURLHash(Utils::GetDomain(url));
    long long int newWeight = ++Scheduler::weights[hash];
    Scheduler::visited.insert(vhash);
    newWeight = 100000000ll*newWeight + Utils::CountComponents(url);
    Scheduler::pq_urls.push(make_pair(url, newWeight));
  }
}

void Scheduler::PreProcessBackup()
{
  Scheduler::pq_bkp = Scheduler::pq_urls;
}

void Scheduler::Backup(string filename)
{
  filebuf fb;
  if(fb.open(filename, ios::out))
  {
    ostream os(&fb);
    while(not Scheduler::pq_bkp.empty())
    {
      os << Scheduler::pq_bkp.top().first << endl;
      Scheduler::pq_bkp.pop();
    }
    fb.close();
  }
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
