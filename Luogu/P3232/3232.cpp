#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
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
const int Max_n = 505;
int n, m;
int cntr, hd[Max_n], nx[Max_n * Max_n << 1], to[Max_n * Max_n << 1];
double in[Max_n], f[Max_n][Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3232.in", "r", stdin);
  freopen("3232.out", "w", stdout);
#endif
  n = read(), m = read();
  int u, v;
  for (int i = 1; i <= m; i++) {
    in[u = read()]++, in[v = read()]++;
    addr(u, v), addr(v, u);
  }
  for (int i = 1; i < n; i++) {
    f[i][i] = 1;
    go(i, j, v) if (v != n) f[i][v] = -1.0 / in[v];
  }
  f[1][n] = 1;
}
