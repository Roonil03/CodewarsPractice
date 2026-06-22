// #include <vector>
// #include <string>
// #include <regex>
#include <bits/stdc++.h>
using namespace std;

struct AST{
  string op;
  AST *a;
  AST *b;
  int n;
  AST(string op, AST *a, AST *b) : op(op), a(a), b(b), n(0) {}
  AST(string op, int n) : op(op), a(nullptr), b(nullptr), n(n) {}
};

struct Compiler {

  std::vector <std::string> compile (std::string program) {
    return pass3 (pass2 (pass1 (program)));
  }

  // Turn a program string into a vector of tokens.  Each token
  // is either '[', ']', '(', ')', '+', '-', '*', '/', a variable
  // name or a number (as a string)
  std::vector <std::string> tokenize (std::string program) {
    static std::regex re ("[-+*/()[\\]]|[A-Za-z]+|\\d+");
    std::sregex_token_iterator it (program.begin (), program.end (), re);
    return std::vector <std::string> (it, std::sregex_token_iterator ());
  }

  // Returns an un-optimized AST
  AST *pass1 (std::string program) {
    auto tokens = tokenize (program);
//     return 0;
    unordered_map<string, int> args;
    int i = 0;
    while (i < tokens.size() && tokens[i] != "["){
      i++;
    }
    i++;
    int ai = 0;
    while (i < tokens.size() && tokens[i] != "]"){
        args[tokens[i++]] = ai++;
    }
    i++;
    function<AST*(int&)> parse_expr, parse_term, parse_factor;
    parse_factor = [&](int &pos) -> AST*{
        if (tokens[pos] == "("){
            pos++;
            AST *node = parse_expr(pos);
            pos++;
            return node;
        } else if (isdigit(tokens[pos][0])){
            return new AST("imm", stoi(tokens[pos++]));
        } else{
            return new AST("arg", args[tokens[pos++]]);
        }
    };
    parse_term = [&](int &pos) -> AST*{
        AST *node = parse_factor(pos);
        while (pos < tokens.size() && (tokens[pos] == "*" || tokens[pos] == "/")){
            string op = tokens[pos++];
            AST *right = parse_factor(pos);
            node = new AST(op, node, right);
        }
        return node;
    };
    parse_expr = [&](int &pos) -> AST*{
        AST *node = parse_term(pos);
        while (pos < tokens.size() && (tokens[pos] == "+" || tokens[pos] == "-")){
            string op = tokens[pos++];
            AST *right = parse_term(pos);
            node = new AST(op, node, right);
        }
        return node;
    };
    return parse_expr(i);
  }

  // Returns an AST with constant expressions reduced
//   AST *pass2 (AST *ast);
  AST *pass2(AST *ast){
      if (!ast){
        return nullptr;
      }
      if (ast->op == "imm" || ast->op == "arg"){
        return ast;
      }
      ast->a = pass2(ast->a);
      ast->b = pass2(ast->b);
      if (ast->a->op == "imm" && ast->b->op == "imm"){
          int v1 = ast->a->n, v2 = ast->b->n;
          int res = 0;
          if (ast->op == "+"){
            res = v1 + v2;
          } else if (ast->op == "-"){
            res = v1 - v2;
          } else if (ast->op == "*"){
            res = v1 * v2;
          } else if (ast->op == "/"){
            res = v1 / v2;
          }
          return new AST("imm", res);
      }
      return ast;
  }

  // Returns assembly instructions
//   std::vector <std::string> pass3 (AST *ast);
  vector<string> pass3(AST *ast){
        vector<string> res;
        function<void(AST*)> gen = [&](AST *node){
            if (node->op == "imm"){
                res.push_back("IM " + to_string(node->n));
            } else if (node->op == "arg"){
                res.push_back("AR " + to_string(node->n));
            } else{
                gen(node->a);
                res.push_back("PU");
                gen(node->b);
                res.push_back("SW");
                res.push_back("PO");
                if (node->op == "+"){
                  res.push_back("AD");
                } else if (node->op == "-"){
                  res.push_back("SU");
                } else if (node->op == "*"){
                  res.push_back("MU");
                } else if (node->op == "/"){
                  res.push_back("DI");
                }
            }
        };
        gen(ast);
        return res;
    }
};