#include <bits/stdc++.h>
using namespace std;

template<class T> class MagicCompare;

template<class T> struct unwrap{
    using type = T;
};

template<class T> struct unwrap<MagicCompare<T>>{
    using type = T;
};

template<class T> struct is_magic : false_type{};
template<class T> struct is_magic<MagicCompare<T>> : true_type{};

template<class T> struct Chain;
template<class T> struct is_chain : false_type{};
template<class T> struct is_chain<Chain<T>> : true_type{};

template<class T> struct Chain{
    bool ok; 
    T v;
    operator bool() const{
        return ok;
    }

#define CMP(op) \
    template<class U> auto operator op(const U& o) const{ \
        using out = typename unwrap<U>::type; \
        out r = o; \
        return Chain<out>{ok && (v op r), r}; \
        }
    CMP(==) CMP(!=) CMP(<) CMP(>) CMP(<=) CMP(>=)
#undef CMP
};

template<class T>
class MagicCompare {
  public:
    T v;
    MagicCompare(T val = 0) : v(val){}
    operator T() const{
        return v;
    }

#define ARITH(op) \
    template<class U> auto operator op(const U& o) const{ \
        using out = typename unwrap<U>::type; \
        return MagicCompare<decltype(v op declval<out>())>(v op (out)o); \
    } \
    template<class U, class = enable_if_t<!is_magic<U>::value>> \
    friend auto operator op(const U& l, const MagicCompare& r){ \
        return MagicCompare<decltype(l op r.v)>(l op r.v); \
    }
    ARITH(+) ARITH(-) ARITH(*) ARITH(/) ARITH(%)
#undef ARITH

#define CMP(op) \
    template<class U> auto operator op(const U& o) const{ \
        using out = typename unwrap<U>::type; \
        out r = o; \
        return Chain<out>{v op r, r}; \
    } \
    template<class U, class = enable_if_t<!is_magic<U>::value && !is_chain<U>::value>> \
    friend auto operator op(const U& l, const MagicCompare& r){ \
        return Chain<T>{l op r.v, r.v}; \
    }
    CMP(==) CMP(!=) CMP(<) CMP(>) CMP(<=) CMP(>=)
#undef CMP

    MagicCompare operator+() const{
        return MagicCompare(+v);
    }
    MagicCompare operator-() const{
        return MagicCompare(-v);
    }
    MagicCompare& operator++(){
        v++;
        return *this;
    }
    MagicCompare operator++(int){
        auto c = *this;
        v++;
        return c;
    }
    MagicCompare& operator--(){
        v--;
        return *this;
    }
    MagicCompare operator--(int){
        auto c = *this;
        v--;
        return c;
    }

    template<class U> MagicCompare& operator+=(const U& o){
        v += (typename unwrap<U>::type)o;
        return *this;
    }
    template<class U> MagicCompare& operator-=(const U& o){
        v -= (typename unwrap<U>::type)o;
        return *this;
    }
    template<class U> MagicCompare& operator*=(const U& o){
        v *= (typename unwrap<U>::type)o;
        return *this;
    }
    template<class U> MagicCompare& operator/=(const U& o){
        v /= (typename unwrap<U>::type)o;
        return *this;
    }
    template<class U> MagicCompare& operator%=(const U& o){
        v %= (typename unwrap<U>::type)o;
        return *this;
    }
};