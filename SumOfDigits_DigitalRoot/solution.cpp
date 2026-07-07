#include <bits/stdc++.h>
using namespace std;

int digital_root(int n)
{
    // ...
    return n ? 1 + (n - 1) % 9 : 0;
}