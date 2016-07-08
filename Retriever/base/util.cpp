#include "util.hpp"


std::vector<std::string> base::Util::SplitStr(std::string &s, std::string delimiter) const
{
  std::vector<std::string> result;
  std::string str = s, token;
  size_t pos=0;
  while((pos=str.find(delimiter)) != std::string::npos)
  {
    token = str.substr(0, pos);
    if(token.size() != 0)
      result.push_back(token);
    str.erase(0, pos+delimiter.length());
  }
  if(str.size() != 0)
    result.push_back(str);
  return result;
}
