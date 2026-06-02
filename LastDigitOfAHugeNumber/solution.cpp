#include <bits/stdc++.h>
using namespace std;

int last_digit(list<int> array) {
    // Write your code here
  vector<int> arr(array.begin(), array.end());
  if(arr.empty()){
    return 1;
  }
  int exp {1};
  for(auto it = arr.rbegin(); it != arr.rend() - 1; it++){
    int b = *it;
    if(exp == 0){
      exp = 1;
    } else if(b == 0){
      exp = 0;
    } else if(b == 1){
      exp = 1;
    } else if(exp == 1){
      exp = b < 4 ? b : (b % 4 + 4);
    } else{
      exp = (b % 2 == 0) ? 4 : (b % 4 == 1 ? 5 : (exp % 2 == 0 ? 5 : 7));
    }
  }
  int base = arr[0] % 10, res {1};
  for(int i {0}; i < exp; i++){
    res = (res * base) % 10;
  }
  return res;
}