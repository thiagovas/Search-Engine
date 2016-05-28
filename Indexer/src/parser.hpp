/*
  Parser Class

  This class was created to parse the html source codes and return the words
  of its content.

  The only public method here is GetWords, receiving a the html code and
  returning a vector of terms (words).
*/

#ifndef _parser_hpp
#define _parser_hpp

#include <iostream>

#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <algorithm>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include "gumbo.h"
#include "iconv.hpp"


class Parser {
  public:
    // GetWords receive a html string and return the words of the content
    // on it.
    std::vector<std::string> GetWords(std::string &html) const;
    
  private:
    
    // This function retrieves the context text of a GumboNode
    std::string GetCleanText(GumboNode* node) const;
    
    // RemoveSpecialCharacters as the name says, remove the special characters
    // of the string received.
    std::string RemoveSpecialCharacters(std::string &str) const;
    
    // SplitStr splits the string received using some special characters
    // as delimiters.
    std::vector<std::string> SplitStr(std::string &s) const;
    
    // Function that converts the html source code to utf8.
    void ConvertToUtf8(std::string &html) const;
};


#endif
