#ifndef _crawler_hpp
#define _crawler_hpp

#include <algorithm>
#include <string>

class Crawler
{
  public:
    
    Crawler();
    
    // Starts to crawl
    void Start(std::string pseedFilename, int pnThreads, int pnFiles);
    
    // It sets the name of the folder that will keep the pages crawled
    void SetOutputFolder(std::string pfolderName);
    
  private:
    
    // Name of the folder that will keep the pages crawled
    std::string folderName;
    
    std::string seedFileName;
    
    int nThreads;
    
    int nFiles;
};


#endif
