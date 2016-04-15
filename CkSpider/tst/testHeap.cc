#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
typedef long long int ll;

class BinaryHeap {
  public:
    BinaryHeap(unsigned size);
    bool Push(pair<string, int> neue);
    void Pop();
    pair<string, int> Top() const;
    bool Empty() const;
    void PrintHeap() const;
    
  private:
    vector<pair<string, int> > vHeap;
    unsigned number_elements;
    const int INF = 0x3f3f3f3f;
    
    inline unsigned GetParent(unsigned i) const;
    inline unsigned GetRight(unsigned i) const;
    inline unsigned GetLeft(unsigned i) const;
};


BinaryHeap::BinaryHeap(unsigned size)
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

void BinaryHeap::PrintHeap() const
{
  for(unsigned i = 1; i <= this->number_elements; i++)
    cout << this->vHeap[i].second << " ";
  cout << endl;
}
 
inline unsigned BinaryHeap::GetParent(unsigned i) const
{ return (i>>1); }

inline unsigned BinaryHeap::GetRight(unsigned i) const
{ return (i<<1)+1; }

inline unsigned BinaryHeap::GetLeft(unsigned i) const
{ return (i<<1); }







bool isSorted(vector<int> &v)
{
  for(int i = 1; i < v.size(); i++)
    if(v[i] < v[i-1]) return false;
  return true;
}

int main()
{
  ios::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  
  vector<int> v;
  cout << "Initializing the Heap...\n";
  BinaryHeap bh(10);
  cout << "Pushing 10 items...\n\n";
  for(int i = 0; i < 10; i++)
  {
    if(not bh.Push(make_pair("", i)))
      cout << "Did not pushed " << i << endl;
    v.push_back(i);
  }
  cout << "Heap state:\n";
  bh.PrintHeap();
  cout << endl;
  cout << "Removing them...\n";
  while(not bh.Empty())
  {
    cout << bh.Top().second << " ";
    bh.Pop();
  }
  cout << endl << endl;
  
  cout << "Testing all permutations of 10 items...\n";
  do{
    for(int i = 0; i < 10; i++)
      bh.Push(make_pair("", v[i]));
    
    vector<int> resp;
    while(not bh.Empty())
    {
      resp.push_back(bh.Top().second);
      bh.Pop();
    }
    
    if(not isSorted(resp))
    {
      cout << "DEU PAU\n";
      for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
      cout << endl << "Returned:\n";
      for(int i = 0; i < resp.size(); i++)
        cout << resp[i] << " ";
      cout << endl << endl;
      break;
    }
  }while(next_permutation(v.begin(), v.end()));
  cout << "DONE\n";

  return 0;
}
