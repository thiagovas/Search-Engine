#ifndef _retriever_document_hpp
#define _retriever_document_hpp


#include <string>

namespace base
{

class Document {
  public:
    Document(int pdocid, std::string &url);
    
    // Returns the id of the document.
    int GetDocId();
    
    // Returns the url of the document.
    std::string GetUrl();
    
  private:
    int docid;
    std::string url;
};

} // namespace base

#endif
