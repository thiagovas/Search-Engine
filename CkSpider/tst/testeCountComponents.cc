#include <bits/stdc++.h>
using namespace std;


#define endl "\n"
typedef long long int ll;


int CountComponents(string url)
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
  if(i < 0) cout << "\nIH, DEU PAU\n";
  
  // Ignoring the www in front of the url
  const string www = "www."; j=0;
  if(i < 0) cout << "\nIH, DEU PAU\n";
  for(;i < url.size() && j < www.size(); i++)
  {
    if(url[i]==www[j]) j++;
    else break;
  }
  if(j != www.size()) i-=j;
  
  if(i < 0) cout << "\nIH, DEU PAU\n";
  cout << i << endl;
  for(;i+1 < url.size(); i++)
    if(url[i]=='.' || url[i]=='/' || url[i]=='&' || url[i]=='?') c++;
  
  return c;
}

int main()
{
  vector<string> v;
  
  v.push_back("http://www.dietaesaude.com.br/como-funciona/metodologia");
  v.push_back("https://www.globo.com");
  v.push_back("http://www.globo.com");
  v.push_back("www.globo.com");
  v.push_back("globo.com");
  v.push_back(" ");

  
  for(int i = 0; i < v.size(); i++)
    cout << v[i] << " " << CountComponents(v[i]) << endl;
  
  return 0;
}
