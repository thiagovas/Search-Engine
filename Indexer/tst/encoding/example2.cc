#include <iostream>
#include <clocale>
#include <string>
#include <cstring>
#include <algorithm>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
using namespace std;


string RemoveSpecialCharacters(string &str)
{
  UnicodeString source = UnicodeString::fromUTF8(StringPiece(str));
  
  UErrorCode status = U_ZERO_ERROR;
  Transliterator *accentsConverter = Transliterator::createInstance(
      "NFD; [:Mn:] Remove; NFC", UTRANS_FORWARD, status);
  accentsConverter->transliterate(source);
  
  string result;
  source.toUTF8String(result);
  
  // Transforming the string characters to lower case.
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  
  return result;
}


int main()
{
  string s = "áàéèíìóòúù ç ãâẽêĩîõôũû  ÁÀÉÈÍÌÓÒÚÙ Ç ÃÂẼÊĨÎÕÔŨÛ\n";
  cout << s;
  cout << (s=RemoveSpecialCharacters(s));
  const char *oia = s.c_str();
  for(int i = 0; i < s.size(); i++)
    cout << oia[0];
  cout << endl;
  return 0;
}
