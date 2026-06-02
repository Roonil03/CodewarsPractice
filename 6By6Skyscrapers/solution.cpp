#include <bits/stdc++.h>
using namespace std;

std::vector<std::vector<int>> SolvePuzzle(const std::vector<int> &clues)
{
    vector<vector<int>> perms;
    vector<int> p ={1, 2, 3, 4, 5, 6};
    do{
        perms.push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    vector<vector<int>> rw[6];
    for (int i {0}; i < 6; i++){
        int lc = clues[23 - i], rc = clues[6 + i];
        for (auto &perm : perms){
            int vl {0}, ml {0}, vr {0}, mr {0};
            for (int j {0}; j < 6; j++){
                if (perm[j] > ml){
                    ml = perm[j];
                    vl++;
                }
                if (perm[5 - j] > mr){
                    mr = perm[5 - j];
                    vr++;
                }
            }
            if ((lc == 0 || vl == lc) && (rc == 0 || vr == rc)){
                rw[i].push_back(perm);
            }
        }
    }
    vector<vector<int>> grid(6, vector<int>(6));
    vector<int> mk(6, 0);
    vector<vector<int>> res;
    auto check_cols = [&](){
        for (int j {0}; j < 6; j++){
            int tc = clues[j], bc = clues[17 - j];
            if (tc == 0 && bc == 0){
                continue;
            }
            int vt {0}, mt {0}, vb {0}, mb {0};
            for (int i {0}; i < 6; i++){
                if (grid[i][j] > mt){
                    mt = grid[i][j];
                    vt++;
                }
                if (grid[5 - i][j] > mb){
                    mb = grid[5 - i][j];
                    vb++;
                }
            }
            if ((tc != 0 && vt != tc) || (bc != 0 && vb != bc)){
                return false;
            }
        }
        return true;
    };
    auto dfs = [&](auto& self, int r) -> bool{
        if (r == 6){
            if (check_cols()){
                res = grid;
                return true;
            }
            return false;
        }
        for (auto &row : rw[r]){
            bool ok = true;
            for (int j {0}; j < 6; j++){
                if (mk[j] & (1 << row[j])){
                    ok = false;
                    break;
                }
            }
            if (!ok){
                continue;
            }
            for (int j {0}; j < 6; j++){
                mk[j] |= (1 << row[j]);
            }
            grid[r] = row;
            for (int j {0}; j < 6; j++){
                int tc = clues[j], bc = clues[17 - j];
                int vt {0}, mt {0};
                for (int i {0}; i <= r; ++i){
                    if (grid[i][j] > mt){
                        mt = grid[i][j];
                        vt++;
                    }
                    if (grid[i][j] == 6 && bc != 0 && (6 - i) < bc){
                        ok = false;
                        break;
                    }
                }
                if (!ok || (tc != 0 && (vt > tc || vt + (5 - r) < tc))){
                    ok = false;
                    break;
                }
            }
            if (!ok){
                for (int j {0}; j < 6; j++){
                    mk[j] &= ~(1 << row[j]);
                }
                continue;
            }
            if (self(self, r + 1)){
                return true;
            }
            for (int j {0}; j < 6; j++){
                mk[j] &= ~(1 << row[j]);
            }
        }
        return false;
    };
    dfs(dfs, 0);
    return res;
}