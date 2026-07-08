#include <bits/stdc++.h>
using namespace std;

long nextBigger(long n) {
//   return n;
    string s = to_string(n);
    return next_permutation(s.begin(), s.end()) ? stol(s) : -1;
}