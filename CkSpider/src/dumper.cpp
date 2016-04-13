#include "dumper.hpp"
using namespace std;

Dumper::Dumper()
{}

void Dumper::SetFilename(string filename)
{
  this->_filename = filename;
}

void Dumper::OpenStream()
{
  this->_fb.open(this->_filename, ios::out);
}

void Dumper::Dump()
{
  if(this->_vp.size() > 100) this->ForceDump();
}

void Dumper::ForceDump()
{
  ostream out(&this->_fb);
  out.sync_with_stdio(false);
  while(not this->_vp.empty())
  {
    out << "|||\n" << this->_vp.front().first << "\n|\n";
    out << this->_vp.front().second << endl;
    this->_vp.pop();
  }
  out.flush();
}

void Dumper::AddPage(CkString &ckurl, CkString &ckhtml)
{
  string url = ckurl.getString();
  string html = ckhtml.getString();
  url.shrink_to_fit();
  html.shrink_to_fit();
  this->_vp.push(make_pair(url, html));
}

void Dumper::CloseStream()
{
  this->_fb.close();
}
