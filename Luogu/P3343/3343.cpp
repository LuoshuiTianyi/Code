#pragma GCC diagnostic error "-std=c++11"
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3343.in", "r", stdin);
  freopen("3343.out", "w", stdout);
#endif
}
