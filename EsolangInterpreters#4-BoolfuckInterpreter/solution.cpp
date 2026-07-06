// #include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

char *boolfuck (const char *code, const char *input) {
//   return (char*) calloc (1, 1);
    string c, in(input ? input : ""), out;
    for (int i = 0; code[i]; i++){
        char x = code[i];
        if (x=='+'||x==','||x==';'||x=='<'||x=='>'||x=='['||x==']'){
            c += x;
        }
    }    
    vector<int> m(c.size()), s;
    for (int i = 0; i < c.size(); i++){
        if (c[i] == '['){
            s.push_back(i);
        }
        else if (c[i] == ']'){
            m[s.back()] = i; 
            m[i] = s.back(); 
            s.pop_back();
        }
    }    
    vector<char> tp(1, 0), tn(0);
    auto t = [&](int x) -> char&{
        if (x >= 0){ 
            if (x >= tp.size()){
                tp.resize(x + 1, 0); 
            }
            return tp[x]; 
        }
        if (-x > tn.size()){
            tn.resize(-x, 0); 
        }
        return tn[-x - 1];
    };    
    int p = 0, ii = 0, ib = 0, ob = 0;
    char co = 0;    
    for (int i = 0; i < c.size(); i++){
        char x = c[i];
        if (x == '+'){
            t(p) ^= 1;
        }  else if (x == '<'){
            p--;
        } else if (x == '>'){
            p++;
        } else if (x == ','){
            t(p) = (ii < in.size()) ? ((in[ii] >> ib++) & 1) : 0;
            if (ib == 8){
                ib = 0;
                ii++;
            }
        } else if (x == ';'){
            co |= (t(p) << ob++);
            if (ob == 8){
                out += co;
                co = 0;
                ob = 0;
            }
        } else if (x == '[' && !t(p)){
            i = m[i];
        } else if (x == ']' && t(p)){
            i = m[i];
        }
    }    
    if (ob > 0){
        out += co;    
    }
    char *r = (char*)malloc(out.size() + 1);
    memcpy(r, out.c_str(), out.size() + 1);
    return r;
}