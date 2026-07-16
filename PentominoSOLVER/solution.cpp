// #include <vector>
// #include <string>
#include <bits/stdc++.h>
using namespace std;

struct Solver{
//   static std::vector<std::string> solve(const std::string& entry) {
//     /// your code here...
//     return {""};
//   }
    struct DLX {
        int num_cols;
        int sz;
        vector<int> L, R, U, D, Row, Col, S;
        vector<int> current_solution;
        vector<vector<int>> all_solutions;        
        DLX(int c) {
            num_cols = c;
            int estimated_nodes = 150000;
            L.reserve(estimated_nodes);
            R.reserve(estimated_nodes);
            U.reserve(estimated_nodes);
            D.reserve(estimated_nodes);
            Row.reserve(estimated_nodes);
            Col.reserve(estimated_nodes);            
            sz = num_cols + 1;
            L.resize(sz);
            R.resize(sz);
            U.resize(sz);
            D.resize(sz);
            Row.resize(sz, 0);
            Col.resize(sz, 0);
            S.assign(sz, 0);            
            for (int i = 0; i <= num_cols; i++) {
                L[i] = i - 1;
                R[i] = i + 1;
                U[i] = i;
                D[i] = i;
            }
            L[0] = num_cols;
            R[num_cols] = 0;
        }
        
        void add_row(int r, const vector<int>& columns) {
            if (columns.empty()) return;
            int first = sz;
            for (int c : columns) {
                L.push_back(sz - 1);
                R.push_back(sz + 1);
                D.push_back(c);
                U.push_back(U[c]);
                Row.push_back(r);
                Col.push_back(c);
                D[U[c]] = sz;
                U[c] = sz;
                S[c]++;
                sz++;
            }
            L[first] = sz - 1;
            R[sz - 1] = first;
        }
        
        void cover(int c) {
            L[R[c]] = L[c];
            R[L[c]] = R[c];
            for (int i = D[c]; i != c; i = D[i]) {
                for (int j = R[i]; j != i; j = R[j]) {
                    U[D[j]] = U[j];
                    D[U[j]] = D[j];
                    S[Col[j]]--;
                }
            }
        }
        
        void uncover(int c) {
            for (int i = U[c]; i != c; i = U[i]) {
                for (int j = L[i]; j != i; j = L[j]) {
                    U[D[j]] = j;
                    D[U[j]] = j;
                    S[Col[j]]++;
                }
            }
            L[R[c]] = c;
            R[L[c]] = c;
        }
        
        void search() {
            if (R[0] == 0) {
                all_solutions.push_back(current_solution);
                return;
            }
            int c = R[0];
            for (int i = R[0]; i != 0; i = R[i]) {
                if (S[i] < S[c]) c = i;
            }
            if (S[c] == 0){
                return;
            }            
            cover(c);
            for (int i = D[c]; i != c; i = D[i]) {
                current_solution.push_back(Row[i]);
                for (int j = R[i]; j != i; j = R[j]){
                    cover(Col[j]);
                }                
                search();                
                for (int j = L[i]; j != i; j = L[j]){
                    uncover(Col[j]);
                }
                current_solution.pop_back();
            }
            uncover(c);
        }
    };

