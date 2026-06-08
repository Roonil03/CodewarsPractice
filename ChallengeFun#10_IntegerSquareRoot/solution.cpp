// #include <iostream>
// #include <string>
#include<bits/stdc++.h>
using namespace std;

bool lte(string a, string b){
    if (a.size() != b.size()){
        return a.size() < b.size();
    }
    return a <= b;
}

string sub(string a, string b){
    string r = "";
    int br {0}, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0){
        int cur = (a[i] - '0') - (j >= 0 ? b[j] - '0' : 0) - br;
        if (cur < 0){
            cur += 10;
            br = 1;
        } else{
            br = 0;
        }
        r += (cur + '0');
        i--;
        j--;
    }
    while (r.size() > 1 && r.back() == '0'){
        r.pop_back();
    }
    reverse(r.begin(), r.end());
    return r;
}

string mul2(string s){
    string r = "";
    int c {0};
    for (int i = s.size() - 1; i >= 0; i--){
        int cur = (s[i] - '0') * 2 + c;
        r += (cur % 10 + '0');
        c = cur / 10;
    }
    if (c){
        r += (c + '0');
    }
    reverse(r.begin(), r.end());
    return r;
}

string mul_d(string s, int x){
    if (x == 0) return "0";
    string r = "";
    int c {0};
    for (int i = s.size() - 1; i >= 0; i--){
        int cur = (s[i] - '0') * x + c;
        r += (cur % 10 + '0');
        c = cur / 10;
    }
    if (c){
        r += (c + '0');
    }
    reverse(r.begin(), r.end());
    return r;
}

string integer_square_root(string n) {
  // Coding and coding ... 
//   return "";
        if (n == "0"){
        return "0";
    }
    vector<string> pairs;
    int rem = n.size() % 2;
    if (rem == 1){
        pairs.push_back(n.substr(0, 1));
    }
    for (size_t i = rem; i < n.size(); i += 2){
        pairs.push_back(n.substr(i, 2));
    }
    string res = "", rem_str = "";
    for (string& p : pairs){
        if (rem_str == "0"){
            rem_str = "";
        }
        rem_str += p;
        size_t id = rem_str.find_first_not_of('0');
        rem_str = (id == string::npos) ? "0" : rem_str.substr(id);
        string base = mul2(res);
        for (int x = 9; x >= 0; x--){
            string prod = mul_d(base + to_string(x), x);
            if (lte(prod, rem_str)){
                res += to_string(x);
                rem_str = sub(rem_str, prod);
                break;
            }
        }
    }
    size_t id = res.find_first_not_of('0');
    return (id == string::npos) ? "0" : res.substr(id);
}