#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
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

const int Max_n = 3e5 + 5, LIM = 1 << 20;
int n, m, Q;
int cnta, a[1001][1001];

int main() {
  freopen("3960.in", "r", stdin);
  freopen("3960.ans", "w", stdout);
  n = read(), m = read(), Q = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) a[i][j] = ++cnta;
  while (Q--) {
    int x = read(), y = read();
    cout << a[x][y] << endl;
    int tp = a[x][y];
    for (int i = y; i < m; i++) a[x][i] = a[x][i + 1];
    for (int i = x; i < n; i++) a[i][m] = a[i + 1][m];
    a[n][m] = tp;
  }
}
