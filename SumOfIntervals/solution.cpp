// #include <vector>
// #include <utility>
#include <bits/stdc++.h>
using namespace std;

int sum_intervals(std::vector<std::pair<int, int>> intervals) {
  if(intervals.empty()){
    return 0;
  }
  sort(intervals.begin(), intervals.end());
  int sum {0}, start = intervals[0].first, end = intervals[0].second;
  for(auto& i : intervals){
    if(i.first <= end){
      end = max(end, i.second);
    } else{
      sum += end - start;
      start = i.first;
      end = i.second;
    }
  }
  return sum + (end - start);
}