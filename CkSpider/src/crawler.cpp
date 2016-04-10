#include "crawler.hpp"
using namespace std;

std::string Crawler::folderName = ".\\";
std::mutex Crawler::scheduler_mutex;
bool Crawler::stopping = false;
int Crawler::crawlCount = 0;
map<string, long long int> Crawler::weights;

Crawler::Crawler()
{
  this->urlWeight=0;
}

void Crawler::Start(string pseedFilename, int pnThreads)
{
  this->seedFilename = pseedFilename;
  this->nThreads = pnThreads;
  this->LoadScheduler();
  Crawler::stopping = false;
  
  vector<thread> running;
  for(int i = 0; i < pnThreads; i++)
    running.push_back(thread(&Crawler::Crawl, this));
  
  for(int i = 0; i < pnThreads; i++)
    running[i].join();
  
  cout << "Stopped crawling\n";
}

void Crawler::SetOutputFolder(string pfolderName)
{
  Crawler::folderName = pfolderName;
}

void Crawler::Log()
{
  sleep(10);
  filebuf fb;
  if(fb.open(Crawler::folderName+"Log", ios::out))
  {
    ostream os(&fb);
    os << Crawler::crawlCount << " different url's collected\n";
    fb.close();
  }
}

void Crawler::Stop()
{
  cout << "\nStopping...\n";
  Crawler::stopping = true;
  this->Log();
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
      if(not Scheduler::AddURL(url, -1))
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
  CkString collectedUrl, collectedTitle, collectedHtml;
  
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
    
    //if(nextUrl!="")
      cout << Crawler::crawlCount << " " << nextUrl << endl;
    
    Crawler::scheduler_mutex.unlock();
    if(Crawler::stopping)
    {
      dmp.ForceDump();
      break;
    }
    if(Scheduler::IsEmpty()) continue;
    
    Crawler::scheduler_mutex.lock();
    Crawler::crawlCount++;
    Crawler::scheduler_mutex.unlock();
    
    spider.Initialize(nextUrl.c_str());
    spider.CrawlNext();
    spider.get_LastUrl(collectedUrl);
    spider.get_LastHtmlTitle(collectedTitle);
    spider.get_LastHtml(collectedHtml);
    dmp.AddPage(collectedUrl.getString(), collectedTitle.getString(), collectedHtml.getString());
    dmp.Dump();
    
    int unspidered = spider.get_NumUnspidered();
    for(int i = 0; i < unspidered; i++)
    {
      spider.GetUnspideredUrl(0, collectedUrl);
      spider.SkipUnspidered(0);
      string curl = collectedUrl.getString();
      Crawler::scheduler_mutex.lock();
      long long int newWeight = ++Crawler::weights[Utils::GetDomain(curl)];
      Scheduler::AddURL(curl, newWeight);
      Crawler::scheduler_mutex.unlock();
    }
  }
  
  dmp.CloseStream();
}
