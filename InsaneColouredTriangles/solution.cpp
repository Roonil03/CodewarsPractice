#include <bits/stdc++.h>
using namespace std;

char triangle(const string &row)
{
    int n = row.length();
    int sum = 0;
    int N = n - 1;
    for (int i = 0; i < n; ++i) {
        int val = (row[i] == 'R' ? 0 : (row[i] == 'G' ? 1 : 2));
        if (val == 0){
          continue;
          }
        int tempN = N, tempI = i, c = 1;
        while (tempI > 0 || tempN > 0) {
            int ni = tempN % 3;
            int ki = tempI % 3;
            if (ki > ni) {
              c = 0; break;
            }
            if (ki == 1 && ni == 2){
              c = (c * 2) % 3;
              }
            tempN /= 3;
            tempI /= 3;
        }
        sum = (sum + c * val) % 3;
    }
    if (N % 2 != 0){
      sum = (3 - sum) % 3;
      }
    return sum == 0 ? 'R' : (sum == 1 ? 'G' : 'B');
}