#include <bits/stdc++.h>
using namespace std;

std::string encode_rail_fence_cipher(const std::string &str, int n) {
  if(str.empty() || n < 2){
    string res = str;
    return res;
  }
  vector<string>fence(n);
  int rail {0};
  int d {1};
  for(char c : str){
    fence[rail] += c;
    rail += d;
    if(rail == 0 || rail == n - 1){
      d = -d;
    }
  }
  string res = "";
  for(string& r: fence){
    res += r;
  }
  return res;
}

std::string decode_rail_fence_cipher(const std::string &str, int n) {
  if(str.empty() || n < 2){
    string res = str;
    return res;
  }
  int n1 = str.length();
  vector<vector<bool>> mark(n, vector<bool>(n1, false));
  int rail {0};
  int d {1};
  for(int i {0}; i < n1; i++){
    mark[rail][i] = true;
    rail += d;
    if(rail == 0 || rail == n - 1){
      d = -d;
    }
  }
  int id {0};
  vector<string> fence(n);
  for(int i {0}; i < n; i++){
    for(int j {0}; j < n1; j++){
      if(mark[i][j]){
        fence[i] += str[id++];
      }
    }
  }
  string res = "";
  rail = 0;
  d = 1;
  vector<int>pos(n1, 0);
  for(int i{0}; i < n1; i++){
    res += fence[rail][pos[rail]++];
    rail += d;
    if(rail == 0 || rail == n - 1){
      d = -d;
    }
  }
  return res;
}