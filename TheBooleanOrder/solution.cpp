#include <bits/stdc++.h>
using namespace std;

int64_t solve(const std::string &s, const std::string &ops)
{
//   return 0;
  int n = s.length();
  vector<vector<int64_t>> t(n, vector<int64_t>(n, 0));
  vector<vector<int64_t>> f(n, vector<int64_t>(n, 0));
  for(int i {0}; i < n; i++){
    t[i][i] = (s[i] == 't');
    f[i][i] = (s[i] == 'f');
  }
  for(int i {1}; i < n; i++){
    for(int j {0}; j < n - i; j++){
      int k = j + i;
      for(int l = j; l < k; l++){
        int64_t tt = t[j][l] * t[l + 1][k];
        int64_t tf = t[j][l] * f[l + 1][k];
        int64_t ft = f[j][l] * t[l + 1][k];
        int64_t ff = f[j][l] * f[l + 1][k];
        if(ops[l] == '&'){
          t[j][k] += tt;
          f[j][k] += tf + ft + ff;
        } else if(ops[l] == '|'){
          t[j][k] += tt + tf + ft;
          f[j][k] += ff;
        } else if(ops[l] == '^'){
          t[j][k] += tf + ft;
          f[j][k] += tt + ff;
        }
      }
    }
  }
  return t[0][n-1];
}