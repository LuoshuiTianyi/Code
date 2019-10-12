#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
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
const int Max_n = 505, Max_m = 1e4 + 5;
int n, m;
struct points {
  int hd[Max_n];
} V;
struct edges {
  int cntr, nx[Max_m], to[Max_m], w[Max_m];
} E;
void addr(points &V, edges &E, int u, int v, int w) {
  E.cntr++;
  E.nx[E.cntr] = V.hd[u], E.to[E.cntr] = v, E.w[E.cntr] = w;
  V.hd[u] = E.cntr;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4897.in", "r", stdin);
  freopen("4897.out", "w", stdout);
#endif
  n = read(), m = read();
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), w = read();
  }
}
