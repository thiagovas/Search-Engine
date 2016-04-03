#include "crawler.hpp"
using namespace std;

std::string Crawler::folderName = ".\\";
std::mutex Crawler::scheduler_mutex;

Crawler::Crawler()
{ }

void Crawler::Start(string pseedFilename, int pnThreads)
{
  this->seedFilename = pseedFilename;
  this->nThreads = pnThreads;
  this->LoadScheduler();
  
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

void Crawler::Stop()
{
  cout << "Stopping...\n";
  
  // TODO: Make sure every file is closed.
  
  exit(0);
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
      Scheduler::AddURL(url);
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
  CkSpider spider;
  CkString collectedUrl, collectedTitle, collectedHtml;
  
  while(not Scheduler::IsEmpty())
  {
    Crawler::scheduler_mutex.lock();
    string nextUrl = Scheduler::GetNext();
    Scheduler::RemoveTop();
    Crawler::scheduler_mutex.unlock();
    
    spider.Initialize(nextUrl.c_str());
    spider.CrawlNext();
    spider.get_LastUrl(collectedUrl);
    spider.get_LastHtmlTitle(collectedTitle);
    spider.get_LastHtml(collectedHtml);
    
    cout << nextUrl << " " << collectedUrl.getString() << endl << endl;
    int unspidered = spider.get_NumUnspidered();
    for(int i = 0; i < unspidered; i++)
    {
      spider.GetUnspideredUrl(0, collectedUrl);
      spider.SkipUnspidered(0);
      Crawler::scheduler_mutex.lock();
      Scheduler::AddURL(collectedUrl.getString());
      Crawler::scheduler_mutex.unlock();
    }
  }
}
