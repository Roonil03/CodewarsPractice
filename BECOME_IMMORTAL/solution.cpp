#include <cstdint>
#include <bits/stdc++.h>
using namespace std;

int64_t elder_age(int64_t m, int64_t n, int64_t l, int64_t t)
{
//   return 0;
    if (m == 0 || n == 0){
      return 0;
    }
    if (m < n){
      swap(m, n);
    }
    uint64_t p = 1ULL << (63 - __builtin_clzll(m));
    auto ss = [&](uint64_t len, uint64_t loss) -> uint64_t {
        if (len <= loss) return 0;
        uint64_t N = len - loss;
        uint64_t a = N, b = N - 1;
        if (a % 2 == 0){
          a /= 2;
        } else{
          b /= 2;
        }
        return (a % t) * (b % t) % t;
    };
    if (n <= p) {
        uint64_t t1 = (n % t) * ss(p, l) % t;
        uint64_t t2 = elder_age(m - p, n, l > p ? l - p : 0, t);
        uint64_t t3 = p > l ? (((m - p) % t) * (n % t) % t) * ((p - l) % t) % t : 0;
        return (t1 + t2 + t3) % t;
    }
    uint64_t t1 = (p % t) * ss(p, l) % t;
    uint64_t t2 = (((m - p) % t + (n - p) % t) % t) * ((t + ss(2 * p, l) - ss(p, l)) % t) % t;
    uint64_t t3 = elder_age(m - p, n - p, l, t);
    return (t1 + t2 + t3) % t;
}