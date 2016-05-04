#include "dumper.hpp"
using namespace std;

Dumper::Dumper()
{
  this->dumpCount=0;
}

void Dumper::SetFilename(string filename)
{
  this->_filename = filename;
}

void Dumper::OpenStream()
{
  this->_fb.open(this->_filename, ios::out);
  this->out = new ostream(&this->_fb);
  this->dumpCount=0;
}

void Dumper::Dump(CkString &ckurl, CkString &ckhtml)
{
  this->dumpCount++;
  (*this->out) << "|||\n" << ckurl.getString() << "\n|\n";
  (*this->out) << ckhtml.getString();
  
  if(this->dumpCount > 100)
  {
    (*this->out) << endl;
    this->out->flush();
    this->dumpCount=0;
  }
  else (*this->out) << "\n";
}

void Dumper::CloseStream()
{
  delete this->out;
  this->_fb.close();
}
