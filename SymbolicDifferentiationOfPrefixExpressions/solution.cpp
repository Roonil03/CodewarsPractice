#include<bits/stdc++.h>
using namespace std;

struct Expr{
    string op;
    shared_ptr<Expr> a, b;
    bool is_num; double val;
    string var;
    Expr() : is_num(false), val(0){}
};

shared_ptr<Expr> parse(const string& s, size_t& i){
    while (i < s.size() && isspace(s[i])){
        i++;
    }
    if (i == s.size()){
        return nullptr;
    }
    auto e = make_shared<Expr>();
    if (s[i] == '('){
        i++;
        while (i < s.size() && isspace(s[i])){
            i++;
        }
        size_t j = i;
        while (j < s.size() && !isspace(s[j]) && s[j] != ')'){
            j++;
        }
        e->op = s.substr(i, j - i);
        i = j;
        e->a = parse(s, i);
        if (e->op == "+" || e->op == "-" || e->op == "*" || e->op == "/" || e->op == "^"){
            e->b = parse(s, i);
        }
        while (i < s.size() && isspace(s[i])){
            i++;
        }
        if (i < s.size() && s[i] == ')'){
            i++;
        }
    } else{
        size_t j = i;
        while (j < s.size() && !isspace(s[j]) && s[j] != ')'){
            j++;
        }
        string tok = s.substr(i, j - i);
        i = j;
        if (tok == "x"){
            e->var = "x";
        } else{
            e->is_num = true;
            e->val = stod(tok);
        }
    }
    return e;
}

shared_ptr<Expr> mk_num(double v){
    auto e = make_shared<Expr>();
    e->is_num = true;
    e->val = v;
    return e;
}

shared_ptr<Expr> simplify(shared_ptr<Expr> e){
    if (!e){
        return e;
    }
    if (e->is_num || !e->var.empty()){
        return e;
    }
    e->a = simplify(e->a);
    if (e->b){
        e->b = simplify(e->b);
    }
//     if (e->op == "+" || e->op == "*"){
//         if (e->b && e->b->is_num && (!e->a->is_num)){
//             swap(e->a, e->b);
//         }
//     }
    if (e->op == "+"){
        if (e->a->is_num && e->a->val == 0){
            return e->b;
        }
        if (e->b->is_num && e->b->val == 0){
            return e->a;
        }
        if (e->a->is_num && e->b->is_num){
            return mk_num(e->a->val + e->b->val);
        }
    } else if (e->op == "-"){
        if (e->b->is_num && e->b->val == 0){
            return e->a;
        }
        if (e->a->is_num && e->b->is_num){
            return mk_num(e->a->val - e->b->val);
        }
    } else if (e->op == "*"){
        if ((e->a->is_num && e->a->val == 0) || (e->b->is_num && e->b->val == 0)){
            return mk_num(0);
        }
        if (e->a->is_num && e->a->val == 1){
            return e->b;
        }
        if (e->b->is_num && e->b->val == 1){
            return e->a;
        }
        if (e->a->is_num && e->a->val == -1 && e->b->is_num){
            return mk_num(-e->b->val);
        }
        if (e->b->is_num && e->b->val == -1 && e->a->is_num){
            return mk_num(-e->a->val);
        }
        if (e->a->is_num && e->b->is_num){
            return mk_num(e->a->val * e->b->val);
        }
    } else if (e->op == "/"){
        if (e->a->is_num && e->a->val == 0){
            return mk_num(0);
        }
        if (e->b->is_num && e->b->val == 1){
            return e->a;
        }
        if (e->a->is_num && e->b->is_num){
            return mk_num(e->a->val / e->b->val);
        }
    } else if (e->op == "^"){
        if (e->b->is_num && e->b->val == 0){
            return mk_num(1);
        }
        if (e->b->is_num && e->b->val == 1){
            return e->a;
        }
        if (e->a->is_num && e->b->is_num){
            return mk_num(pow(e->a->val, e->b->val));
        }
    }
    return e;
}

shared_ptr<Expr> mk_op(string op, shared_ptr<Expr> a, shared_ptr<Expr> b = nullptr){
    auto e = make_shared<Expr>();
    e->op = op;
    e->a = a;
    e->b = b;
    return simplify(e);
}

shared_ptr<Expr> derive(shared_ptr<Expr> e){
    if (e->is_num){
        return mk_num(0);
    }
    if (!e->var.empty()){
        return mk_num(1);
    }
    if (e->op == "+"){
        return mk_op("+", derive(e->a), derive(e->b));
    }
    if (e->op == "-"){
        return mk_op("-", derive(e->a), derive(e->b));
    }
    if (e->op == "*"){
        return mk_op("+", mk_op("*", derive(e->a), e->b), mk_op("*", e->a, derive(e->b)));
    }
    if (e->op == "/"){
        return mk_op("/", mk_op("-", mk_op("*", derive(e->a), e->b), mk_op("*", e->a, derive(e->b))), mk_op("^", e->b, mk_num(2)));
    }
    if (e->op == "^") {
        if (e->b->is_num) {
            return mk_op("*", derive(e->a), mk_op("*", mk_num(e->b->val), mk_op("^", e->a, mk_num(e->b->val - 1))));
        }
        return mk_op("*", mk_op("^", e->a, e->b), mk_op("+", mk_op("*", derive(e->b), mk_op("ln", e->a)), mk_op("*", e->b, mk_op("/", derive(e->a), e->a))));
    }
    if (e->op == "sin"){
        return mk_op("*", derive(e->a), mk_op("cos", e->a));
    }
    if (e->op == "cos"){
        return mk_op("*", derive(e->a), mk_op("*", mk_num(-1), mk_op("sin", e->a)));
    }
    if (e->op == "tan"){
        return mk_op("*", derive(e->a), mk_op("+", mk_num(1), mk_op("^", mk_op("tan", e->a), mk_num(2))));
    }
    if (e->op == "exp"){
        return mk_op("*", derive(e->a), mk_op("exp", e->a));
    }
    if (e->op == "ln"){
        return mk_op("*", derive(e->a), mk_op("/", mk_num(1), e->a));
    }
    return mk_num(0);
}

string to_string(shared_ptr<Expr> e){
    if (e->is_num){
        ostringstream out;
        out.precision(10);
        out << e->val;
        return out.str();
    }
    if (!e->var.empty()){
        return e->var;
    }
    if (e->b){
        return "(" + e->op + " " + to_string(e->a) + " " + to_string(e->b) + ")";
    }
    return "(" + e->op + " " + to_string(e->a) + ")";
}

std::string diff(const std::string &s)
{
//   return "";
    size_t i {0};
    return to_string(simplify(derive(simplify(parse(s, i)))));
}