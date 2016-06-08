#include "triple.hpp"


Triple::Triple(int ptermid, int pdocid, int pfrequency)
{
  this->SetTriple(ptermid, pdocid, pfrequency);
}

void Triple::SetTriple(int ptermid, int pdocid, int pfrequency)
{
  this->termid = ptermid;
  this->docid = pdocid;
  this->frequency = pfrequency;
}

int Triple::GetTermId() const
{
  return this->termid;
}

int Triple::GetDocId() const
{
  return this->docid;
}

int Triple::GetFrequency() const
{
  return this->frequency;
}

bool Triple::operator< (const Triple &a) const
{
  if(this->termid == a.GetTermId())
  {
    if(this->docid == a.GetDocId())
      return this->frequency > a.GetFrequency();
    else
      return this->docid > a.GetDocId();
  }
  else
  {
    return this->termid > a.GetTermId();
  }
}
