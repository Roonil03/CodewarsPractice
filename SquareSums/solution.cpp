// #include <vector>
#include <bits/stdc++.h>
using namespace std;

std::vector<int> square_sums_row(int n)
{
    if (n < 1){
        return{};
    }
    if (n == 1){
        return{1};
    }
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i {1}; i <= n; i++){
        for (int j {1}; j * j <= 2 * n; j++){
            int sq = j * j;
            int sib = sq - i;
            if (sib > 0 && sib <= n && sib != i){
                adj[i].push_back(sib);
                deg[i]++;
            }
        }
    }
    int c1 {0};
    for (int i {1}; i <= n; i++){
        if (deg[i] == 0){
            return{};
        }
        if (deg[i] == 1){
            c1++;
        }
    }
    if (c1 > 2){
        return{};
    }
    vector<int> path;
    vector<bool> vis(n + 1, false);
    auto dfs = [&](auto& self, int u, int count) -> bool{
        path.push_back(u);
        vis[u] = true;
        if (count == n){
            return true;
        }
        vector<pair<int, int>> next_nodes;
        for (int v : adj[u]){
            if (!vis[v]){
                int c {0};
                for (int w : adj[v]){
                    if (!vis[w]){
                        c++;
                    }
                }
                next_nodes.push_back({c, v});
            }
        }
        sort(next_nodes.begin(), next_nodes.end());
        for (auto& p : next_nodes){
            if (self(self, p.second, count + 1)){
                return true;
            }
        }
        vis[u] = false;
        path.pop_back();
        return false;
    };
    vector<pair<int, int>> start_nodes;
    for (int i {1}; i <= n; i++){
        start_nodes.push_back({deg[i], i});
    }
    sort(start_nodes.begin(), start_nodes.end());
    for (auto& p : start_nodes){
        if (dfs(dfs, p.second, 1)){
            return path;
        }
    }
    return{};
}