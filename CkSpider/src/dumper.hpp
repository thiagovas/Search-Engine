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
    void AddPage(CkString &url, CkString &html);
    void Dump();
    void ForceDump();
    void CloseStream();

  private:
    std::string _filename;
    std::filebuf _fb;
    std::queue<std::pair<std::string, std::string> > _vp;
};

#endif
