#include "triple.hpp"


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

