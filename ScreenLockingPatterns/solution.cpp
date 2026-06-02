// Feel free to write and use any additional functions, variables, objects, etc. as you wish
#include <bits/stdc++.h>
using namespace std;

unsigned int countPatternsFrom(char firstDot, unsigned short length){
    // Your code here
    if (length < 1 || length > 9){
        return 0;
    }
    int skip[9][9];
    for (int i {0}; i < 9; i++){
        for (int j {0}; j < 9; j++){
            skip[i][j] = -1;
        }
    }
    skip[0][2] = skip[2][0] = 1;
    skip[0][6] = skip[6][0] = 3;
    skip[0][8] = skip[8][0] = 4;
    skip[1][7] = skip[7][1] = 4;
    skip[2][6] = skip[6][2] = 4;
    skip[2][8] = skip[8][2] = 5;
    skip[3][5] = skip[5][3] = 4;
    skip[6][8] = skip[8][6] = 7;
    auto dfs = [&](auto& self, int curr, int len, int vis) -> int{
        if (len == 1){
            return 1;
        }
        vis |= (1 << curr);
        int count {0};
        for (int next {0}; next < 9; next++){
            if (!(vis & (1 << next))){
                int s = skip[curr][next];
                if (s == -1 || (vis & (1 << s))){
                    count += self(self, next, len - 1, vis);
                }
            }
        }
        return count;
    };
    return dfs(dfs, firstDot - 'A', length, 0);
}