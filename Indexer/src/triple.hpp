#ifndef _triple_hpp
#define _triple_hpp

class Triple {
  public:
    
    Triple(int ptermid, int pdocid, int pfrequency);

    void SetTriple(int ptermid, int pdocid, int pfrequency);
    
    int GetTermId() const;

    int GetDocId() const;

    int GetFrequency() const;

    bool operator< (const Triple &a) const;
    
  private:
    int termid, docid, frequency;
};

#endif
