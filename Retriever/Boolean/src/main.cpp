#include <iostream>
#include <vector>
#include "document.hpp"
#include "retriever.hpp"
using namespace std;

int main()
{
  string query;
  cout << "Query: ";
  
  // Reading query...
  getline(std::cin, query);
  
  retriever::boolean::Retriever robj("../../Indexer/output/test_1_mais_2/index",
                                     "../../Indexer/output/test_1_mais_2/urls",
                                     "../../Indexer/output/test_1_mais_2/vocabulary_i.txt");
  
  vector<retriever::boolean::Document> result = robj.Retrieve(query);
  for(retriever::boolean::Document d : result)
  {
    cout << d.GetDocId() << ": " << d.GetUrl() << endl;
  }
  
  
  return 0;
}
