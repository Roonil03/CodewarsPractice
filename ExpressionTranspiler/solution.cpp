#include <bits/stdc++.h>
using namespace std;

// char *cat (const char *s0, ...);              // cat all strings together, stop at argument value 0
// char *segment (const char *s, const char *e); // create string from characters between s (inclusive) and e (exclusive)

// struct list;

// list *node (void *data);           // create one-element list
// list *concat (list *l1, list *l2); // concatenate two lists, modifies l1

// string transpile_str(const string& expression) {
//     vector<string> tokens;
//     regex token_regex(R"([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+|\{|\}|\(|\)|->|,|[^ \n\r\t]+)");
//     auto words_begin = sregex_iterator(expression.begin(), expression.end(), token_regex);
//     auto words_end = sregex_iterator();
//     for (sregex_iterator i = words_begin; i != words_end; i++){
//         smatch match = *i;
//         string token = match.str();
//         if (token == "{" || token == "}" || token == "(" || token == ")" || token == "->" || token == ","){
//             tokens.push_back(token);
//         } else if (regex_match(token, regex(R"([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+)"))){
//             tokens.push_back(token);
//         } else{
//              return "";
//         }
//     }
//     size_t pos = 0;
//     auto match = [&](const string& expected) -> bool{
//         if (pos < tokens.size() && tokens[pos] == expected){
//             pos++;
//             return true;
//         }
//         return false;
//     };
//     auto peek = [&](const string& expected) -> bool{
//          return (pos < tokens.size() && tokens[pos] == expected);
//     };    
//     auto is_name_or_number = [&]() -> bool{
//         if (pos < tokens.size()){
//              string t = tokens[pos];
//              return t != "{" && t != "}" && t != "(" && t != ")" && t != "->" && t != ",";
//         }
//         return false;
//     };
//     auto consume_name_or_number = [&]() -> string{
//         if (is_name_or_number()){
//             return tokens[pos++];
//         }
//         return "";
//     };
//     function<string()> parse_expression;
//     function<string()> parse_lambda;
//     function<string()> parse_function;    
//     parse_lambda = [&]() -> string{
//         if (!match("{")){
//           return "";
//         }
//         string params = "";
//         string stmts = "";        
//         size_t saved_pos = pos;
//         bool has_arrow = false;
//         while(pos < tokens.size() && tokens[pos] != "}" && tokens[pos] != "->"){
//             pos++;
//         }
//         if (pos < tokens.size() && tokens[pos] == "->") {
//             has_arrow = true;
//         }
//         pos = saved_pos;
//         if (has_arrow){
//             while(pos < tokens.size() && tokens[pos] != "->"){
//                 string p = consume_name_or_number();
//                 if (p == ""){
//                   return "";
//                 }
//                 params += p;
//                 if (match(",")){
//                     params += ",";
//                 } else if (peek("->")){
//                     break;
//                 } else{
//                     return "";
//                 }
//             }
//             if (!match("->")){
//               return "";
//             }
//         }        
//         while(pos < tokens.size() && tokens[pos] != "}"){
//             string s = consume_name_or_number();
//             if (s == ""){
//               return "";
//             }
//             stmts += s + ";";
//         }        
//         if (!match("}")){
//           return "";        
//         }
//         return "(" + params + "){" + stmts + "}";
//     };
//     parse_expression = [&]() -> string{
//         if (peek("{")){
//             return parse_lambda();
//         } else if (is_name_or_number()){
//             return consume_name_or_number();
//         }
//         return "";
//     };
//     parse_function = [&]() -> string{
//         string expr = parse_expression();
//         if (expr == ""){
//           return "";        
//         }
//         string params = "";
//         bool has_parens = false;        
//         if (match("(")){
//             has_parens = true;
//             if (!peek(")")){
//                 while(true){
//                     string p = parse_expression();
//                     if (p == ""){
//                       return "";
//                     }
//                     params += p;
//                     if (match(",")){
//                         params += ",";
//                     } else{
//                         break;
//                     }
//                 }
//             }
//             if (!match(")")){
//               return "";
//             }
//         }        
//         if (peek("{")){
//             string lam = parse_lambda();
//             if (lam == ""){
//               return "";
//             }
//             if (params != ""){
//                 params += "," + lam;
//             } else{
//                 params = lam;
//             }
//             has_parens = true;
//         }        
//         if (has_parens){
//              return expr + "(" + params + ")";
//         } else{
//              return expr;
//         }
//     };    
//     string res = parse_function();
//     if (res != "" && pos == tokens.size()) {
//         return res;
//     }    
//     return "";
// }

