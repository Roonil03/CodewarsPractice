// #include <string>
#include <bits/stdc++.h>
using namespace std;

struct Reg{
    string s; int p;
    bool nul() const{
        return p == 0;
    }
    bool eps() const{
        return p == 1;
    }
};

Reg Nul ={"", 0}, Eps ={"", 1};
Reg atom(string s){
    return{s, 2};
}

int get_p(const string& s){
    if (s == "0" || s == "1" || s == "[01]" || (!s.empty() && s.back() == '*')){
        return 2;
    }
    if (s.length() >= 2 && s[0] == '(' && s.back() == ')'){
        int d = 0;
        bool ok = true;
        for (int i = 0; i < s.length() - 1; i++){
            if (s[i] == '(') d++; else if (s[i] == ')'){
                d--;
            }
            if (d == 0){
                ok = false;
                break;
            }
        }
        if (ok){
            return 2;
        }
    }
    return 3;
}

vector<string> split_uni(const string& s){
    vector<string> r;
    int d = 0;
    string c = "";
    for (char x : s){
        if (x == '(' || x == '['){
            d++;
        } else if (x == ')' || x == ']'){
            d--;
        }
        if (x == '|' && d == 0){
            r.push_back(c);
            c = "";
        } else{
            c += x;
        }
    }
    r.push_back(c);
    return r;
}

Reg uni(Reg a, Reg b){
    if (a.nul()){
        return b;
    }
    if (b.nul()){
        return a;
    }
    if (a.s == b.s){
        return a;
    }
    auto ta = split_uni(a.s), tb = split_uni(b.s);
    set<string> ts(ta.begin(), ta.end()); ts.insert(tb.begin(), tb.end());
    if (ts.count("0") && ts.count("1")){
        ts.erase("0");
        ts.erase("1");
        ts.insert("[01]");
    }
    if (ts.size() == 1){
        return{*ts.begin(), get_p(*ts.begin())};
    }
    string r = "";
    for (auto it = ts.begin(); it != ts.end(); it++){
        if (it != ts.begin()){
            r += "|";
        }
        r += *it;
    }
    return{r, 4};
}

Reg seq(Reg a, Reg b){
    if (a.nul() || b.nul()){
        return Nul;
    }
    if (a.eps()){
        return b;
        if (b.eps()){
            return a;
        }
    }
    string sa = a.s, sb = b.s;
    if (a.p == 4){
        sa = "(?:" + sa + ")";
    }
    if (b.p == 4){
        sb = "(?:" + sb + ")";
    }
    return{sa + sb, 3};
}

Reg star(Reg a){
    if (a.nul() || a.eps()){
        return Eps;
    }
    if (a.s == "[01]"){
        return{"[01]*", 2};
    }
    if (a.p == 2 && a.s.back() == '*'){
        return a;
    }
    string sa = a.s;
    if (a.p > 2){
        sa = "(?:" + sa + ")";
    }
    return{sa + "*", 2};
}

std::string regex_divisible_by(int n)
{
//   return "";
  if (n == 1){
    return "^[01]+$";
  }
  vector<vector<Reg>> M(n, vector<Reg>(n, Nul));
  for (int i = 0; i < n; i++){
      M[i][(2 * i) % n] = uni(M[i][(2 * i) % n], atom("0"));
      M[i][(2 * i + 1) % n] = uni(M[i][(2 * i + 1) % n], atom("1"));
  }
  vector<int> st;
  for (int i = 1; i < n; i++){
    st.push_back(i);
  }
  while (!st.empty()){
      int bk = -1, ml = 1e9;
      for (int k : st){
          int cl = 0;
          for (int i : st){
              if (i == k){
                continue;
              }
              for (int j : st){
                  if (j == k){
                    continue;
                  }
                  cl += uni(M[i][j], seq(M[i][k], seq(star(M[k][k]), M[k][j]))).s.length();
              }
              cl += uni(M[i][0], seq(M[i][k], seq(star(M[k][k]), M[k][0]))).s.length();
              cl += uni(M[0][i], seq(M[0][k], seq(star(M[k][k]), M[k][i]))).s.length();
          }
          cl += uni(M[0][0], seq(M[0][k], seq(star(M[k][k]), M[k][0]))).s.length();
          if (cl < ml){
            ml = cl;
            bk = k;
          }
      }
      int k = bk;
      vector<vector<Reg>> nM = M;
      for (int i = 0; i < n; i++){
          if (i == k){
            continue;
          }
          for (int j = 0; j < n; j++){
              if (j == k){
                continue;
              }
              nM[i][j] = uni(M[i][j], seq(M[i][k], seq(star(M[k][k]), M[k][j])));
          }
      }
      M = nM; st.erase(find(st.begin(), st.end(), k));
  }
  Reg r = M[0][0]; string a = r.s;
  if (r.p > 2){
    a = "(?:" + a + ")";
  }
  return "^" + a + "+$";
}