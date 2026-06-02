#include <bits/stdc++.h>
using namespace std;

bool validate_battlefield(std::vector< std::vector<int> > field) {
  // Write your magic here ;)
  int ships[5] = {0};
  int n {10};
  for(int i {0}; i < n; i++){
    for(int j {0}; j < n; j++){
      if(field[i][j] == 1){
        int a = i, b = i, c = j, d = j;
        int sz {0};
        queue<pair<int, int>> q;
        q.push({i, j});
        field[i][j] = 0;
        while(!q.empty()){
          auto[r, o] = q.front();
          q.pop();
          sz++;
            a = min(a, r);
            b = max(b, r);
            c = min(c, o);
            d = max(d, o);
            for(int dr {-1}; dr <= 1; dr++){
              for(int dc {-1}; dc <= 1; dc++){
                int nr = r + dr;
                int nc = o + dc;
                if(nr >= 0 && nr < n && nc >= 0 && nc < n && field[nr][nc] == 1){
                  field[nr][nc] = 0;
                  q.push({nr, nc});
                }
              }
            }
        }
        if((b - a > 0 && d - c > 0) || (sz != (b - a + d - c + 1))){
          return false;
        }
        if(sz < 1 || sz > 4){
          return false;
        }
        ships[sz]++;
      }
    }
  }
  return ships[4] == 1 && ships[3] == 2 && ships[2] == 3 && ships[1] == 4;
}