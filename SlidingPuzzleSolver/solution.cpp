#include <bits/stdc++.h>
using namespace std;

std::vector<int> slide_puzzle(const std::vector<std::vector<int>> &arr)
{
//   return std::vector<int>();
    int N = arr.size(), r0 {0}, zr = -1, zc = -1, inv {0};
    vector<int> flat;
    for (int i {0}; i < N; i++){
        for (int j {0}; j < N; j++){
            if (arr[i][j]){
                flat.push_back(arr[i][j]);
            } else{
                r0 = i;
                zr = i;
                zc = j;
            }
        }
    }
    for (size_t i {0}; i < flat.size(); i++){
        for (size_t j = i + 1; j < flat.size(); j++){
            if (flat[i] > flat[j]){
                inv++;            
            }
        }
    }
    if ((inv + (N % 2 == 0 ? N - 1 - r0 : 0)) % 2 != 0){
        return{0};
    }
    vector<vector<int>> board = arr;
    vector<vector<bool>> locked(N, vector<bool>(N, false));
    vector<int> res;
    auto bfs = [&](vector<int> targets, vector<int> goals){
        int K = targets.size();
        vector<int> unlocked, cid(N * N, -1);
        for (int i {0}; i < N * N; i++){
            if (!locked[i / N][i % N]){
                cid[i] = unlocked.size();
                unlocked.push_back(i);
            }
        }
        int U = unlocked.size(), max_states = 1;
        for (int i {0}; i <= K; i++){
            max_states *= U;
        }
        vector<int> parent(max_states, -1), action(max_states, -1), p(K);
        int p0 {-1};
        for (int i {0}; i < N * N; i++){
            if (board[i / N][i % N] == 0){
                p0 = i;
            }
            for (int j {0}; j < K; j++){
                if (board[i / N][i % N] == targets[j]){
                    p[j] = i;
                }
            }
        }        
        auto encode = [&](vector<int>& p, int p0){
            int res = cid[p0];
            for (int i {0}; i < K; i++){
                res = res * U + cid[p[i]];
            }
            return res;
        };        
        int start_state = encode(p, p0);
        vector<int> q; q.reserve(max_states);
        q.push_back(start_state);
        parent[start_state] = start_state;        
        int goal_state = -1, head {0};
        vector<int> cur_p(K);        
        while (head < q.size()){
            int curr = q[head++];
            int temp = curr;
            for (int i = K - 1; i >= 0; i--){
                cur_p[i] = unlocked[temp % U];
                temp /= U;
            }
            int cur_p0 = unlocked[temp];            
            bool ok = true;
            for (int i {0}; i < K; i++){
                if (cur_p[i] != goals[i]){
                    ok = false;
                }
            }
            if (ok){
                goal_state = curr;
                break;
            }            
            int r = cur_p0 / N, c = cur_p0 % N;
            int dr[] ={-1, 1, 0, 0}, dc[] ={0, 0, -1, 1};
            for (int d {0}; d < 4; d++){
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N && !locked[nr][nc]){
                    int np0 = nr * N + nc;
                    vector<int> np = cur_p;
                    for (int i {0}; i < K; i++){
                        if (np[i] == np0){
                            np[i] = cur_p0;
                        }
                    }
                    int nstate = encode(np, np0);
                    if (parent[nstate] == -1){
                        parent[nstate] = curr;
                        action[nstate] = np0;
                        q.push_back(nstate);
                    }
                }
            }
        }        
        vector<int> path;
        int curr = goal_state;
        while (curr != start_state){
            path.push_back(action[curr]);
            curr = parent[curr];
        }
        for (int i = path.size() - 1; i >= 0; i--){
            int np0 = path[i];
            int r = np0 / N, c = np0 % N;
            res.push_back(board[r][c]);
            swap(board[zr][zc], board[r][c]);
            zr = r; zc = c;
        }
    };
    for (int r {0}; r < N - 2; r++){
        for (int c {0}; c < N - 2; c++){
            bfs({r * N + c + 1},{r * N + c});
            locked[r][c] = true;
        }
        bfs({r * N + N - 1, r * N + N},{r * N + N - 2, r * N + N - 1});
        locked[r][N - 2] = true;
        locked[r][N - 1] = true;
    }
    for (int c {0}; c < N - 2; c++){
        bfs({(N - 2) * N + c + 1, (N - 1) * N + c + 1},{(N - 2) * N + c, (N - 1) * N + c});
        locked[N - 2][c] = true;
        locked[N - 1][c] = true;
    }
    bfs({(N - 2) * N + N - 1, (N - 2) * N + N, (N - 1) * N + N - 1},{(N - 2) * N + N - 2, (N - 2) * N + N - 1, (N - 1) * N + N - 2});        
    return res;
}