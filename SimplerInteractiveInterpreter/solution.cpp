// // #include <string>
// #include <bits/stdc++.h>
// using namespace std;

// static map<string, double> vars;

// inline void skip_ws(const char*& p) {
//     while (*p && isspace((unsigned char)*p)) {
//         p++;
//     }
// }

// double parse_expr(const char*& p);

// double parse_factor(const char*& p) {
//     skip_ws(p);
//     if (*p == '\0') {
//         throw runtime_error("");
//     }
//     if (*p == '(') {
//         p++;
//         double res = parse_expr(p);
//         skip_ws(p);
//         if (*p != ')') {
//             throw runtime_error("");
//         }
//         p++;
//         return res;
//     }
//     if (isdigit((unsigned char)*p) || *p == '.') {
//         const char* start = p;
//         bool has_digit = false;
//         while (isdigit((unsigned char)*p)) {
//             p++;
//             has_digit = true;
//         }
//         if (*p == '.') {
//             const char* dot_p = p;
//             p++;
//             if (!isdigit((unsigned char)*p) && !has_digit) {
//                 p = dot_p;
//             } else {
//                 while (isdigit((unsigned char)*p)) {
//                     p++;
//                     has_digit = true;
//                 }
//             }
//         }
//         if (has_digit) {
//             string num_str(start, p - start);
//             char* endptr;
//             return strtod(num_str.c_str(), &endptr);
//         }
//     }
//     if (isalpha((unsigned char)*p) || *p == '_') {
//         string id = "";
//         id += *p++;
//         while (isalnum((unsigned char)*p) || *p == '_') {
//             id += *p++;
//         }
//         if (vars.find(id) == vars.end()) {
//             throw runtime_error("");
//         }
//         return vars[id];
//     }
//     throw runtime_error("");
// }

// double parse_term(const char*& p) {
//     double res = parse_factor(p);
//     while (true) {
//         skip_ws(p);
//         if (*p == '*') {
//             p++;
//             res *= parse_factor(p);
//         } else if (*p == '/') {
//             p++;
//             double den = parse_factor(p);
//             if (den == 0) {
//                 throw runtime_error("");
//             }
//             res /= den;
//         } else if (*p == '%') {
//             p++;
//             double den = parse_factor(p);
//             if (den == 0) {
//                 throw runtime_error("");
//             }
//             res = fmod(res, den);
//         } else {
//             break;
//         }
//     }
//     return res;
// }

// double parse_expr(const char*& p) {
//     double res = parse_term(p);
//     while (true) {
//         skip_ws(p);
//         if (*p == '+') {
//             p++;
//             res += parse_term(p);
//         } else if (*p == '-') {
//             p++;
//             res -= parse_term(p);
//         } else {
//             break;
//         }
//     }
//     return res;
// }

// double interpret(std::string expression) {
// //   return 0;
//     if (expression.find_first_not_of(" \t\r\n") == string::npos) {
//         throw runtime_error("");
//     }
//     const char* p = expression.c_str();
//     skip_ws(p);
//     if (isalpha((unsigned char)*p) || *p == '_') {
//         const char* peek = p;
//         string id = "";
//         id += *peek++;
//         while (isalnum((unsigned char)*peek) || *peek == '_') {
//             id += *peek++;
//         }
//         skip_ws(peek);
//         if (*peek == '=') {
//             p = peek + 1;
//             double val = parse_expr(p);
//             skip_ws(p);
//             if (*p != '\0') {
//                 throw runtime_error("");
//             }
//             vars[id] = val;
//             return val;
//         }
//     }
//     double val = parse_expr(p);
//     skip_ws(p);
//     if (*p != '\0') {
//         throw runtime_error("");
//     }
//     return val;
// }

#include <bits/stdc++.h>
using namespace std;

static map<string, double> vars;

inline void skip_ws(const char*& p) {
    while (*p && isspace((unsigned char)*p)) {
        p++;
    }
}

double parse_expr(const char*& p);

double parse_factor(const char*& p) {
    skip_ws(p);
    if (*p == '\0') {
        throw runtime_error("Unexpected end of expression");
    }
    if (*p == '+') {
        p++;
        return parse_factor(p);
    }
    if (*p == '-') {
        p++;
        return -parse_factor(p);
    }
    if (*p == '(') {
        p++;
        double res = parse_expr(p);
        skip_ws(p);
        if (*p != ')') {
            throw runtime_error("Missing closing parenthesis");
        }
        p++;
        return res;
    }
    if (isdigit((unsigned char)*p) || *p == '.') {
        const char* start = p;
        bool has_digit = false;
        while (isdigit((unsigned char)*p)) {
            p++;
            has_digit = true;
        }
        if (*p == '.') {
            const char* dot_p = p;
            p++;
            if (!isdigit((unsigned char)*p) && !has_digit) {
                p = dot_p;
            } else {
                while (isdigit((unsigned char)*p)) {
                    p++;
                    has_digit = true;
                }
            }
        }
        if (has_digit) {
            string num_str(start, p - start);
            char* endptr;
            return strtod(num_str.c_str(), &endptr);
        }
    }
    if (isalpha((unsigned char)*p) || *p == '_') {
        string id = "";
        id += *p++;
        while (isalnum((unsigned char)*p) || *p == '_') {
            id += *p++;
        }
        const char* peek = p;
        skip_ws(peek);
        if (*peek == '=') {
            p = peek + 1;
            double val = parse_expr(p);
            vars[id] = val;
            return val;
        }
        if (vars.find(id) == vars.end()) {
            throw runtime_error("ERROR: Invalid identifier. No variable with name '" + id + "' was found.");
        }
        return vars[id];
    }
    throw runtime_error("Invalid factor");
}

double parse_term(const char*& p) {
    double res = parse_factor(p);
    while (true) {
        skip_ws(p);
        if (*p == '*') {
            p++;
            res *= parse_factor(p);
        } else if (*p == '/') {
            p++;
            double den = parse_factor(p);
            if (den == 0) {
                throw runtime_error("Division by zero");
            }
            res /= den;
        } else if (*p == '%') {
            p++;
            double den = parse_factor(p);
            if (den == 0) {
                throw runtime_error("Modulo by zero");
            }
            res = fmod(res, den);
        } else {
            break;
        }
    }
    return res;
}

double parse_expr(const char*& p) {
    double res = parse_term(p);
    while (true) {
        skip_ws(p);
        if (*p == '+') {
            p++;
            res += parse_term(p);
        } else if (*p == '-') {
            p++;
            res -= parse_term(p);
        } else {
            break;
        }
    }
    return res;
}

double interpret(std::string expression) {
    if (expression.find_first_not_of(" \t\r\n") == string::npos) {
        throw runtime_error("Empty expression");
    }
    const char* p = expression.c_str();
    skip_ws(p);
    double val = parse_expr(p);
    skip_ws(p);
    if (*p != '\0') {
        throw runtime_error("Extra characters at end of expression");
    }
    return val;
}