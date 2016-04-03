#ifndef _utils_hpp
#define _utils_hpp

#include <string>
#include <locale>

class Utils {
  public:
    // This function returns the number of components the url has.
    static int CountComponents(std::string url);
    
    // Returns if the pattern exists on the string.
    static bool Exists(std::string str, std::string pattern);
    
    // This function returns the domain of the url.
    static std::string GetDomain(std::string url);
  private:
};

#endif
