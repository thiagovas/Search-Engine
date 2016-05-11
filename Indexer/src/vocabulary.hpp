#ifndef _vocabulary_hpp
#define _vocabulary_hpp

#include <map>
#include <string>
#include <vector>
#include <cstdlib>


class Vocabulary
{
  public:
    
    // Function to add a word to the vocabulary.
    void AddWord(std::string &s);
    
    // Returns the index of a word, -1 if it doesn't exist.
    int GetIndex(std::string &s) const;
    
    // Given an index, this function returns the correspondent word.
    // It returns an empty string if the index doesn't exist.
    std::string GetWord(int index) const;
    
  private:
    static std::map<std::string, int> fromWordToIndex;
    static std::vector<std::string> fromIndexToWord;
    static int numberOfWords;
};


#endif
