#ifndef _retriever_util_hpp
#define _retriever_util_hpp


#include <vector>
#include <string>


namespace base
{
  class Util {
    public:
      std::vector<std::string> SplitStr(std::string &s, std::string delimiter) const;
      
    private:
      
  };
} // namespace base

#endif
