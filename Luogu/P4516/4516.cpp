#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5, mod = 1e9 + 7;
int n, K;
int cntr, hd[Max_n], nx[Max_n << 1], to[Max_n << 1];
int f[Max_n][105][2][2];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
void DP(int x, int fa) {
  for (int i = hd[x]; i; i = nx[i])
    if (to[i] != fa) {
      DP(to[i], x);
    }
}
int main() {
  freopen("4516.in", "r", stdin);
  freopen("4516.out", "w", stdout);
  n = read(), K = read();
  int u, v;
  for (int i = 1; i < n; i++) {
    u = read(), v = read();
    addr(u, v), addr(v, u);
  }
  DP(1, 0);
}
