#ifndef _vocabulary_hpp
#define _vocabulary_hpp

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>


class Vocabulary
{
  public:
    
    // Function to add a word to the vocabulary.
    // And return the id given to the new word.
    static int AddWord(std::string &s);
    
    // Returns the index of a word, -1 if it doesn't exist.
    static int GetIndex(std::string &s);
    
    // Given a string s, it returns if s exists on the vocabulary.
    static bool ExistsWord(std::string &s);

    static void Dump();
    
  private:
    static std::map<std::string, int> fromWordToIndex;
    static int numberOfWords;
};


#endif
