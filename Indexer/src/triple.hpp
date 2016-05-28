#ifndef _triple_hpp
#define _triple_hpp

class Triple {
  public:
    
    void SetTriple(int ptermid, int pdocid, int pfrequency);
    
    int GetTermId() const;

    int GetDocId() const;

    int GetFrequency() const;
    
  private:
    int termid, docid, frequency;
};

#endif
