// #include <string>
// #include <utility>
#include <bits/stdc++.h>
using namespace std;

namespace nQueens
{

    std::string solveNQueens(int n, std::pair<int, int> mandatoryQueenCoordinates)
    {
//       return "";
        int mc = mandatoryQueenCoordinates.first, mr = mandatoryQueenCoordinates.second;
        vector<int> q(n);
        mt19937 rng(1337);
        for(int i{0}; i < 50; i++){
            fill(q.begin(), q.end(), 0);
            vector<int> r(n, 0), d1(2 * n, 0), d2(2 * n, 0);
            q[mc] = mr;
            r[mr]++;
            d1[mr + mc]++;
            d2[mr - mc + n]++;
            for(int j{0}; j < n; j++){
                if(j == mc){
                    continue;
                }
                int a = 1e9;
                vector<int> br;
                for(int k{0}; k < n; k++){
                    int conf = r[k] + d1[j + k] + d2[k - j + n];
                    if(conf < a){
                        a = conf;
                        br = {k};
                    } else if(conf == a){
                        br.push_back(k);
                    }
                }
                int d = br[rng() % br.size()];
                q[j] = d;
                r[d]++;
                d1[j + d]++;
                d2[d - j + n]++;
            }
            int it = 100 * n, iter{0};
            for(; iter < it; iter++){
                vector<int> w;
                int a{0};
                for(int j{0}; j < n; j++){
                    if(j == mc){
                        continue;
                    }
                    int d = q[j];
                    int conf = r[d] + d1[d + j] + d2[d - j + n] - 3;
                    if(conf > a){
                        a = conf;
                        w = {j};
                    } else if(conf > 0 && conf == a){
                        w.push_back(j);
                    }
                }
                if(a == 0){
                    break;
                }
                int c = w[rng() % w.size()];
                int o = q[c];
                r[o]--;
                d1[o + c]--;
                d2[o - c + n]--;
                int b = 1e9;
                vector<int> br;
                for(int j{0}; j < n; j++){
                    int conf = r[j] + d1[j + c] + d2[j - c + n];
                    if(conf < b){
                        b = conf;
                        br = {j};
                    } else if(conf == b){
                        br.push_back(j);
                    }
                }
                int j = br[rng() % br.size()];
                q[c] = j;
                r[j]++;
                d1[j + c]++;
                d2[j - c + n]++;
            }
            if(iter < it){
                string s(n * (n + 1), '.');
                for(int i{0}; i < n; i++){
                    s[i * (n + 1) + n] = '\n';
                }
                for(int i{0}; i < n; i++){
                    s[q[i] * (n + 1) + i] = 'Q';
                }
                return s;
            }
        }
        return "";
    }
}