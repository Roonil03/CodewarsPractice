#include <bits/stdc++.h>
using namespace std;

#define i128 __int128
#define ull uint64_t

extern ull addmod(ull a, ull b, ull m);
extern ull mulmod(ull a, ull b, ull m);

unsigned i128 gcd128(unsigned i128 a, unsigned i128 b){
    while (b){
        a %= b;
        swap(a, b);
    }
    return a;
}

pair<ull, ull> fibMod(ull n, ull m){
    if (n == 0){
        return{0, 1};
    }
    auto p = fibMod(n >> 1, m);
    ull a = p.first;
    ull b = p.second;
    ull doubleB = addmod(b, b, m);
    ull diff = doubleB >= a ? doubleB - a : m - (a - doubleB);
    ull c = mulmod(a, diff, m);
    ull d = addmod(mulmod(a, a, m), mulmod(b, b, m), m);
    if (n & 1){
        return{d, addmod(c, d, m)};
    }
    return{c, d};
}

ull powerMod(ull base, ull exp, ull mod){
    ull res{1};
    base %= mod;
    while (exp > 0){
        if (exp % 2 == 1){
            res = mulmod(res, base, mod);
        }
        base = mulmod(base, base, mod);
        exp /= 2;
    }
    return res;
}

bool millerRabin(ull n){
    if (n < 2){
        return false;
    }
    if (n == 2 || n == 3){
        return true;
    }
    if (n % 2 == 0){
        return false;
    }
    ull d = n - 1;
    int s{0};
    while (d % 2 == 0){
        d /= 2;
        s++;
    }
    static const ull bases[] ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ull a : bases){
        if (n <= a){
            break;
        }
        ull x = powerMod(a, d, n);
        if (x == 1 || x == n - 1){
            continue;
        }
        bool isComposite = true;
        for (int r{1}; r < s; r++){
            x = mulmod(x, x, n);
            if (x == n - 1){
                isComposite = false;
                break;
            }
        }
        if (isComposite){
            return false;
        }
    }
    return true;
}

ull getFactor(ull n){
    if (n % 2 == 0){
        return 2;
    }
    ull x{2}, y{2}, d{1}, c{1};
    static mt19937_64 rng(1337);
    auto f = [&](ull val){
        return addmod(mulmod(val, val, n), c, n);
    };
    while (d == 1){
        x = f(x);
        y = f(f(y));
        ull diff = x > y ? x - y : y - x;
        d = gcd(diff, n);
        if (d == n){
            x = rng() % (n - 2) + 2;
            y = x;
            c = rng() % (n - 1) + 1;
            d = 1;
        }
    }
    return d;
}

void factorize(ull n, map<ull, ull>& factors){
    if (n <= 1){
        return;
    }
    if (millerRabin(n)){
        factors[n]++;
        return;
    }
    ull divisor = getFactor(n);
    factorize(divisor, factors);
    factorize(n / divisor, factors);
}

ull getPrimePeriod(ull p){
    if (p == 2){
        return 3;
    }
    if (p == 5){
        return 20;
    }
    ull d{0};
    if (p % 10 == 1 || p % 10 == 9){
        d = p - 1;
    } else{
        d = 2 * p + 2;
    }
    map<ull, ull> factors;
    factorize(d, factors);
    ull t = d;
    for (auto const& [q, _] : factors){
        while (t % q == 0){
            auto fibRes = fibMod(t / q, p);
            if (fibRes.first == 0 && fibRes.second == 1){
                t /= q;
            } else{
                break;
            }
        }
    }
    return t;
}

uint64_t pisano_period(ull n){
//   return 0;
    if (n <= 1){
        return 1;
    }
    map<ull, ull> factors;
    factorize(n, factors);    
    unsigned i128 res{1};
    for (auto const& [p, k] : factors){
        ull period = getPrimePeriod(p);
        for (ull i{1}; i < k; i++){
            period *= p;
        }
        unsigned i128 a = res;
        unsigned i128 b = period;
        res = (a / gcd128(a, b)) * b;
    }
    return (ull)res;
}