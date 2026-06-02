#include <bits/stdc++.h>
using namespace std;

double e(const string& str, size_t& i);

void s(const string& str, size_t& i){
  while(i < str.size() && isspace(str[i])){
    i++;
  }
}

double f(const string& str, size_t& i){
  s(str, i);
  if(str[i] == '-'){
    i++;
    return -f(str, i);
  }
  if(str[i] == '('){
    i++;
    double r = e(str, i);
    s(str, i);
    i++;
    return r;
  }
  char* end;
  double r = strtod(str.data() + i, &end);
  i = end - str.data();
  return r;
}

double t(const string& str, size_t& i){
  double r = f(str, i);
  while(true){
    s(str, i);
    if(i >= str.size()){
      break;
    }
    if(str[i] == '*'){
      i++;
      r *= f(str, i);
    } else if(str[i] == '/'){
      i++;
      r /= f(str, i);
    } else{
      break;
    }
  }
  return r;
}

double e(const string& str, size_t& i){
  double r = t(str, i);
  while(true){
    s(str, i);
    if(i >= str.size()){
      break;
    }
    if(str[i] == '+'){
      i++;
      r += t(str, i);
    } else if(str[i] == '-'){
      i++;
      r -= t(str, i);
    } else{
      break;
    }
  }
  return r;
}

double calc(std::string expression) {
  size_t i = 0;
  return e(expression, i);
}