#ifndef _compressor_hpp
#define _compressor_hpp

#include <string>
#include <vector>

class Compressor {
  public:
    std::string Compress(std::string s);
    std::string Decompress(std::string s);
};

#endif
