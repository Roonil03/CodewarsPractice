// #include <vector>
#include <bits/stdc++.h>
using namespace std;

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &clues)
{
//     return {};
    vector<array<int, 7>> perms;
    perms.reserve(5040);
    array<int, 7> p = {1, 2, 3, 4, 5, 6, 7};
    do{
        perms.push_back(p);
    } while(next_permutation(p.begin(), p.end()));
    auto vis = [](const array<int, 7>& a){
        int v {0}, m {0};
        for(int x : a){
            if(x > m){
                v++;
                m = x;
            }
        }
        return v;
    };
    vector<int> rp[7];
    vector<vector<vector<int>>> col_opts(8, vector<vector<int>>(7));
    for(int step {1}; step <= 7; ++step){
        for(int c {0}; c < 7; c++){
            col_opts[step][c].reserve(5040);
        }
    }
    for(int i {0}; i < 5040; i++){
        int lv = vis(perms[i]);
        auto rev = perms[i];
        reverse(rev.begin(), rev.end());
        int rv = vis(rev);
        for(int r {0}; r < 7; r++){
            int cl = clues[27 - r], cr = clues[7 + r];
            if((!cl || cl == lv) && (!cr || cr == rv)){
                rp[r].push_back(i);
            }
        }
        for(int c {0}; c < 7; c++){
            int ct = clues[c], cb = clues[20 - c];
            if((!ct || ct == lv) && (!cb || cb == rv)){
                col_opts[0][c].push_back(i);
            }
        }
    }
    int order[7];
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order), [&](int a, int b){
        return rp[a].size() < rp[b].size();
    });
    vector<vector<int>> res(7, vector<int>(7));
    auto dfs = [&](auto& self, int step) -> bool {
        if(step == 7){
            return true;
        }
        int r = order[step];
        for(int id : rp[r]){
            const auto& pp = perms[id];
            bool ok = true;
            for(int c {0}; c < 7; c++){
                col_opts[step + 1][c].clear();
                for(int i : col_opts[step][c]){
                    if(perms[i][r] == pp[c]){
                        col_opts[step + 1][c].push_back(i);
                    }
                }
                if(col_opts[step + 1][c].empty()){
                    ok = false;
                    break;
                }
            }
            if(ok){
                for(int c {0}; c < 7; c++){
                    res[r][c] = pp[c];
                }
                if(self(self, step + 1)){
                    return true;
                }
            }
        }
        return false;
    };
    dfs(dfs, 0);
    return res;
}
