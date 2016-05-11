#include <iostream>
using namespace std;

#define endl "\n"
typedef long long int ll;

int main()
{
  ios::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);

  //TODO:
  // 1) Read the crawled pages.
  // 2) Foreach document read, send to the parser the string of the document with its id.
  // 3) Save the parser's result in a file.
  // 4) Sort the file.
  // 5) Create the index using the sorted file.
  // 6) Save the vocabulary with the ids in a file.
  
  // The sorted file before the index will have a quadruple for each line:
  // <TermID, DocumentID, Term Frequency on the document, position of the term>
  
  // Each line of the index file will represent a term of the vocabulary.
  // A line will have triples <DocumentID, Term Frequency of the document, position of the term>
  
  return 0;
}
