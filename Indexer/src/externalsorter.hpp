#ifndef _externalsorter_hpp
#define _externalsorter_hpp


class ExternalSorter {
  public:
    void SortFile(std::string filename);
  private:
    std::string _filename;
};


#endif
