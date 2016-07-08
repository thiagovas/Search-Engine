#ifndef _retriever_hpp
#define _retriever_hpp

#include <vector>
#include <string>
#include <map>
#include "../base/document.hpp"


namespace retriever
{
namespace vectormodel
{

class Retriever {
  public:
    // The constructor of this class receives the name of the index file,
    // the name of the file where the urls are kept and the name of the file,
    // where the vocabulary (sorted by index) is kept.
    Retriever(std::string pIndexFilename, std::string urlsFilename,
              std::string vocabularyFilename);
    
    // Function that processes the given query.
    // The query here is basically a sequence of words.
    // The method consider that words are the terms separated by spaces.
    std::vector<base::Document> Retrieve(std::string &query);
    
  private:
    
    // The name of the file where the index is kept.
    std::string indexFilename;
    
    // Map from term to term id.
    std::map<std::string, int> vocabulary;
    
    // Map from document id to url.
    std::map<int, std::string> murls;
    
    // Method to load the vocabulary.
    void LoadVocabulary(std::string filename);
    
    // Method that loads the urls.
    void LoadUrls(std::string filename);
    
    // This method goes through 
    std::vector<base::Document> GetTopKCosine(std::string &query, unsigned k);
};

} // namespace vectormodel
} // namespace retriever

#endif
