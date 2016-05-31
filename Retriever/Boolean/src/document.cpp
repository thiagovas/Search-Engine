#include "document.hpp"
using namespace std;


namespace retriever
{
namespace boolean
{

Document::Document(int pdocid, std::string &purl)
{
  this->docid = pdocid;
  this->url = purl;
}

int Document::GetDocId()
{
  return this->docid;
}

std::string Document::GetUrl()
{
  return this->url;
}

} // namespace Boolean
} // namespace retriever

