#ifndef _externalsorter_hpp
#define _externalsorter_hpp

#include <iostream>

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "triple.hpp"

class ExternalSorter {
  public:
    
    ExternalSorter();
    
    
    void Sort(std::string filename);
    
    
    void SetMemoryLimit(int newLimit);
    
  private:
    
    std::string triplesFilename;
    
    int numberChunks;
    
    int memoryLimit;
    
    int maxTriples;
    

    void GenerateSortedChunks();
    
    
    void DumpChunk(std::priority_queue<Triple> &pq);
};


#endif
