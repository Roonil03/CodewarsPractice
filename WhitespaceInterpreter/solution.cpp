// #include <map>
#include <bits/stdc++.h>
using namespace std;

// To help with debugging
std::string unbleach(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), [] (char c) { return (c == ' ') ? 's' : ((c == '\n') ? 'n' : 't'); });
  return s;
}

// Solution
std::string whitespace(const std::string &code_in, const std::string &inp = std::string())
{
    std::map<int, int > heap;
    std::vector<int> stack;
    std::string output;
    /// ...
    string code;
    for (char c : code_in){
        if (c == ' ' || c == '\t' || c == '\n'){
            code += c;
        }
    }    
        int n = code.length(), pc {0}, inp_ptr {0};vector<int> call_stack;
    map<string, int> labels;    
    auto read_num = [&]() -> int{    if (pc >= n){
            throw runtime_error("EOF");
        }
        char sign = code[pc++];
        if (sign == '\n'){
            throw runtime_error("Invalid sign");
        }
        int num {0};
        bool started = false;
        while (pc < n && code[pc] != '\n'){
            started = true;
            num = (num << 1) | (code[pc++] == '\t');
        }
        if (pc >= n){
            throw runtime_error("EOF");
        }
        pc++;
        return (sign == '\t') ? -num : num;
    };    
    auto read_label = [&]() -> string{
        string l = "";
        while (pc < n && code[pc] != '\n'){
            l += code[pc++];
        }
        if (pc >= n){
            throw runtime_error("EOF");
        }
        pc++;
        return l;
    };
    int scan_pc {0};
    while (scan_pc < n){
        char imp = code[scan_pc++];
        if (imp == ' '){
            if (scan_pc >= n) break;
            char cmd = code[scan_pc++];
            if (cmd == ' '){
                while (scan_pc < n && code[scan_pc] != '\n') scan_pc++;
                if (scan_pc < n) scan_pc++;
            } else if (cmd == '\t'){
                if (scan_pc >= n) break;
                char subcmd = code[scan_pc++];
                if (subcmd == ' ' || subcmd == '\n'){
                    while (scan_pc < n && code[scan_pc] != '\n') scan_pc++;
                    if (scan_pc < n) scan_pc++;
                }
            } else if (cmd == '\n'){
                if (scan_pc < n) scan_pc++;
            }
        } else if (imp == '\t'){
            if (scan_pc >= n) break;
            char cmd = code[scan_pc++];
            if (cmd == ' '){
                scan_pc += 2;
            } else if (cmd == '\t'){
                scan_pc += 1;
            } else if (cmd == '\n'){
                scan_pc += 2;
            }
        } else if (imp == '\n'){
            if (scan_pc >= n) break;
            char cmd = code[scan_pc++];
            if (cmd == ' '){
                if (scan_pc >= n) break;
                char subcmd = code[scan_pc++];
                string l = "";
                while (scan_pc < n && code[scan_pc] != '\n') l += code[scan_pc++];
                if (scan_pc < n) scan_pc++;
                
                if (subcmd == ' '){
                    if (labels.count(l)) throw runtime_error("Dup label");
                    labels[l] = scan_pc;
                }
            } else if (cmd == '\t'){
                if (scan_pc >= n) break;
                char subcmd = code[scan_pc++];
                if (subcmd == ' ' || subcmd == '\t'){
                    while (scan_pc < n && code[scan_pc] != '\n') scan_pc++;
                    if (scan_pc < n) scan_pc++;
                }
            } else if (cmd == '\n'){
                if (scan_pc < n) scan_pc++;
            }
        }
    }    
    auto pop = [&]() -> int{
        if (stack.empty()){
            throw runtime_error("Empty stack");
        }
        int val = stack.back();
        stack.pop_back();
        return val;
    };    
    while (pc < n){
        if (code[pc] == ' '){
            pc++;
            if (pc >= n){
                throw runtime_error("EOF");
            }
            if (code[pc] == ' '){
                pc++; stack.push_back(read_num());
            } else if (code[pc] == '\t'){
                pc++;
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                if (code[pc] == ' '){
                    pc++;
                    int nth = read_num();
                    if (nth < 0 || nth >= (int)stack.size()){
                        throw runtime_error("Invalid nth");
                    }
                    stack.push_back(stack[stack.size() - 1 - nth]);
                } else if (code[pc] == '\n'){
                    pc++;
                    int nth = read_num();
                    if (nth < 0 || nth >= (int)stack.size()){
                        stack.erase(stack.begin(), stack.end() - 1);
                    } else{
                        stack.erase(stack.end() - 1 - nth, stack.end() - 1);
                    }
                } else{
                    throw runtime_error("Invalid");
                }
            } else if (code[pc] == '\n'){
                pc++;
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                if (code[pc] == ' '){
                    pc++;
                    if (stack.empty()){
                        throw runtime_error("Empty");
                    }
                    stack.push_back(stack.back());
                } else if (code[pc] == '\t'){
                    pc++;
                    if (stack.size() < 2){
                        throw runtime_error("Empty");
                    }
                    swap(stack[stack.size() - 1], stack[stack.size() - 2]);
                } else if (code[pc] == '\n'){
                    pc++;
                    pop();
                }
            }
        } else if (code[pc] == '\t'){
            pc++;
            if (pc >= n){
                throw runtime_error("EOF");
            }
            if (code[pc] == ' '){
                pc++;
                if (pc >= n + 1){
                    throw runtime_error("EOF");
                }
                char op1 = code[pc++], op2 = code[pc++];
                int a = pop(), b = pop();
                if (op1 == ' ' && op2 == ' '){
                    stack.push_back(b + a);
                } else if (op1 == ' ' && op2 == '\t'){
                    stack.push_back(b - a);
                } else if (op1 == ' ' && op2 == '\n'){
                    stack.push_back(b * a);
                } else if (op1 == '\t' && op2 == ' '){
                    if (a == 0){
                        throw runtime_error("Div by 0");
                    }
                    stack.push_back(floor((double)b / a));
                } else if (op1 == '\t' && op2 == '\t'){
                    if (a == 0){
                        throw runtime_error("Mod by 0");
                    }
                    int res = b % a;
                    if ((b < 0 && a > 0) || (b > 0 && a < 0)){
                        if (res != 0){
                            res += a;
                        }
                    }
                    stack.push_back(res);
                } else{
                    throw runtime_error("Invalid");
                }
            } else if (code[pc] == '\t'){
                pc++;
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                char op = code[pc++];
                if (op == ' '){
                    int a = pop(), b = pop();
                    heap[b] = a;
                } else if (op == '\t'){
                    int a = pop();
                    if (!heap.count(a)){
                        throw runtime_error("Invalid heap");
                    }
                    stack.push_back(heap[a]);
                } else{
                    throw runtime_error("Invalid");
                }
            } else if (code[pc] == '\n'){
                pc++;
                if (pc >= n + 1){
                    throw runtime_error("EOF");
                }
                char op1 = code[pc++], op2 = code[pc++];
                if (op1 == ' ' && op2 == ' '){
                    output += (char)pop();
                } else if (op1 == ' ' && op2 == '\t'){
                    output += to_string(pop());
                } else if (op1 == '\t' && op2 == ' '){
                    if (inp_ptr >= (int)inp.length()){
                        throw runtime_error("No input");
                    }
                    int b = pop();
                    heap[b] = inp[inp_ptr++];
                } else if (op1 == '\t' && op2 == '\t'){
                    int b = pop();
                    string num = "";
                    while (inp_ptr < (int)inp.length() && inp[inp_ptr] != '\n'){
                        num += inp[inp_ptr++];
                    }
                    if (inp_ptr < (int)inp.length() && inp[inp_ptr] == '\n'){
                        inp_ptr++;
                    } else if (inp_ptr >= (int)inp.length()){
                        throw runtime_error("No input");
                    }
                    heap[b] = stoi(num);
                } else{
                    throw runtime_error("Invalid");
                }
            }
        } else if (code[pc] == '\n'){
            pc++;
            if (pc >= n){
                throw runtime_error("EOF");
            }
            char type1 = code[pc++];
            if (type1 == ' '){
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                char type2 = code[pc++];
                string l = read_label();
                if (type2 == ' '){
                    continue;
                } else if (type2 == '\t'){
                    if (!labels.count(l)){
                        throw runtime_error("Undef");
                    }
                    call_stack.push_back(pc);
                    pc = labels[l];
                } else if (type2 == '\n'){
                    if (!labels.count(l)){
                        throw runtime_error("Undef");
                    }
                    pc = labels[l];
                }
            } else if (type1 == '\t'){
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                char type2 = code[pc++];
                if (type2 == ' '){
                    string l = read_label();
                    if (pop() == 0){
                        if (!labels.count(l)){
                            throw runtime_error("Undef");
                        }
                        pc = labels[l];
                    }
                } else if (type2 == '\t'){
                    string l = read_label();
                    if (pop() < 0){
                        if (!labels.count(l)){
                            throw runtime_error("Undef");
                        }
                        pc = labels[l];
                    }
                } else if (type2 == '\n'){
                    if (call_stack.empty()){
                        throw runtime_error("Empty call");
                    }
                    pc = call_stack.back();
                    call_stack.pop_back();
                }
            } else if (type1 == '\n'){
                if (pc >= n){
                    throw runtime_error("EOF");
                }
                if (code[pc] == '\n'){
                    return output;
                } else{
                    throw runtime_error("Invalid exit");
                }
            }
        }
    }
    throw runtime_error("Unclean exit");
//     return output;
}
