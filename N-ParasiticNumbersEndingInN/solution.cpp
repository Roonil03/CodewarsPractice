// #include <string>
#include <bits/stdc++.h>
using namespace std;

std::string calculateSpecial(int lastDigit, int radix) {
//   return "";
    string res = "";
    int d = lastDigit, c {0};
    string ch = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while(true){
        res += ch[d];
        int p = d * lastDigit + c;
        c = p / radix;
        d = p % radix;
        if(d == lastDigit && !c){
            break;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
