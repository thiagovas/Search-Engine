#include <iostream>
#include <clocale>
#include <string>
#include <cstring>
#include <algorithm>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
using namespace std;

std::string oia(const std::string& str) {
    UnicodeString source = UnicodeString::fromUTF8(StringPiece(str));
    
    UErrorCode status = U_ZERO_ERROR;
    Transliterator *accentsConverter = Transliterator::createInstance(
        "NFD; [:Mn:] Remove; NFC", UTRANS_FORWARD, status);
    accentsConverter->transliterate(source);
    // TODO: handle errors with status

    // UTF-16 UnicodeString -> UTF-8 std::string
    std::string result;
    source.toUTF8String(result);
    
    return result;
}


int main()
{
  string s = "Alô Mundo\n";
  cout << s;
  cout << oia(s);
  return 0;
}
