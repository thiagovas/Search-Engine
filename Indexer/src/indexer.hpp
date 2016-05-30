#ifndef _indexer_hpp
#define _indexer_hpp

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
    
    // The name of the file where the triples stay.
    // This is the not sorted file.
    std::string triplesFilename;
    
    // File buffer used to write at the triples file.
    std::filebuf fb;
    
    // File buffer for the file that keeps the urls.
    std::filebuf urlFile;
    
    // Map used to count the frequency of each term in a document.
    std::map<int, int> frequency;
    
    // Method to add the triples of the page html on the triples file.
    void AddTriples(std::string &html, std::string &url, int docid);   
    
    // Method to write the term id, document id and the frequency of the term
    // on a file referenced by os.
    void WriteTriple(std::ostream &os, int termid, int docid, int frequency);
    
    // Method to open fb
    void OpenTriplesFile();
    
    // Method just to close fb, the file buffer used to write
    // at the triples file.
    void CloseTriplesFile();
    
    // Method to set a new name for the file used as output by
    // GenerateTriples function.
    void SetTriplesFilename(std::string pfilename);
    
    // This function generate the triples given a set of files with 
    // the documents collected by the crawler.
    void GenerateTriples(std::vector<std::string> &vFilenames);
    
    // Method that basically calls the external sorter.
    void SortTriples();
    
    // Function that reads the sorted triples file and write the index.
    void WriteFinalIndexFile();
};


#endif
