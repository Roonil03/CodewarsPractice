// #include <vector>
// #include <string>
#include <bits/stdc++.h>
using namespace std;

std::vector<std::string> break_piece(const std::string &shape)
{
//   return {};
    vector<string> g;
    stringstream ss(shape);
    string l;
    int mw {0};
    while (getline(ss, l)){
        if (!l.empty() && l.back() == '\r'){
            l.pop_back();
        }
        g.push_back(l);
        mw = max(mw, (int)l.size());
    }
    int hh = g.size() + 2, ww = mw + 2;
    vector<string> grd(hh, string(ww, ' '));
    for (int r {0}; r < g.size();r++){
        for (int c {0}; c < g[r].size(); c++){
            grd[r + 1][c + 1] = g[r][c];
        }
    }    
    vector<vector<bool>> vis(hh, vector<bool>(ww, false));
    auto bfs = [&](int sr, int sc){
        queue<pair<int, int>> q;
        q.push({sr, sc});
        vis[sr][sc] = true;
        vector<pair<int, int>> res;
        while (!q.empty()){
            auto [r, c] = q.front(); q.pop();
            res.push_back({r, c});
            int dr[] ={-1, 1, 0, 0}, dc[] ={0, 0, -1, 1};
            for (int i {0}; i < 4; ++i){
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < hh && nc >= 0 && nc < ww && !vis[nr][nc] && grd[nr][nc] == ' '){
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return res;
    };    
    bfs(0, 0);
    vector<string> res;    
    for (int r {0}; r < hh;r++){
        for (int c {0}; c < ww; c++){
            if (grd[r][c] == ' ' && !vis[r][c]){
                auto sp = bfs(r, c);
                set<pair<int, int>> bnd;
                int mr = 1e9, Mr = -1e9, mc = 1e9, Mc = -1e9;
                for (auto [sr, sc] : sp){
                    for (int dr = -1; dr <= 1; ++dr){
                        for (int dc = -1; dc <= 1; ++dc){
                            int nr = sr + dr, nc = sc + dc;
                            if (grd[nr][nc] != ' '){
                                bnd.insert({nr, nc});
                            }
                        }
                    }
                }
                for (auto [br, bc] : bnd){
                    mr = min(mr, br); Mr = max(Mr, br);
                    mc = min(mc, bc); Mc = max(Mc, bc);
                }
                vector<string> p(Mr - mr + 1, string(Mc - mc + 1, ' '));
                for (auto [br, bc] : bnd){
                    bool hh = bnd.count({br, bc - 1}) || bnd.count({br, bc + 1});
                    bool hv = bnd.count({br - 1, bc}) || bnd.count({br + 1, bc});
                    p[br - mr][bc - mc] = (hh && hv) ? '+' : (hh ? '-' : (hv ? '|' : grd[br][bc]));
                }
                string ps = "";
                for (int i {0}; i < p.size(); ++i){
                    while (!p[i].empty() && p[i].back() == ' '){
                        p[i].pop_back();
                    }
                    ps += p[i] + (i + 1 == p.size() ? "" : "\n");
                }
                res.push_back(ps);
            }
        }
    }
    return res;
}