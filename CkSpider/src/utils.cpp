#include "utils.hpp"
using namespace std;

// This function verifies if [str] has any of the pattern characters
bool Utils::FindAny(string str, string pattern)
{
  for(unsigned i = 0; i < str.size(); i++)
  {
    bool found=false;
    for(unsigned j = 0; j < pattern.size(); j++)
    {
      if(str[i] == pattern[j])
      {
        found=true;
        break;
      }
    }
    if(found) return true;
  }
  return false;
}

string Utils::GetDomain(string &url)
{
  unsigned i, j=0;
  const string http = "https";
  
  // Ignoring the http in front of the url
  // If the url doesnt start with http:// it does nothing
  for(i=0; i < url.size() && j < http.size(); i++)
  {
    if(url[i]==http[j]) j++;
    else break;
  }
  if(j+1 >= http.size()) i+=3;
  
  for(;i < url.size(); i++)
    if(url[i]=='/') break;
  
  return url.substr(0, i);
}

// This function returns the number of components the url has.
int Utils::CountComponents(string url)
{
  int c=1;
  unsigned i, j=0;
  const string http = "https";
  
  // Ignoring the http in front of the url
  // If the url doesnt start with http:// it does nothing
  for(i=0; i < url.size() && j < http.size(); i++)
  {
    if(url[i]==http[j]) j++;
    else break;
  }
  if(j+1 >= http.size()) i+=3;
  
  // Ignoring the www in front of the url
  const string www = "www."; j=0;
  for(;i < url.size() && j < www.size(); i++)
  {
    if(url[i]==www[j]) j++;
    else break;
  }
  if(j != www.size()) i-=j;
   
  for(;i+1 < url.size(); i++)
    if(url[i]=='.' || url[i]=='/' || url[i]=='&' || url[i]=='?') c++;
  
  return c;
}

unsigned char Utils::GetURLHash(string &url)
{
  unsigned char hash=0;
  for(unsigned i = 0; i < url.size(); i++)
    if(isalpha(url[i]))
      hash += url[i]-'A';
  return hash;
}
