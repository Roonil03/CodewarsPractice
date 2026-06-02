#include <bits/stdc++.h>

using namespace std;

std::vector<int> snail(const std::vector<std::vector<int>> &snail_map) {
  if(snail_map.empty() || snail_map[0].empty()){
    return {};
    } 
  int t = 0, b = snail_map.size() - 1;
  int l = 0, r = snail_map[0].size() - 1;
  vector<int> res;
  res.reserve((b + 1) * (r + 1));
  while (t <= b && l <= r) {
      for (int i = l; i <= r; ++i){
        res.push_back(snail_map[t][i]);
        }
      t++;
      for (int i = t; i <= b; ++i){
        res.push_back(snail_map[i][r]);
        }
      r--;
      if (t <= b) {
          for (int i = r; i >= l; --i){
            res.push_back(snail_map[b][i]);
            }
          b--;
      }
      if (l <= r) {
          for (int i = b; i >= t; --i){
            res.push_back(snail_map[i][l]);
            }
          l++;
      }
  }
  return res;
}