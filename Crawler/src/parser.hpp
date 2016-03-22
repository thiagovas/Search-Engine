#ifndef _parser_hpp
#define _parser_hpp

#include <regex>
#include <vector>
#include <algorithm>
#include <functional>

class Parser
{
  public:
    Parser();
    std::vector<std::string> GetLinks(std::string html);
    
  private:
};

#endif
