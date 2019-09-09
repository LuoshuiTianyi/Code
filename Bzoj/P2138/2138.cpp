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
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
const int Max_n = 4e4 + 5;
int n, m, x, y, z, mod, Ans;
int s[Max_n];
int f[Max_n << 2], g[Max_n << 2], tagf[Max_n << 2], tagg[Max_n << 2];
int L, R, ans;
int ned[Max_n], ln, rn;
bool fl;
int sqr(int x) { return x * x; }
void pushup(int *f, int o) {
  if (!fl)
    f[o] = min(f[ls], f[rs]);
  else
    f[o] = max(f[ls], f[rs]);
}
void pushdown(int *f, int *t, int o) {
  t[ls] += t[o], f[ls] += t[o];
  t[rs] += t[o], f[rs] += t[o];
  t[o] = 0;
}
void build(int *f, int o, int l, int r) {
  if (l == r) {
    if (!fl)
      f[o] = s[l];
    else
      if (l) f[o] = s[l - 1];
    return;
  }
  build(f, ls, l, mid);
  build(f, rs, mid + 1, r);
  pushup(f, o);
}
void query(int *f, int *t, int o, int l, int r) {
  if (L > R) return;
  if (l >= L && r <= R) {
    if (!fl)
      ans = min(ans, f[o]);
    else
      ans = max(ans, f[o]);
    return;
  }
  pushdown(f, t, o);
  if (mid >= L) query(f, t, ls, l, mid);
  if (mid < R) query(f, t, rs, mid + 1, r);
  pushup(f, o);
}
void add(int *f, int *t, int o, int l, int r) {
  if (L > R) return;
  if (l >= L && r <= R) {
    f[o] += ans, t[o] += ans;
    return;
  }
  pushdown(f, t, o);
  if (mid >= L) add(f, t, ls, l, mid);
  if (mid < R) add(f, t, rs, mid + 1, r);
  pushup(f, o);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("2138.in", "r", stdin);
  freopen("2138.out", "w", stdout);
#endif
  n = read(), x = read(), y = read(), z = read(), mod = read();
  for (int i = 1; i <= n; i++) {
    s[i] = (sqr(x - i) % mod + sqr(y - i) % mod + sqr(z - i) % mod) % mod;
    s[i] += s[i - 1];
  }
  fl = 0, build(f, 1, 0, n);
  fl = 1, build(g, 1, 0, n);
  m = read();
  ned[1] = read(), ned[2] = read();
  x = read(), y = read(), z = read(), mod = read();
  for (int i = 3; i <= m; i++)
    ned[i] = (x * ned[i - 1] % mod + y * ned[i - 2] % mod + z) % mod;
  for (int q = 1; q <= m; q++) {
    ln = read(), rn = read();
    ans = -2e9, fl = 1, L = 1, R = ln;
    query(g, tagg, 1, 0, n);
    Ans = -ans, ans = 2e9, fl = 0, L = rn, R = n;
    query(f, tagf, 1, 0, n);
    Ans = min(Ans + ans, ned[q]);
    printf("%d\n", Ans);
    fl = 1, L = ln + 1, ans = -Ans;
    add(g, tagg, 1, 0, n);
    fl = 0, L = rn;
    add(f, tagf, 1, 0, n);
  }
}
