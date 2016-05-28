#include "vocabulary.hpp"
using namespace std;

map<string, int> Vocabulary::fromWordToIndex;
vector<string> Vocabulary::fromIndexToWord;
int Vocabulary::numberOfWords;


// Function to add a word to the vocabulary.
// And return the id given to the new word.
int Vocabulary::AddWord(string &s)
{
  map<string, int>::iterator its = Vocabulary::fromWordToIndex.find(s);
  if(its != Vocabulary::fromWordToIndex.end())
    return its->second;
  
  Vocabulary::fromIndexToWord.push_back(s);
  Vocabulary::fromWordToIndex[s] = numberOfWords++;
  return numberOfWords-1;
}

// Returns the index of a word, -1 if it doesn't exist.
int Vocabulary::GetIndex(string &s)
{
  if(Vocabulary::fromWordToIndex.find(s) == Vocabulary::fromWordToIndex.end())
    return -1;
  
  return Vocabulary::fromWordToIndex[s];
}

// Given an index, this function returns the correspondent word.
string Vocabulary::GetWord(unsigned index)
{
  if(index >= Vocabulary::fromIndexToWord.size())
    return "";
  
  return Vocabulary::fromIndexToWord[index];
}

// Given a string s, it returns if s exists on the vocabulary.
bool Vocabulary::ExistsWord(std::string &s)
{
  return (Vocabulary::fromWordToIndex.find(s) !=
          Vocabulary::fromWordToIndex.end());
}

void Vocabulary::Dump()
{
  filebuf fb;
  fb.open(".tmp/vocabulary_l.txt", std::ios::out);
  ostream os(&fb);
  
  for(pair<string, int> e : Vocabulary::fromWordToIndex)
  {
    os << e.first << " " << e.second << endl;
  }
  os.flush();
  fb.close();
  
  
  fb.open(".tmp/vocabulary_i.txt", std::ios::out);
  for(unsigned i = 0; i < Vocabulary::fromIndexToWord.size(); i++)
    os << i << ": " << Vocabulary::fromIndexToWord[i] << endl;
  os.flush();
  fb.close();
}
