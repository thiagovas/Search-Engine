/*
  Running the example provided at gumbo's repository at github...
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include "gumbo.h"

static std::string cleantext(GumboNode* node) {
  if (node->type == GUMBO_NODE_TEXT) {
    return std::string(node->v.text.text);
  } else if (node->type == GUMBO_NODE_ELEMENT &&
             node->v.element.tag != GUMBO_TAG_SCRIPT &&
             node->v.element.tag != GUMBO_TAG_STYLE) {
    std::string contents = "";
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      const std::string text = cleantext((GumboNode*) children->data[i]);
      if (i != 0 && !text.empty()) {
        contents.append(" ");
      }
      contents.append(text);
    }
    return contents;
  } else {
    return "";
  }
}

int main()
{
  std::string a, s;
  while(true)
  {
    getline(std::cin, a);
    if(not std::cin) break;
    s+=a;
  }
  
  GumboOutput *output = gumbo_parse(s.c_str());
  std::cout << cleantext(output->root) << std::endl;
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return 0;
}
