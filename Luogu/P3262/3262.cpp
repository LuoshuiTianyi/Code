#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1 << 11;
int n, m;
int w1[Max_n][11], w2[Max_n][11];
int main() {
#ifndef ONLINE_JUDGE
  freopen("3262.in", "r", stdin);
  freopen("3262.out", "w", stdout);
#endif
  n = read(), m = read();
}
