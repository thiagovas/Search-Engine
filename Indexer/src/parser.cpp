#include "parser.hpp"
using namespace std;


void Parser::ConvertToUtf8(string &html) const
{
  iconvpp::converter objConverter("UTF8", "iso-8859-1", true, 2000000);
  string output;
  objConverter.convert(html, output);
  html=output;
}


vector<string> Parser::GetWords(string &html) const
{
  vector<string> words;
  this->ConvertToUtf8(html);
  html = this->RemoveSpecialCharacters(html);
  
  GumboOutput *output = gumbo_parse(html.c_str());
  string cleantext = this->GetCleanText(output->root);
  words = this->SplitStr(cleantext);
  
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  words.shrink_to_fit();

  return words;
}


string Parser::RemoveSpecialCharacters(string &str) const
{
  UnicodeString source = UnicodeString::fromUTF8(StringPiece(str));
  
  UErrorCode status = U_ZERO_ERROR;
  Transliterator *accentsConverter = Transliterator::createInstance(
      "NFKD; [:Mn:] Remove; NFKC", UTRANS_FORWARD, status);
  accentsConverter->transliterate(source);
  
  std::string result;
  source.toUTF8String(result);
  
  // Transforming the string characters to lower case.
  transform(result.begin(), result.end(), result.begin(), ::tolower);

  delete accentsConverter;
  return result;
}


string Parser::GetCleanText(GumboNode* node) const
{
  if (node->type == GUMBO_NODE_TEXT)
  {
    return string(node->v.text.text);
  }
  else if (node->type == GUMBO_NODE_ELEMENT &&
           node->v.element.tag != GUMBO_TAG_SCRIPT &&
           node->v.element.tag != GUMBO_TAG_STYLE)
  {
    string contents = "";
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i++)
    {
      const string text = this->GetCleanText((GumboNode*) children->data[i]);
      if (i != 0 && !text.empty())
        contents.append(" ");
      contents.append(text);
    }
    return contents;
  }
  else return "";
}

bool IsSpecial(char a)
{
  if(not isprint(a))
  {
    return true;
  }
  
  switch(a)
  {
    case ',':
    case '.':
    case '-':
    case '_':
    case '+':
    case ';':
    case ':':
    case '[':
    case '{':
    case ']':
    case '(':
    case ')':
    case '}':
    case '\\':
    case '"':
    case '\'':
    case '/':
    case '|':
    case '!':
    case '$':
    case '%':
    case '*':
    case '&':
    case '?':
    case '<':
    case '>':
    case '@':
    case '#':
      return true;
  }
  return false;
}

vector<string> Parser::SplitStr(string &s) const
{
  //,.-_+;:[{]}|!@#$%*&?<>
  std::replace_if(s.begin(), s.end(), IsSpecial, ' ');
  
  vector<string> result;
  string str = s, token, delimiter = " ";
  size_t pos=0;
  while((pos=str.find(delimiter)) != std::string::npos)
  {
    token = str.substr(0, pos);
    if(token.size() != 0)
      result.push_back(token);
    str.erase(0, pos+delimiter.length());
  }
  if(str.size() != 0)
    result.push_back(str);
  return result;
}
