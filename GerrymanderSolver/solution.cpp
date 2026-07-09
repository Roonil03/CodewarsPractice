/*
NOTE : You are provided with these functions

std::string join(const std::string &sep, const std::vector<std::string> &to_join)

std::vector<std::string> split(const std::string &to_split, char separator = '\n')
*/
#include <bits/stdc++.h>
using namespace std;

std::string gerrymander(const std::string &map)
{
    vector<string> row = split(map, '\n');
    int g {0};
    for(int i {0}; i < 5; i++){
      for(int j {0}; j < 5; j++){
        if(row[i][j] == 'O'){
          g |= (1 << (i * 5 + j));
        }
      }
    }
    int grid_o = g;
    int adj[25];
    for(int i {0}; i < 25; i++){
      int r = i / 5, c = i % 5;
      int mask = 0;
      if(r > 0){
        mask |= (1 << (i - 5));
      }
      if(r < 4){
        mask |= (1 << (i + 5));
      }
      if(c > 0){
        mask |= (1 << (i - 1));
      }
      if(c < 4){
        mask |= (1 << (i + 1));
      }
      adj[i] = mask;
    }
    auto check_components = [&](int rem) {
      while (rem > 0) {
        int start = __builtin_ctz(rem);
        int comp_mask = 0;
        int next_frontier = (1 << start);
        while (next_frontier > 0) {
          comp_mask |= next_frontier;
          int new_frontier = 0;
          int f = next_frontier;
          while (f > 0) {
            int c = __builtin_ctz(f);
            f &= f - 1;
            new_frontier |= adj[c];
          }
          next_frontier = new_frontier & rem & ~comp_mask;
        }
        if (__builtin_popcount(comp_mask) % 5 != 0) return false;
        rem ^= comp_mask;
      }
      return true;
    };
  vector<int> district_assignments(25, 0);
  auto solve = [&](auto& self, int dist_id, int empty_mask, int win_count) -> bool {
    if (dist_id == 6) return win_count >= 3;
    if (win_count + (5 - dist_id + 1) < 3) return false;
    if (__builtin_popcount(empty_mask & grid_o) < 3 * (3 - win_count)) return false;
    int start = __builtin_ctz(empty_mask);
    vector<pair<int, int>> valid_pents;
    unordered_set<int> seen;
    auto find_pents = [&](auto& sf, int mask, int frontier, int o_cnt, int size) -> void {
      if (size == 5) {
        valid_pents.push_back({mask, o_cnt});
        return;
      }
      int f = frontier;
      while (f > 0) {
        int c = __builtin_ctz(f);
        f &= f - 1;
        int nmask = mask | (1 << c);
        if (!seen.insert(nmask).second) continue;
        int nfrontier = (frontier | adj[c]) & empty_mask & ~nmask;
        sf(sf, nmask, nfrontier, o_cnt + ((grid_o >> c) & 1), size + 1);
      }
    };
    seen.insert(1 << start);
    find_pents(find_pents, 1 << start, adj[start] & empty_mask, (grid_o >> start) & 1, 1);
    sort(valid_pents.begin(), valid_pents.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
      int a_is_win = (a.second >= 3) ? 1 : 0;
      int b_is_win = (b.second >= 3) ? 1 : 0;
      if (win_count < 3) return a_is_win > b_is_win;
      return a_is_win < b_is_win;
    });
    for (const auto& pent : valid_pents) {
      int mask = pent.first;
      int o_cnt = pent.second;
      int next_win = win_count + (o_cnt >= 3 ? 1 : 0);
      int next_mask = empty_mask ^ mask;
      if (!check_components(next_mask)) continue;
      if (self(self, dist_id + 1, next_mask, next_win)) {
        for (int i = 0; i < 25; ++i) {
          if ((mask >> i) & 1) district_assignments[i] = dist_id;
        }
        return true;
      }
    }
    return false;
  };
  if (solve(solve, 1, (1 << 25) - 1, 0)) {
    vector<string> result_rows(5, string(5, ' '));
    for (int i = 0; i < 25; ++i) {
      result_rows[i / 5][i % 5] = '0' + district_assignments[i];
    }
    return join("\n", result_rows);
  }
  return "";
}