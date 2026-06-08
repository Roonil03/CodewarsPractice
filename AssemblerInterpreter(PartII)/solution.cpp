// #include <string>
#include <bits/stdc++.h>
using namespace std;

std::string assembler_interpreter(std::string program) {
//   return "";
    vector<pair<string, string>> insts;
    map<string, int> labels, reg;
    stringstream ss(program);
    string line, out;
    while (getline(ss, line)){
        string c;
        bool in = false;
        for (char ch : line){
            if (ch == '\''){
                in = !in;
            }
            if (!in && ch == ';') {
                break;
            }
            c += ch;
        }
        int s {0}, e = (int)c.size() - 1;
        while (s <= e && isspace(c[s])){
            s++;
        }
        while (e >= s && isspace(c[e])){
            e--;
        }
        if (s > e){
            continue;
        }
        c = c.substr(s, e - s + 1);
        size_t id = c.find(':');
        bool isl = id != string::npos;
        for (size_t i {0}; isl && i < id; ++i){
            if (isspace(c[i]) || c[i] == '\''){
                isl = false;
            }
        }
        if (isl){
            labels[c.substr(0, id)] = insts.size();
            c = c.substr(id + 1);
            s = 0;
            e = (int)c.size() - 1;
            while (s <= e && isspace(c[s])){
                s++;
            }
            while (e >= s && isspace(c[e])){
                e--;
            }
            if (s > e){
                continue;
            }
            c = c.substr(s, e - s + 1);
        }
        size_t sp = c.find_first_of(" \t");
        if (sp == string::npos){
            insts.push_back({c, ""});
        }
        else{
            s = sp;
            while (s < (int)c.size() && isspace(c[s])){
                s++;
            }
            int e2 = (int)c.size() - 1;
            while (e2 >= s && isspace(c[e2])){
                e2--;
            }
            insts.push_back({c.substr(0, sp), c.substr(s, e2 - s + 1)});
        }
    }
    auto val = [&](string x){ return isalpha(x[0]) ? reg[x] : stoi(x); };
    vector<int> st;
    int cmp {0};
    for (int i {0}; i < (int)insts.size(); ){
        string op = insts[i].first, arg = insts[i].second, x, y;
        if (op == "mov" || op == "add" || op == "sub" || op == "mul" || op == "div" || op == "cmp"){
            size_t comma = arg.find(',');
            x = arg.substr(0, comma); y = arg.substr(comma + 1);
            while (x.size() && isspace(x.back())){
                x.pop_back();
            }
            while (y.size() && isspace(y.front())){
                y.erase(0, 1);
            }
            int v = val(y);
            if (op == "mov"){
                reg[x] = v;
            } else if (op == "add"){
                reg[x] += v;
            } else if (op == "sub"){
                reg[x] -= v;
            } else if (op == "mul"){
                reg[x] *= v;
            } else if (op == "div"){
                reg[x] /= v;
            } else{
                int vx = val(x);
                cmp = vx < v ? -1 : vx > v ? 1 : 0;
            }
            i++;
        } else if (op == "inc"){
            reg[arg]++;
            i++;
        } else if (op == "dec"){
            reg[arg]--;
            i++;
        } else if (op == "jmp"){
            i = labels[arg];
        } else if (op == "jne"){
            i = cmp != 0 ? labels[arg] : i + 1;
        } else if (op == "je"){
            i = cmp == 0 ? labels[arg] : i + 1;
        } else if (op == "jge"){
            i = cmp >= 0 ? labels[arg] : i + 1;
        } else if (op == "jg"){
            i = cmp > 0 ? labels[arg] : i + 1;
        } else if (op == "jle"){
            i = cmp <= 0 ? labels[arg] : i + 1;
        } else if (op == "jl"){
            i = cmp < 0 ? labels[arg] : i + 1;
        } else if (op == "call"){
            st.push_back(i + 1);
            i = labels[arg];
        } else if (op == "ret"){
            i = st.back();
            st.pop_back();
        } else if (op == "end"){
            return out;
        } else if (op == "msg"){
            bool in = false; string cur;
            for (char ch : arg){
                if (ch == '\''){
                    if (!in) {
                        cur = ""; 
                    }
                    in = !in;
                    if (!in){
                        out += cur;
                        cur = "";
                    }
                } else if (!in && ch == ','){
                    int s {0}, e = (int)cur.size() - 1;
                    while (s <= e && isspace(cur[s])){
                        s++;
                    }
                    while (e >= s && isspace(cur[e])){
                        e--;
                    }
                    if (s <= e){
                        out += to_string(val(cur.substr(s, e - s + 1)));
                    }
                    cur = "";
                } else{
                    cur += ch;
                }
            }
            int s {0}, e = (int)cur.size() - 1;
            while (s <= e && isspace(cur[s])){
                s++;
            }
            while (e >= s && isspace(cur[e])){
                e--;
            }
            if (s <= e){
                out += to_string(val(cur.substr(s, e - s + 1)));
            }
            i++;
        } else{
            i++;
        }
    }
    return "-1";
}