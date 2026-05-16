#include <bits/stdc++.h>
using namespace std;
  
std::string spinWords(const std::string &str)
{
  string res = "", w = "";
  for (char c : str) {
    if (c == ' ') {
      if (w.length() >= 5){
        reverse(w.begin(), w.end());
      }
      res += w + " ";
      w = "";
    } else{
      w += c;
    }
  }
  if (w.length() >= 5){
    reverse(w.begin(), w.end());
  }
  res += w;
  return res;
}