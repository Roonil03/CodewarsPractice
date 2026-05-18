#include<bits/stdc++.h>
using namespace std;

std::string pig_it(std::string str)
{
    // Code here
  string res;
  for (int i {0}, n = str.length(); i < n; i++){
    if(isalpha(str[i])){
      int j = i;
      while(j < n && isalpha(str[j])){
        j++;
      }
      res += str.substr(i + 1, j - i - 1) + str[i] + "ay";
      i = j - 1;
    } else{
      res += str[i];
    }
  }
  return res;
}