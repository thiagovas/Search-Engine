#ifndef _parser_hpp
#define _parser_hpp

#include <regex>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <functional>

class Parser
{
  public:
    Parser();

    // Function that returns canonized urls grepped from the html
    // Parameters:
    //    html -> The html source code of the page
    //    url  -> The url of the page crawled
    std::vector<std::string> GetLinks(std::string &html, std::string &url);
    
  private:
    
    // Method that transforms the url into a canonical form
    void CanonizeUrl(std::string &url);
    
    // Method that add on vmatches all substrings that matches the regex pattern.
    void GetAll(vector<string> &vmatches, string str, string pattern);
};

#endif
