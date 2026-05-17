#include <bits/stdc++.h>
using namespace std;

std::vector<int> move_zeroes(const std::vector<int>& input) {
  vector<int> res = input;
  fill(remove(res.begin(), res.end(), 0), res.end(), 0);
  return res;
}