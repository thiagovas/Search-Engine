#ifndef _dumper_hpp
#define _dumper_hpp

#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "CkString.h"

class Dumper {
  public:
    
    Dumper();
    void SetFilename(std::string filename);
    void OpenStream();
    void Dump(CkString &url, CkString &html);
    void CloseStream();

  private:
    std::string _filename;
    std::filebuf _fb;
    std::ostream *out;
    int dumpCount;
};

#endif
