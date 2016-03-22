#include "crawler.hpp"
using namespace std;


Crawler::Crawler()
{}

void Crawler::Start(string pseedFilename, int pnThreads, int pnFiles)
{
  this->seedFilename = pseedFilename;
  this->nThreads = pnThreads;
  this->nFiles = pnFiles;
  this->LoadScheduler();
  
  
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  if(!curl)
  {
    cout << "Error: Curl did not initialize correctly\n";
    exit(1);
  }
  
  
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Crawler::WriteOnString);
  while(not this->_scheduler.IsEmpty())
  {
    string url = this->_scheduler.GetNext(), html;
    this->_scheduler.RemoveTop();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
    res = curl_easy_perform(curl);
    cout << url << endl;
  }
  curl_easy_cleanup(curl);
}

void Crawler::SetOutputFolder(string pfolderName)
{
  this->folderName = pfolderName;
}

void Crawler::Stop()
{
  cout << "Stopping...\n";
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
      _scheduler.AddURL(url);
    }
    fb.close();
  }
  else
  {
    cout << "Error: Could not open the seed file\n";
    exit(1);
  }
}

size_t Crawler::WriteOnString(void *content, size_t size, size_t nmembytes, void *userp)
{
  ((string*)userp)->append((char*)content, size*nmembytes);
  return size*nmembytes;
}