    static vector<vector<pair<int, int>>> get_pentominoes(int id) {
        static bool initialized = false;
        static vector<vector<pair<int, int>>> pentominoes[12];
        if (!initialized) {
            vector<pair<int, int>> base_shapes[12] = {
                {{0,1}, {0,2}, {1,0}, {1,1}, {2,1}}, // F
                {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}}, // I
                {{0,0}, {1,0}, {2,0}, {3,0}, {3,1}}, // L
                {{0,1}, {1,1}, {2,0}, {2,1}, {3,0}}, // N
                {{0,0}, {0,1}, {1,0}, {1,1}, {2,0}}, // P
                {{0,0}, {0,1}, {0,2}, {1,1}, {2,1}}, // T
                {{0,0}, {0,2}, {1,0}, {1,1}, {1,2}}, // U
                {{0,0}, {1,0}, {2,0}, {2,1}, {2,2}}, // V
                {{0,0}, {1,0}, {1,1}, {2,1}, {2,2}}, // W
                {{0,1}, {1,0}, {1,1}, {1,2}, {2,1}}, // X
                {{0,1}, {1,0}, {1,1}, {2,1}, {3,1}}, // Y
                {{0,0}, {0,1}, {1,1}, {2,1}, {2,2}}  // Z
            };
            auto rotate = [](const vector<pair<int, int>>& p) {
                vector<pair<int, int>> res;
                for (auto cell : p){
                    res.push_back({cell.second, -cell.first});
                }
                return res;
            };
            auto reflect = [](const vector<pair<int, int>>& p) {
                vector<pair<int, int>> res;
                for (auto cell : p){
                    res.push_back({cell.first, -cell.second});
                }
                return res;
            };
            auto normalize = [](const vector<pair<int, int>>& p) {
                int min_r = 1e9, min_c = 1e9;
                for (auto cell : p) {
                    min_r = min(min_r, cell.first);
                    min_c = min(min_c, cell.second);
                }
                vector<pair<int, int>> res;
                for (auto cell : p) {
                    res.push_back({cell.first - min_r, cell.second - min_c});
                }
                sort(res.begin(), res.end());
                return res;
            };            
            for (int i = 0; i < 12; i++) {
                set<vector<pair<int, int>>> unq;
                vector<pair<int, int>> cur = base_shapes[i];
                for (int r = 0; r < 4; r++) {
                    unq.insert(normalize(cur));
                    unq.insert(normalize(reflect(cur)));
                    cur = rotate(cur);
                }
                for (auto& config : unq) {
                    pentominoes[i].push_back(config);
                }
            }
            initialized = true;
        }
        return pentominoes[id];
    }

    static vector<string> solve(const string& entry) {
        vector<string> board;
        string cur = "";
        for (char c : entry) {
            if (c == '\n') {
                board.push_back(cur);
                cur = "";
            } else {
                cur += c;
            }
        }
        if (!cur.empty()){
            board.push_back(cur);
        }        
        int H = board.size();
        if (H == 0){
            return {};
        }
        int W = board[0].size();
        vector<vector<int>> cell_id(H, vector<int>(W, 0));
        int num_cells = 0;
        vector<pair<int, int>> id_to_cell;
        id_to_cell.push_back({-1, -1});
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (board[r][c] != '-') {
                    num_cells++;
                    cell_id[r][c] = num_cells;
                    id_to_cell.push_back({r, c});
                }
            }
        }        
        string TYPE_CHARS = "FILNPTUVWXYZ";
        int num_cols = num_cells + 12;
        DLX dlx(num_cols);        
        struct Placement {
            int type_id;
            vector<int> cell_ids;
        };
        vector<Placement> placements;
        int row_id = 0;        
        for (int t = 0; t < 12; t++) {
            placements.push_back({t, {}});
            dlx.add_row(row_id++, {num_cells + 1 + t});
            auto configs = get_pentominoes(t);
            for (auto& config : configs) {
                for (int r = 0; r < H; r++) {
                    for (int c = 0; c < W; c++) {
                        bool ok = true;
                        vector<int> cols;
                        cols.push_back(num_cells + 1 + t);
                        vector<int> cells;
                        for (auto& p : config) {
                            int rr = r + p.first;
                            int cc = c + p.second;
                            if (rr < 0 || rr >= H || cc < 0 || cc >= W) {
                                ok = false;
                                break;
                            }
                            char ch = board[rr][cc];
                            if (ch == '-') {
                                ok = false;
                                break;
                            }
                            if (ch != '*' && ch != TYPE_CHARS[t]) {
                                ok = false;
                                break;
                            }
                            int cid = cell_id[rr][cc];
                            cols.push_back(cid);
                            cells.push_back(cid);
                        }
                        if (ok) {
                            placements.push_back({t, cells});
                            dlx.add_row(row_id++, cols);
                        }
                    }
                }
            }
        }        
        dlx.search();        
        vector<string> res;
        for (auto& sol : dlx.all_solutions) {
            vector<string> b = board;
            for (int r = 0; r < H; r++) {
                for (int c = 0; c < W; c++) {
                    if (b[r][c] == '*') b[r][c] = '.';
                }
            }            
            for (int rid : sol) {
                auto& p = placements[rid];
                if (p.cell_ids.empty()){
                    continue;
                }
                char ch = TYPE_CHARS[p.type_id];
                for (int cid : p.cell_ids) {
                    auto cell = id_to_cell[cid];
                    b[cell.first][cell.second] = ch;
                }
            }            
            string s = "";
            for (int i = 0; i < H; ++i) {
                s += b[i];
                if (i < H - 1) s += "\n";
            }
            res.push_back(s);
        }        
        return res;
    }
};