const char *transpile (const char* expression) {
//   return "";
    if (!expression){
        return "";
    }
    string expr_str(expression);
    vector<string> tokens;
    for (size_t i = 0; i < expr_str.length(); ){
        char c = expr_str[i];
        if (isspace(c)){
            i++;
            continue;
        }
        if (c == '(' || c == ')' || c == '{' || c == '}' || c == ','){
            tokens.push_back(string(1, c));
            i++;
            continue;
        }
        if (c == '-' && i + 1 < expr_str.length() && expr_str[i+1] == '>'){
            tokens.push_back("->");
            i += 2;
            continue;
        }
        if (isalpha(c) || c == '_'){
            string t = "";
            while (i < expr_str.length() && (isalnum(expr_str[i]) || expr_str[i] == '_')){
                t += expr_str[i++];
            }
            tokens.push_back(t);
            continue;
        }
        if (isdigit(c)){
            string t = "";
            while (i < expr_str.length() && isdigit(expr_str[i])){
                t += expr_str[i++];
            }
            if (i < expr_str.length() && (isalpha(expr_str[i]) || expr_str[i] == '_')){
                return "";
            }
            tokens.push_back(t);
            continue;
        }
        return "";
    }

    size_t pos = 0;
    auto peek = [&]() -> string{
        return pos < tokens.size() ? tokens[pos] : "";
    };
    auto match = [&](const string& s){
        if (peek() == s){
            pos++;
            return true;
        }
        return false;
    };
    auto is_name_or_number = [&](){
        string p = peek();
        return !p.empty() && p != "(" && p != ")" && p != "{" && p != "}" && p != "," && p != "->";
    };

    function<string()> parse_expression;
    function<string()> parse_lambda = [&]() -> string{
        if (!match("{")){
            return "";
        }
        size_t temp = pos;
        bool has_arrow = false;
        while (temp < tokens.size() && tokens[temp] != "}" && tokens[temp] != "->"){
            temp++;
        }
        if (temp < tokens.size() && tokens[temp] == "->"){
            has_arrow = true;
        }
        string params = "";
        if (has_arrow){
            while (true){
                if (!is_name_or_number()){
                    return "";
                }
                params += tokens[pos++];
                if (match(",")){
                    params += ",";
                } else if (peek() == "->"){
                    break;
                } else{
                    return "";
                }
            }
            match("->");
        }
        string stmts = "";
        while (peek() != "}"){
            if (!is_name_or_number()){
                return "";
            }
            stmts += tokens[pos++] + ";";
        }
        if (!match("}")){
            return "";
        }
        return "(" + params + "){" + stmts + "}";
    };

    parse_expression = [&]() -> string{
        if (peek() == "{"){
            return parse_lambda();
        }
        if (is_name_or_number()){
            return tokens[pos++];
        }
        return "";
    };

    auto parse_parameters = [&]() -> string{
        string res = parse_expression();
        if (res == ""){
            return "";
        }
        while (match(",")){
            string nxt = parse_expression();
            if (nxt == ""){
                return "";
            }
            res += "," + nxt;
        }
        return res;
    };

    auto parse_function = [&]() -> string{
        string expr = parse_expression();
        if (expr == ""){
            return "";
        }
        bool is_func = false;
        string params = "";
        if (match("(")){
            is_func = true;
            if (peek() != ")"){
                params = parse_parameters();
                if (params == ""){
                    return "";
                }
            }
            if (!match(")")){
                return "";
            }
        }
        if (peek() == "{"){
            string lam = parse_lambda();
            if (lam == ""){
                return "";
            }
            if (!params.empty()){
                params += ",";
            }
            params += lam;
            is_func = true;
        }
        if (is_func){
            return expr + "(" + params + ")";
        }
        return "";
    };
    string res = parse_function();
    if (res == "" || pos != tokens.size()){
        return "";
    }
    char* out = new char[res.length() + 1];
    strcpy(out, res.c_str());
    return out;
}

// char* cat(const char* s0, ...) {
//     va_list args;
//     va_start(args, s0);
//     size_t len = 0;
//     const char* s = s0;
//     while (s != nullptr){
//         len += strlen(s);
//         s = va_arg(args, const char*);
//     }
//     va_end(args);
//     char* res = new char[len + 1];
//     res[0] = '\0';
//     va_start(args, s0);
//     s = s0;
//     while (s != nullptr){
//         strcat(res, s);
//         s = va_arg(args, const char*);
//     }
//     va_end(args);
//     return res;
// }

// char* segment(const char* s, const char* e){
//     if (s == nullptr || e == nullptr || s >= e){
//         char* empty = new char[1];
//         empty[0] = '\0';
//         return empty;
//     }
//     size_t len = e - s;
//     char* res = new char[len + 1];
//     strncpy(res, s, len);
//     res[len] = '\0';
//     return res;
// }


