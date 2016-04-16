#include "crawler.hpp"
using namespace std;

std::string Crawler::folderName = ".\\";
std::mutex Crawler::scheduler_mutex;
std::mutex Crawler::crawlCount_mutex;
bool Crawler::stopping = false;
int Crawler::crawlCount = 0;
int Crawler::collecting=0;

Crawler::Crawler()
{
  this->urlWeight=0;
  Crawler::crawlCount=0;
  Crawler::collecting=0;
}

void Crawler::Start(string pseedFilename, int pnThreads)
{
  Scheduler::Initialize(Crawler::folderName+"tmpScheduler");
  
  this->seedFilename = pseedFilename;
  this->nThreads = pnThreads;
  this->LoadScheduler();
  Crawler::stopping = false;
  
  
  list<thread> running;
  for(int i = 0; i < pnThreads; i++)
    running.push_back(thread(&Crawler::Crawl, this));
  
  for(list<thread>::iterator it = running.begin(); it != running.end(); it++)
    it->join();
  
  cout << "Stopped crawling\n";
}

void Crawler::Stop()
{
  cout << "\nStopping...\n";
  Crawler::stopping = true;
  this->Log();
  this->ForceBackupScheduler();
}

void Crawler::SetOutputFolder(string pfolderName)
{
  Crawler::folderName = pfolderName;
}

void Crawler::ForceBackupScheduler()
{
  cout << "Locking mutex to backup scheduler\n";
  Crawler::scheduler_mutex.lock();
  cout << "Backing up scheduler\n";
  Scheduler::PreProcessBackup();
  cout << "Finished backing up scheduler\n";
  Crawler::scheduler_mutex.unlock();
  
  Scheduler::Backup(Crawler::folderName+"scheduler_urls");
}

void Crawler::Log()
{
  sleep(20);
  filebuf fb;
  if(fb.open(Crawler::folderName+"Log", ios::out))
  {
    ostream os(&fb);
    os << Crawler::crawlCount << " different url's collected\n";
    fb.close();
  }
}

void Crawler::LoadScheduler()
{
  string url;
  filebuf fb;
  if(fb.open(this->seedFilename, ios::in))
  {
    istream is(&fb);
    while(true)
    {
      getline(is, url);
      if(not is) break;
      if(not Scheduler::AddURL(url))
        cerr << "Discarded: " << url << endl;
    }
    fb.close();
  }
  else
  {
    cout << "Error: Could not open the seeds file\n";
    exit(1);
  }
}

void Crawler::Crawl()
{
  Dumper dmp;
  CkSpider spider;
  CkString collectedUrl, collectedHtml;
  
  stringstream ss;
  ss << this_thread::get_id();
  
  string filename = Crawler::folderName + "f" + ss.str();
  dmp.SetFilename(filename);
  dmp.OpenStream();
  
  while(true)
  {
    Crawler::scheduler_mutex.lock();
    string nextUrl = Scheduler::GetNext();
    Scheduler::RemoveTop();
    Crawler::scheduler_mutex.unlock();
    
    Crawler::crawlCount_mutex.lock();
    if(nextUrl != "")
      Crawler::collecting+=1;
    Crawler::crawlCount_mutex.unlock();
    
    if(Crawler::stopping)
    {
      break;
    }

    if(Scheduler::IsEmpty())
    {
      bool loaded=false, isThereThreadCollecting=false;
      Crawler::crawlCount_mutex.lock();
      isThereThreadCollecting = (Crawler::collecting>0);
      Crawler::crawlCount_mutex.unlock();
      
      
      Crawler::scheduler_mutex.lock();
      loaded=Scheduler::LoadFromDump();
      Crawler::scheduler_mutex.unlock();
      if(not loaded && not isThereThreadCollecting)
      {
        cout << "There is no more URL's to collect\n";
        Crawler::stopping=true;
        break;
      }
      continue;
    }
    
    spider.Initialize(Utils::GetDomain(nextUrl).c_str());
    if(not spider.CrawlNext())
    {
      Crawler::scheduler_mutex.lock();
      Scheduler::ForceAddURL(nextUrl);
      Crawler::scheduler_mutex.unlock();
      continue;
    }
    
    Crawler::crawlCount_mutex.lock();
    Crawler::crawlCount++;
    cout << Crawler::crawlCount << " " << nextUrl << endl;
    Crawler::crawlCount_mutex.unlock();
    
    spider.get_LastUrl(collectedUrl);
    spider.get_LastHtml(collectedHtml);
    
    dmp.Dump(collectedUrl, collectedHtml);
    
    // Adding the non-outbound links to the scheduler
    int unspidered = spider.get_NumUnspidered();
    for(int i = 0; i < unspidered; i++)
    {
      spider.GetUnspideredUrl(0, collectedUrl);
      string curl = collectedUrl.getString();
      curl.shrink_to_fit();
      spider.SkipUnspidered(0);
      
      Crawler::scheduler_mutex.lock();
      Scheduler::AddURL(curl);
      Crawler::scheduler_mutex.unlock();
    }
    
    // Adding the outbound links to the scheduler
    for(int i = 0; i < spider.get_NumOutboundLinks(); i++)
    {
      if(not spider.GetOutboundLink(i, collectedUrl)) continue;
      string curl = collectedUrl.getString();
      curl.shrink_to_fit();
      
      Crawler::scheduler_mutex.lock();
      Scheduler::AddURL(curl);
      Crawler::scheduler_mutex.unlock();
    }
    spider.ClearOutboundLinks();
    spider.ClearSpideredUrls();
    spider.ClearFailedUrls();
    
    Crawler::crawlCount_mutex.lock();
    Crawler::collecting-=1;
    Crawler::crawlCount_mutex.unlock();
  }
  
  dmp.CloseStream();
}
