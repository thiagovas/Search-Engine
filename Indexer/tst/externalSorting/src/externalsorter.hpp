#ifndef _externalsorter_hpp
#define _externalsorter_hpp

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "triple.hpp"

class ExternalSorter {
  public:
    
    ExternalSorter();
    
    // Function that sorts [filename] using a multiway sorting algorithm.
    void Sort(std::string filename);
    
    // Method to update the primary memory limit
    void SetMemoryLimit(int newLimit);
    
  private:
    
    std::string triplesFilename;
    
    // The number of chunk files GenerateSortedChunks generated.
    int numberChunks;
    
    // Primary memory limit in bytes.
    // Default value is 128Mb.
    int memoryLimit;
    
    // The maximum number of triples that can be represented in primary memory.
    int maxTriples;
    
    void GenerateSortedChunks();
    
    // Method to dump the priority queue in the next chunk file.
    // This method is called whenever the priority queue gets full.
    void DumpChunk(std::priority_queue<Triple> &pq);
};


#endif
