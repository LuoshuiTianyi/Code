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
const int Max_n = 1e3 + 5, mod = 1e9 + 7;
int n, a, b;
int pa, pb, pp;
int f[Max_n][Max_n];
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
int DP(int a, int ab) {
  int &res = f[a][ab];
  if (res != -1) return res;
  if (a + ab >= n) {
    res = (a + ab + pp) % mod;
    return res;
  }
  return res =
             (1ll * pa * DP(a + 1, ab) % mod + 1ll * pb * DP(a, ab + a) % mod) %
             mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read(), a = read(), b = read();
  pa = 1ll * a * ksm(a + b, mod - 2) % mod;
  pb = 1ll * b * ksm(a + b, mod - 2) % mod;
  pp = 1ll * a * ksm(b, mod - 2) % mod;
  memset(f, -1, sizeof(f));
  printf("%d\n", DP(1, 0));
}
