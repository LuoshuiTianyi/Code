#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 5e5 + 5;
int n;
LL X[Max_n], R[Max_n];
namespace SGT {
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("5025.in", "r", stdin);
  freopen("5025.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) X[i] = read(), R[i] = read();
}
