/*

NOTE : You are provided with these functions

std::string join(const std::string &sep, const std::vector<std::string> &to_join)

std::vector<std::string> split(const std::string &to_split, char separator = '\n')
*/

#include<bits/stdc++.h>
using namespace std;

std::vector<std::string> cut(const std::string &cake)
{
//   return {};
    vector<string> g = split(cake, '\n');
    while (!g.empty() && g.back().empty()){
        g.pop_back();
    }
    if (g.empty()){
        return{};
    }
    int h = g.size(), w = g[0].size(), n = 0;
    for (auto& r : g){
        for (char c : r){
            if (c == 'o'){
                n++;
            }
        }
    }
    if (!n || (w * h) % n){
        return{};
    }
    int s = w * h / n;
    vector<pair<int, int>> f;
    for (int i = w; i >= 1; i--){
        if (s % i == 0 && s / i <= h){
            f.push_back({i, s / i});
        }
    }
    vector<vector<bool>> vis(h, vector<bool>(w, false));
    vector<string> res;
    function<bool()> dfs = [&](){
        int r = -1, c = -1;
        for (int i = 0; i < h && r < 0; i++){
            for (int j = 0; j < w && r < 0; j++){
                if (!vis[i][j]){
                    r = i;
                    c = j;
                }
            }
        }
        if (r < 0){
            return true;
        }
        for (auto [pw, ph] : f){
            if (r + ph > h || c + pw > w){
                continue;
            }
            int o = 0; bool ok = true;
            for (int i = r; i < r + ph && ok; i++){
                for (int j = c; j < c + pw && ok; j++){
                    if (vis[i][j]){
                        ok = false;
                    } else if (g[i][j] == 'o'){
                        o++;
                    }
                }
            }
            if (ok && o == 1){
                for (int i = r; i < r + ph; i++){
                    for (int j = c; j < c + pw; j++){
                        vis[i][j] = true;
                    }
                }
                vector<string> p;
                for (int i = r; i < r + ph; i++){
                    p.push_back(g[i].substr(c, pw));
                }
                res.push_back(join("\n", p));
                if (dfs()){
                    return true;
                }
                res.pop_back();
                for (int i = r; i < r + ph; i++){
                    for (int j = c; j < c + pw; j++){
                        vis[i][j] = false;
                    }
                }
            }
        }
        return false;
    };
    return dfs() ? res : vector<string>{};
}