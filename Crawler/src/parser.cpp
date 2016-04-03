#include "parser.hpp"
using namespace std;

// It returns the urls contained on the html.
// The URL's returned are on the canonical form.
vector<string> Parser::GetLinks(string &html, string &url)
{
  vector<string> result;
  
  // Get All complete url's
  GetAll(result, html, "");
  
  // Get All relative url's
  GetAll(result, html, "");
  
  
  // Canonizing every url collected
  for(int i = 0; i < result.size(); i++)
    CanonizeUrl(result[i]);
  
  return result;
}

// Method that transforms the url into a canonical form
void Parser::CanonizeUrl(string &url)
{
  
}

// Method that add on vmatches all substrings that matches the regex pattern.
void Parser::GetAll(vector<string> &vmatches, string str, string pattern)
{
  try {
    regex re(pattern);
    sregex_iterator next(str.begin(), str.end(), re);
    sregex_iterator end;
    while(next != end)
      vmatches.push_back((next++)->str());
  }
  catch(regex_error &e)
  {
    cerr << "Error: parser.cpp -> GetAll function -> Error in the regular expression\n";
    exit(1);
  }
}
