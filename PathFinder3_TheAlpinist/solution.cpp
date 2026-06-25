// #include <string>
#include <bits/stdc++.h>
using namespace std;

int path_finder(const std::string& maze)
{
  // your code here... enjoy!
//   return -1;
    vector<string> g;
    stringstream ss(maze);
    string t;
    while(ss >> t){
        g.push_back(t);
    }
    int n = g.size();
    if(!n){
        return 0;
    }
    vector<vector<int>> d(n, vector<int>(n, 1e9));
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> q;
    d[0][0] = 0;
    q.push({0, 0, 0});
    int w[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while(!q.empty()){
        auto[c, y, x] = q.top();
        q.pop();
        if(y == n - 1 && x == n - 1){
            return c;
        }
        if(c > d[y][x]){
          continue;
        }
        for(auto a : w){
          int ny = y + a[0], nx = x + a[1];
          if(ny >= 0 && ny < n && nx >= 0 && nx < n){
            int nc = c + abs(g[y][x] - g[ny][nx]);
            if(nc < d[ny][nx]){
              d[ny][nx] = nc;
              q.push({nc, ny, nx});
            }
          }
        }
      }
    return 0;
}
