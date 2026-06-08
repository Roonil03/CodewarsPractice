struct RegExp;

RegExp* any ();
RegExp* normal (char c);
RegExp* zeroOrMore (RegExp *starred);
RegExp* orr (RegExp *left, RegExp *right);
RegExp* str (RegExp *first);
RegExp* add (RegExp *str, RegExp *next);

// #include <bits/stdc++.h>
using namespace std;

RegExp *parseRegExp (const char *input) {
//   return 0;
    if (!input || *input == '\0'){
      return nullptr;
    }
    auto parseExpr = [](auto& self, const char*& p) -> RegExp*{
        auto parseAtom = [&](const char*& p) -> RegExp*{
            if (*p == '\0'){
              return nullptr;
            }
            if (*p == '.'){
              p++;
              return any();
            }
            if (*p == '('){
                p++;
                auto* e = self(self, p);
                if (!e || *p != ')'){
                  return nullptr;
                }
                p++;
                return e;
            }
            if (*p == ')' || *p == '|' || *p == '*'){
              return nullptr;
            }
            return normal(*p++);
        };
        auto parseFactor = [&](const char*& p) -> RegExp*{
            auto* a = parseAtom(p);
            if (!a){
              return nullptr;
            }
            if (*p == '*'){
                p++;
                if (*p == '*'){
                  return nullptr;
                }
                return zeroOrMore(a);
            }
            return a;
        };
        auto parseSeq = [&](const char*& p) -> RegExp*{
            auto* f = parseFactor(p);
            if (!f){
              return nullptr;
            }
            if (*p == '\0' || *p == ')' || *p == '|'){
              return f;
            }
            auto* res = str(f);
            while (*p != '\0' && *p != ')' && *p != '|' && *p != '*'){
                auto* next = parseFactor(p);
                if (!next){
                  return nullptr;
                }
                res = add(res, next);
            }
            return res;
        };
        auto* left = parseSeq(p);
        if (!left){
          return nullptr;
        }
        if (*p == '|'){
            p++;
            auto* right = parseSeq(p);
            if (!right || *p == '|'){
              return nullptr;
            }
            return orr(left, right);
        }
        return left;
    };
    const char* p = input;
    auto* res = parseExpr(parseExpr, p);
    return *p == '\0' ? res : nullptr;
}