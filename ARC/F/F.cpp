#include <algorithm>
#include <cmath>
#include <complex>
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
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5;
int n;
int cntr, hd[Max_n], nx[Max_n << 2], to[Max_n << 2], w[Max_n << 2];
bool vis[Max_n], bk[Max_n << 2];
void addr(int u, int v, int W) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
  hd[u] = cntr;
}
void build(int x) {
  //for (int i = hd[x]; i; i = nx[i])
    
}
void Solve(int x) {
  build(x);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("F.in", "r", stdin);
  freopen("F.out", "w", stdout);
#endif
  n = read();
  int x, y;
  cntr = 1;
  for (int i = 1; i <= n; i++) {
    x = read(), y = read();
    addr(x, y + n, x + y), addr(y + n, x, x + y);
  }
  for (int i = 1; i <= n; i++) 
    if (!vis[i]) {
      Solve(i);
    }
}
