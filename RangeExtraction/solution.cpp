#include <bits/stdc++.h>
using namespace std;

std::string range_extraction(std::vector<int> args) {
  string res = "";
  int n = args.size();
  for(int i {0}; i < n; ){
    int j = i;
    while(j + 1 < n && args[j+1] == args[j] + 1){
      j++;
    }
    if(!res.empty()){
      res += ",";
    }
    if(j - i >= 2){
      res += to_string(args[i]) + "-" + to_string(args[j]);
      i = j + 1;
    } else{
      res += to_string(args[i]);
      i++;
    }
  }
  return res;
}