// #include <string>
// #include <vector>
#include <bits/stdc++.h>
using namespace std;

std::vector<std::string> get_pins(std::string observed) {
  string adj[] = {"08", "124", "2135", "326", "4157", "52468", "6359", "748", "85790", "968"};
  vector<string> res = {""};
  for(char ch: observed){
    vector<string>rr;
    for(string&s : res){
      for(char a : adj[ch - '0']){
         rr.push_back(s + a);
                       }
    }
    res = move(rr);
  }
  return res;
}