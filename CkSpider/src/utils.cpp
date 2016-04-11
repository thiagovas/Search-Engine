#include "utils.hpp"
using namespace std;

bool Utils::Exists(string str, string pattern)
{
  int u[256], i, j, k;
  if(str.size() < pattern.size()) return false;
  
  for(i = 0; i < 256; i++) u[i] = 0;
  for(i = 0; i < (int)pattern.size(); i++) u[(int)pattern[i]] = i;
  k = pattern.size()-1;
  while(k < (int)str.size())
  {
    i = pattern.size()-1, j = k;
    while(i >= 0 && str[j] == pattern[i]) i--, j--;
    if(i < 0) return true;
    if(k == (int)str.size()-1) break;
    k += pattern.size() - u[(int)str[k+1]];
  }
  return false;
}

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
  if(j >= http.size()-1) i+=3;
  
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
  if(j >= http.size()-1) i+=3;
  
  // Ignoring the www in front of the url
  const string www = "www."; j=0;
  for(;i < url.size() && j < www.size(); i++)
  {
    if(url[i]==www[j]) j++;
    else break;
  }
  if(j != www.size()) i-=j;
  
  for(;i < url.size()-1; i++)
    if(url[i]=='.' || url[i]=='/' || url[i]=='&' || url[i]=='?') c++;
  
  return c;
}

short Utils::GetURLHash(string url)
{
  short hash=0;
  for(unsigned i = 0; i < url.size(); i++)
    if(isalpha(url[i]))
      hash += url[i]-'A';
  return hash;
}
