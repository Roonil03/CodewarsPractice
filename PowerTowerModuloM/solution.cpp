#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull get_phi(ull n){
    ull res = n;
    for (ull i = 2; i * i <= n; ++i){
        if (n % i == 0){
            while (n % i == 0){
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1){
        res -= res / n;
    }
    return res;
}

ull mod_star(ull x, ull m){
    return x >= m ? (x % m) + m : x;
}

ull power_star(ull b, ull e, ull m){
    if (m == 1){
        return 1;
    }
    ull res = mod_star(1, m);
    b = mod_star(b, m);
    while (e > 0){
        if (e & 1){
            res = mod_star(res * b, m);
        }
        b = mod_star(b * b, m);
        e >>= 1;
    }
    return res;
}

ull calc(ull b, ull h, ull m){
    if (m == 1){
        return 1;
    }
    if (h == 0){
        return mod_star(1, m);
    }
    if (b == 1){
        return mod_star(1, m);
    }
    return power_star(b, calc(b, h - 1, get_phi(m)), m);
}

ull tower(ull base, ull h, ull m) {
  // Return base ^ base ^ ... ^ base, where the height is h, modulo m.
  // ull == unsigned long long
    if (m == 1){
        return 0;
    }
    if (h == 0){
        return 1;
    }
    if (base == 1){
        return 1 % m;
    }
    return calc(base, h, m) % m;
//   return 0ull;
}