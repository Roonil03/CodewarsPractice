#include <bits/stdc++.h>
using namespace std;

std::string format_duration(int seconds) {
  // your code here
  if(seconds == 0){
    return "now";
  }
  vector<pair<int, string>> units={
    {31536000, "year"},
    {86400, "day"},
    {3600, "hour"},
    {60, "minute"},
    {1, "second"}
  };
  vector<string> parts;
  for(const auto& [val, name] : units){
    int count = seconds / val;
    if(count > 0){
      parts.push_back(to_string(count) + " " + name + (count > 1 ? "s" : ""));
      seconds %= val;
    }
  }
  string res = parts[0];
  for(size_t i {1}; i < parts.size(); i++){
    if(i == parts.size() - 1){
      res += " and " + parts[i];
    } else{
      res += ", " + parts[i];
    }
  }
  return res;
}