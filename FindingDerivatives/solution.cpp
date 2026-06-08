// #include <functional>
// #include <complex>
// #include <tuple>
// #include <string>
#include <bits/stdc++.h>
using namespace std;
using value_t = std::complex<double>;
using func_t = std::function<value_t(value_t)>;

struct D{
    value_t v, d1, d2;
    D(value_t v = 0, value_t d1 = 0, value_t d2 = 0) : v(v), d1(d1), d2(d2){}
    D operator+(const D& o) const{
        return{v + o.v, d1 + o.d1, d2 + o.d2};
    }
    D operator-(const D& o) const{
        return{v - o.v, d1 - o.d1, d2 - o.d2};
    }
    D operator*(const D& o) const{
        return{v * o.v, d1 * o.v + v * o.d1, d2 * o.v + 2. * d1 * o.d1 + v * o.d2};
    }
    D operator/(const D& o) const{
        value_t nv = v / o.v, nd1 = (d1 - nv * o.d1) / o.v;
        return{nv, nd1, (d2 - 2. * nd1 * o.d1 - nv * o.d2) / o.v};
    }
};

D f_pow(const D& b, const D& e) {
    value_t nv = pow(b.v, e.v), b_frac = b.d1 / b.v;
    value_t t1 = e.d1 * log(b.v) + e.v * b_frac, nd1 = nv * t1;
    return {
      nv, nd1, nd1 * t1 + nv * (e.d2 * log(b.v) + 2. * e.d1 * b_frac + e.v * b.d2 / b.v - e.v * b_frac * b_frac)
    };
}

using Func = function<D(D)>;
using Node = shared_ptr<Func>;
Node make_node(Func f){
    return make_shared<Func>(f);
}

struct P{
    string s;
    size_t p{0};
    P(string s) : s(s){}
    Node expr(){
        auto l = term();
        while (p < s.size() && (s[p] == '+' || s[p] == '-')){
            char o = s[p++]; auto r = term();
            if (o == '+'){
                l = make_node([l, r](D x){
                    return (*l)(x) + (*r)(x);
                });
            } else{
                l = make_node([l, r](D x){ return (*l)(x) - (*r)(x); });
            }
        }
        return l;
    }
    Node term(){
        auto l = factor();
        while (p < s.size() && (s[p] == '*' || s[p] == '/')){
            char o = s[p++]; 
            auto r = factor();
            if (o == '*'){
                l = make_node([l, r](D x){ return (*l)(x) * (*r)(x); });
            } else{
                l = make_node([l, r](D x){ return (*l)(x) / (*r)(x); });
            }
        }
        return l;
    }
    Node factor(){
        auto l = basic();
        if (p < s.size() && s[p] == '^'){
            p++;
            auto r = factor();
            return make_node([l, r](D x){ return f_pow((*l)(x), (*r)(x)); });
        }
        return l;
    }
    Node basic(){
        if (s[p] == '('){
            p++;
            auto r = expr();
            p++;
            return r;
        }
        if (s[p] == 'x'){
            p++;
            return make_node([](D x){
                return x; 
            });
        }
        if (isalpha(s[p])){
            string fn = "";
            while (isalpha(s[p])){
                fn += s[p++];
            }
            p++;
            auto r = expr();
            p++;
                        if (fn == "sin"){
                return make_node([r](D x) {
                    D u = (*r)(x);
                    value_t sv = sin(u.v), cv = cos(u.v);
                    return D(sv, u.d1 * cv, u.d2 * cv - u.d1 * u.d1 * sv);
                });
            }
            if (fn == "cos"){
                return make_node([r](D x) {
                    D u = (*r)(x);
                    value_t sv = sin(u.v), cv = cos(u.v);
                    return D(cv, -u.d1 * sv, -u.d2 * sv - u.d1 * u.d1 * cv);
                });
            }
            if (fn == "tan"){
                return make_node([r](D x) {
                    D u = (*r)(x);
                    value_t tv = tan(u.v), sec2 = 1. + tv * tv, nd1 = u.d1 * sec2;
                    return D(tv, nd1, u.d2 * sec2 + 2. * tv * nd1 * u.d1);
                });
            }
            if (fn == "cot"){
                return make_node([r](D x) {
                    D u = (*r)(x);
                    value_t tv = 1. / tan(u.v), csc2 = 1. + tv * tv, nd1 = -u.d1 * csc2;
                    return D(tv, nd1, -u.d2 * csc2 + 2. * tv * u.d1 * u.d1 * csc2);
                });
            }
            if (fn == "log"){
                return make_node([r](D x) {
                    D u = (*r)(x);
                    value_t uf = u.d1 / u.v;
                    return D(log(u.v), uf, u.d2 / u.v - uf * uf);
                });
            }
        }
        string n = ""; while (p < s.size() && (isdigit(s[p]) || s[p] == '.')) n += s[p++];
        value_t val = stod(n); return make_node([val](D){ return D(val, 0, 0); });
    }
};

std::tuple<func_t, func_t, func_t> differentiate(const std::string& eq) {
//     return {
//         [](value_t) { return 0; },
//         [](value_t) { return 0; },
//         [](value_t) { return 0; }
//     };
    string s = eq;
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    auto f = P(s).expr();
    return {
        [f](value_t x) {
            return (*f)(D(x, 1, 0)).v;
        },
        [f](value_t x) {
            return (*f)(D(x, 1, 0)).d1;
        },
        [f](value_t x) {
            return (*f)(D(x, 1, 0)).d2;
        }
    };
}