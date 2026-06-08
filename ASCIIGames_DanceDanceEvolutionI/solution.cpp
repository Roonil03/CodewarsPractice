// #include <string>
#include <bits/stdc++.h>
using namespace std;

std::wstring dance(const std::wstring &map_str)
{
//   return L"";
    vector<wstring> grid;
    wstring row_str = L"";
    for(wchar_t ch : map_str){
        if(ch == L'\n' || ch == L'\r'){
            if(!row_str.empty()){
                grid.push_back(row_str);
                row_str = L"";
            }
        } else {
            row_str.push_back(ch);
        }
    }
    if(!row_str.empty()){
        grid.push_back(row_str);
    }
    int R = grid.size();
    int C = R > 0 ? grid[0].size() : 0;
    int sr = -1, sc = -1;
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            if(grid[i][j] == L'S'){
                sr = i;
                sc = j;
            }
        }
    }
    wstring arr = L"↑↗→↘↓↙←↖";
    int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
    vector<vector<bool>> vis(R, vector<bool>(C, false));
    wstring best = L"", cur = L"";
    auto valid = [](int d1, int d2){
        if (d1 == -1 || d2 == -1){
            return true;
        }
        int diff = abs(d1 - d2);
        return min(diff, 8 - diff) <= 2;
    };
    auto get_dir = [&](wchar_t ch){
        auto p = arr.find(ch);
        return p == wstring::npos ? -1 : (int)p;
    };
    auto dfs = [&](auto& self, int cr, int cc) -> void{
        if (cr == sr && cc == sc && !cur.empty()){
            if (cur.length() > best.length()){
                best = cur;
            }
            return;
        }
        int cd = get_dir(grid[cr][cc]);
        for (int d = 0; d < 8; ++d) {
            int nr = cr + dr[d], nc = cc + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C){
                continue;
            }
            if (grid[nr][nc] != L'S' && vis[nr][nc]){
                continue;
            }
            int nd = get_dir(grid[nr][nc]);
            if (valid(cd, d) && valid(nd, d)){
                if (grid[nr][nc] != L'S'){
                    vis[nr][nc] = true;
                }
                cur.push_back(arr[d]);
                self(self, nr, nc);
                cur.pop_back();
                if (grid[nr][nc] != L'S'){
                    vis[nr][nc] = false;
                }
            }
        }
    };
    if (sr != -1 && sc != -1){
        dfs(dfs, sr, sc);
    }
    return best;
}