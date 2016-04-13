#ifndef _utils_hpp
#define _utils_hpp

#include <string>
#include <locale>

class Utils {
  public:
    // This function returns the number of components the url has.
    static int CountComponents(std::string url);
    
    // This function returns the domain of the url.
    static std::string GetDomain(std::string &url);
    
    // Hash function
    static short GetURLHash(std::string url);
    
    // This function verifies if [str] has any of the pattern characters
    static bool FindAny(std::string str, std::string pattern);
  private:
};

#endif
