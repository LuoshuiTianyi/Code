#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
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
const int Max_n = 1e5 + 5;
int n;
LL Ans[Max_n];
int cntr = 1, hd[Max_n], nx[Max_n << 1], to[Max_n << 1];
int num[Max_n], U[Max_n], V[Max_n], B[Max_n], C[Max_n];
int fa[Max_n], rk[Max_n], dn[Max_n];
int w;
struct node {
  int fa, v, siz, cnt, s[2];
};
struct Splay {
  vector<node> k;
  bool kd(int x) { return rs(k[x].fa) != x; }
  int nx(int x) { return k[x].v < x ? rs(x) : ls(x); }
  void splay(int x, int to) {
    for (int fa; (fa = k[x].fa) != to; rotate(x))
      
  }
  void add(int x) {
    
  }
} c[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
bool cmp(int x, int y) { return B[x] < B[y]; }
void build(int x, int f) {
  fa[x] = f;
  go(x, i, v) if (v != f) build(v, x);
}
void addc(int k, int x) {
  for (int i = k; i <= n; i += i & -i) c[i].add(x);
}
void delc(int k, int x) {
  for (int i = k; i <= n; i += i & -i) c[i].del(x);
}
void Count(int x, int f, LL ans) {
  
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) {
    U[i] = read(), V[i] = read(), B[i] = read(), C[i] = read(), num[i] = i;
    addr(U[i], V[i]), addr(V[i], U[i]);
  }
  sort(num + 1, num + n + 1, cmp);
  int cnt = 0;
  B[0] = -1;
  for (int i = 1; i <= n; i++) {
    if (B[num[i]] != B[num[i - 1]]) cnt++;
    B[num[i]] = cnt;
  }
  build(0, 0);
  for (int i = 1; i <= n; i++) {
    if (fa[U[i]] == V[i]) swap(U[i], V[i]);
    rk[V[i]] = B[i], dn[V[i]] = B[i];
  }
  Count(0, 0);
}
