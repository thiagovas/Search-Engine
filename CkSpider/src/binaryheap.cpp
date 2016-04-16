#include "binaryheap.hpp"
using namespace std;

BinaryHeap::BinaryHeap(unsigned size)
{
  this->Initialize(size);
}

void BinaryHeap::Initialize(unsigned size)
{
  this->vHeap.resize(size+3, make_pair("", -this->INF));
  this->vHeap.shrink_to_fit();
  this->number_elements=0;
}

bool BinaryHeap::Push(pair<string, int> neue)
{
  if(this->number_elements+3 == this->vHeap.size()) return false;
  if(this->number_elements==0)
  {
    this->vHeap[1] = neue;
    this->number_elements=1;
    return true;
  }
  
  this->vHeap[this->number_elements+1] = neue;
  unsigned i=this->number_elements+1, parent;
  while(i > 1)
  {
    parent = GetParent(i);
    if(this->vHeap[parent].second > this->vHeap[i].second)
    {
      swap(this->vHeap[parent], this->vHeap[i]);
      i = parent;
    }
    else break;
  }
  
  this->number_elements++;
  return true;
}

void BinaryHeap::Pop()
{
  unsigned i=1;
  this->vHeap[1].first.clear();
  this->vHeap[1] = this->vHeap[this->number_elements];
  this->vHeap[this->number_elements] = make_pair("", -this->INF);
  this->number_elements--;
  
  while(i <= this->number_elements)
  {
    unsigned left = GetLeft(i), right = GetRight(i);
    if(left > this->number_elements) break;
    
    unsigned smaller = left;
    if(right <= this->number_elements && this->vHeap[right].second < this->vHeap[left].second)
      smaller = right;
    
    if(this->vHeap[i].second <= this->vHeap[smaller].second) break;
    swap(this->vHeap[i], this->vHeap[smaller]);
    i=smaller;
  } 
}

pair<string, int> BinaryHeap::Top() const
{
  if(this->Empty()) return make_pair("", 0);
  return this->vHeap[1];
}

bool BinaryHeap::Empty() const
{
  return (this->number_elements==0);
}

unsigned BinaryHeap::Size() const
{
  return this->number_elements;
}

unsigned BinaryHeap::Capacity() const
{
  return this->vHeap.size()-3;
}

vector<pair<string, int> > BinaryHeap::GetElements()
{
  vector<pair<string, int> > elements;
  for(unsigned i = 1; i <= this->number_elements; i++)
    elements.push_back(this->vHeap[i]);
  return elements;
}

void BinaryHeap::Clear()
{
  this->vHeap.clear();
  this->vHeap.shrink_to_fit();
  this->number_elements=0;
}

inline unsigned BinaryHeap::GetParent(unsigned i) const
{ return (i>>1); }

inline unsigned BinaryHeap::GetRight(unsigned i) const
{ return (i<<1)+1; }

inline unsigned BinaryHeap::GetLeft(unsigned i) const
{ return (i<<1); }
