#include<bits/stdc++.h>
using namespace std;

int square_digits(int num) {
//  return 0;
    string a = to_string(num);
    string res = "";
    for(char ch : a){
        int d = ch - '0';
        res += to_string(d * d);
    }
    return stoi(res);
}