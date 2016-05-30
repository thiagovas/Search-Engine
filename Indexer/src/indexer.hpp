#ifndef _indexer_hpp
#define _indexer_hpp

#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "parser.hpp"
#include "vocabulary.hpp"
#include "externalsorter.hpp"

class Indexer
{
  public:
    Indexer();
    
    void Index(std::vector<std::string> &vFilenames);
    
  private:

    std::string triplesFilename;
    
    std::filebuf fb;
    
    std::map<int, int> frequency;
    
    void AddTriples(std::string &html, std::string &url, int docid);   
    
    void WriteTriple(std::ostream &os, int termid, int docid, int frequency);
    
    void OpenTriplesFile();
    
    void CloseTriplesFile();
    
    void SetTriplesFilename(std::string pfilename);

    void GenerateTriples(std::vector<std::string> &vFilenames);
    
    void SortTriples();
};


#endif
