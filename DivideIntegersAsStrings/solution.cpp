// #include <iostream>
// #include <string>
// #include <utility>
#include <bits/stdc++.h>
using namespace std;

bool cmp(const string& a, const string& b){
  if(a.length() != b.length()){
    return a.length() < b.length();
  }
  return a < b;
}

string sub(const string& a, const string& b){
  string res = "";
  int i = a.length() - 1, j = b.length() - 1, c = 0;
  while(i >= 0){
    int d = (a[i] - '0') - c - (j >= 0 ? b[j] - '0' : 0);
    c = d < 0;
    if(c){
      d += 10;
    }
    res.push_back(d + '0');
    i--;
    j--;
  }
  while(res.length() > 1 && res.back() == '0'){
    res.pop_back();
  }
  reverse(res.begin(), res.end());
  return res;
}

auto divide_strings(const std::string& a, const std::string&  b)
-> std::pair<std::string, std::string> {
  // This might work for the sample tests and maybe even half of the random tests 
  // but it won't work for arbitrarily large integers
//   return { 
//     std::to_string(std::stoll(a, nullptr, 10) / std::stoll(b, nullptr, 10)), 
//     std::to_string(std::stoll(a, nullptr, 10) % std::stoll(b, nullptr, 10))
//   };
  string q = "", r = "";
  for(char c : a){
    if(r == "0"){
      r = "";
    }
    r += c;
    int count = 0;
    while(!cmp(r, b)){
      r = sub(r, b);
      count++;
    }
    q += to_string(count);
  }
  while(q.length() > 1 && q[0] == '0'){
    q.erase(0, 1);
  }
  if(q.empty()){
     q = "0";
  }
  if(r.empty()){
    r = "0";
  }
  return {q, r};
}