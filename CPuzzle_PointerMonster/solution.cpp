#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

char a[4][7] = {"Common", "Point", "Boost", "Better"};
// /* Insert type here */ char (*b[4])[7] = {a+3, a+1, a, a+2};

char (*b[4])[7] = {a+3, a+1, a, a+2};

// /* Insert type here */ char (*(*C(void))[4])[7]
// {
//     return &b;
// }

// /* Insert type here */ char (**d(void))[7]
// {
//     return C()[1] - 3 /*()[1] - 3*/;
// }

// char buf[256];

// char *pointer_monster(/* Insert type here */ char (**(*f)(void))[7])
// {
//     int len;
    
//     len  = sprintf(buf, "%s", *f()[0]);
//     len += sprintf(buf + len, "%s ", *((**f)()-1)[0]+4);
//     len += sprintf(buf + len, "%s", (*f())[0]-4);
//     len += sprintf(buf + len, "%s", f()[1][2]+3);
//     len += sprintf(buf + len, "%s", *((**f)()-1)[0]+4);
//     return buf;
// }

char (*(*C(void))[4])[7]
{
    return &b;
}

char (**d(void))[7]
{
    return C()[1] - 3;
}

char buf[256];

char *pointer_monster(char (**(*f)(void))[7])
{
    int len;
    
    len  = sprintf(buf, "%s", *f()[0]);
    len += sprintf(buf + len, "%s ", *((**f)()-1)[0]+4);
    len += sprintf(buf + len, "%s", (*f())[0]-4);
    len += sprintf(buf + len, "%s", f()[1][2]+3);
    len += sprintf(buf + len, "%s", *((**f)()-1)[0]+4);
    return buf;
}