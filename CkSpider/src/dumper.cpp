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
}

void Dumper::Dump(CkString &ckurl, CkString &ckhtml)
{
  (*this->out) << "|||\n" << ckurl.getString() << "\n|\n";
  (*this->out) << ckhtml.getString() << endl;
  if(this->dumpCount > 50) this->out->flush();
}

void Dumper::CloseStream()
{
  delete this->out;
  this->_fb.close();
}
