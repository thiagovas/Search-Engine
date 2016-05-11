#include "vocabulary.hpp"
using namespace std;

static map<string, int> Vocabulary::fromWordToIndex;
static vector<string> Vocabulary::fromIndexToWord;
static int Vocabulary::numberOfWords;


// Function to add a word to the vocabulary.
void Vocabulary::AddWord(string &s)
{
  if(Vocabulary::fromWordToIndex.find(s) != Vocabulary::fromWordToIndex.end())
    return;
  
  Vocabulary::fromIndexToWord.push_back(s);
  Vocabulary::fromWordToIndex[s] = numberOfWords++;
}

// Returns the index of a word, -1 if it doesn't exist.
int Vocabulary::GetIndex(string &s) const
{
  if(Vocabulary::fromWordToIndex.find(s) == Vocabulary::fromWordToIndex.end())
    return -1;
  
  return Vocabulary::fromWordToIndex[s];
}

// Given an index, this function returns the correspondent word.
string Vocabulary::GetWord(int index) const
{
  if(index < 0 or index >= Vocabulary::fromIndexToWord.size())
    return "";
  
  return Vocabulary::fromIndexToWord[index];
}
