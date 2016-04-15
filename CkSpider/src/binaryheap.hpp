#ifndef _BinaryHeap_hpp
#define _BinaryHeap_hpp

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

// This heap has fixed size, that is, 
class BinaryHeap {
  public:
    BinaryHeap(){}
    BinaryHeap(unsigned size);
    void Initialize(unsigned size);
    bool Push(std::pair<std::string, int> neue);
    void Pop();
    void Clear();
    std::vector<std::pair<std::string, int> > GetElements();
    std::pair<std::string, int> Top() const;
    bool Empty() const;
    unsigned Size() const;
    unsigned Capacity() const;
    
    
  private:
    std::vector<std::pair<std::string, int> > vHeap;
    unsigned number_elements;
    const int INF = 0x3f3f3f3f;
    
    inline unsigned GetParent(unsigned i) const;
    inline unsigned GetRight(unsigned i) const;
    inline unsigned GetLeft(unsigned i) const;
};

#endif
