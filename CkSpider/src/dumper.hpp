#ifndef _dumper_hpp
#define _dumper_hpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "page.hpp"

class Dumper {
  public:
    
    Dumper();
    void SetFilename(std::string filename);
    void OpenStream();
    void AddPage(std::string url, std::string title, std::string html);
    void Dump();
    void ForceDump();
    void CloseStream();

  private:
    std::string _filename;
    std::filebuf _fb;
    std::vector<Page> _vp;
};

#endif
