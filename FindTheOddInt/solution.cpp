// #include <vector>
#include <bits/stdc++.h>
using namespace std;

int findOdd(const std::vector<int>& numbers){
  //your code here
    int res {0};
    for(int n : numbers){
        res ^= n;
    }
    return res;
}