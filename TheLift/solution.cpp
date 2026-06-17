// #include <vector>
#include <bits/stdc++.h>
using namespace std;

std::vector<int> the_lift(const std::vector<std::vector<int>> &queues, int capacity) {
//   return {};
    vector<vector<int>> q = queues;
    vector<int> res ={0}, pass;
    int cur = 0, dir = 1;
    while (true){
        bool fg = false;
        auto it = remove(pass.begin(), pass.end(), cur);
        if (it != pass.end()){
            fg = true;
            pass.erase(it, pass.end());
        }
        vector<int> rem;
        bool f1 = false;
        for (int d : q[cur]){
            if ((dir == 1 && d > cur) || (dir == -1 && d < cur)){
                f1 = true;
                if (pass.size() < capacity){
                    pass.push_back(d);
                    fg = true;
                } else{
                    rem.push_back(d);
                }
            } else{
                rem.push_back(d);
            }
        }
        if (f1){
            fg = true;
        }
        q[cur] = rem;
        if (fg && res.back() != cur){
            res.push_back(cur);
        }
        auto h1 = [&](){
            if (dir == 1){
                for (int p : pass) if (p > cur){
                    return true;
                }
                for (size_t f = cur + 1; f < q.size(); f++){
                    if (!q[f].empty()){
                        return true;
                    }
                }
            } else{
                for (int p : pass){
                    if (p < cur){
                        return true;
                    }
                }
                for (int f = cur - 1; f >= 0; f--){
                    if (!q[f].empty()){
                        return true;
                    }
                }
            }
            return false;
        };
        if (h1()){
            cur += dir;
        } else{
            bool any = !pass.empty();
            for (auto& f : q){
                if (!f.empty()){
                    any = true;
                }
            }
            if (any){
                dir = -dir;
            } else{
                if (cur == 0){
                    break;
                }
                dir = (cur > 0) ? -1 : 1;
                cur += dir;
            }
        }
    }
    if (res.back() != 0){
        res.push_back(0);
    }
    return res;
}