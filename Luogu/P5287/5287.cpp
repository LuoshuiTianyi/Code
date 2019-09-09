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
const int Max_n = 1e5 + 5, mod = 998244353;
int n;
long long Ans[Max_n];
int f[Max_n], l[Max_n], len[Max_n], sum[Max_n];
char P[Max_n], c[Max_n];
int cntr, hd[Max_n], nx[Max_n], to[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
void Mod(long long &x) { x %= mod; }
void calc(int x, int L, long long ans) {
  if (len[x]) {
    if (!L) Mod(ans = (len[x] - 1) * len[x] / 2);
    int maxx = 0, now = f[L], lastgap = 0;
    for (int i = f[L]; ~i; i = f[i]) {
      if (P[i + 1] == c[x] && min(l[i + 1], len[x]) > maxx) {
        int tp = maxx;
        maxx = min(l[i + 1], len[x]);
        Mod(ans +=
            1ll * (maxx - tp) * sum[i] + (maxx - tp) * (tp + 1 + maxx) / 2);
      }
      if (i - f[i] == lastgap && i) i = i % lastgap + lastgap;
      lastgap = i - f[i];
    }
    if (c[x] == P[1] && L) Mod(ans += (len[x] - maxx) * l[1]);
    lastgap = 0;
    f[L + 1] = 0;
    for (int i = f[L++]; ~i; i = f[i]) {
      if (P[1] == c[x] && l[1] <= len[x]) f[L] = 1;
      if (P[i + 1] == c[x] && l[i + 1] == len[x]) {
        f[L] = i + 1;
        break;
      }
      if (i - f[i] == lastgap && i) i = i % lastgap + lastgap;
      lastgap = i - f[i];
    }
    P[L] = c[x], sum[L] = sum[L - 1] + (l[L] = len[x]);
  }
  Ans[x] = ans;
  for (int i = hd[x]; i; i = nx[i]) calc(to[i], L, ans);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("5287.in", "r", stdin);
  freopen("5287.out", "w", stdout);
#endif
  scanf("%d", &n);
  int opt, x;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &opt, &x);
    if (opt == 2) {
      addr(x, i);
    } else {
      addr(i - 1, i);
      scanf(" %c", &c[i]);
      len[i] = x;
    }
  }
  f[0] = -1;
  calc(0, 0, 0);
  for (int i = 1; i <= n; i++) printf("%lld\n", Ans[i]);
}
