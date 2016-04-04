#ifndef _page_hpp
#define _page_hpp

#include <string>

class Page {
  public:
    
    Page();
    Page(std::string _url, std::string _title, std::string _html);
    std::string GetUrl();
    std::string GetTitle();
    std::string GetHtml();
    
  private:
    std::string url, title, html;
};

#endif
