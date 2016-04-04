#include "page.hpp"
using namespace std;

Page::Page()
{}

Page::Page(string _url, string _title, string _html)
{
  this->url = _url;
  this->title = _title;
  this->html = _html;
}

string Page::GetUrl()
{ return this->url; }

string Page::GetTitle()
{ return this->title; }

string Page::GetHtml()
{ return this->html; }
