#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
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

const int Max_n = 2e5 + 5;
int n, m, cnt, ans = 1e9;
int fa[Max_n];
struct edge {
  int u, v, a;
} e[Max_n];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct node {
  int fa, v, Max, tag, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
int Max(int x, int y) { return k[x].v > k[y].v ? x : y; }
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
void upd(int x) {
  k[x].Max = Max(x, Max(ls(x), rs(x)));
}
void roll(int x) {
  if (!x) return;
  swap(ls(x), rs(x)), k[x].tag ^= 1;
}
void pushdown(int x) {
  if (k[x].tag) k[x].tag = 0, roll(ls(x)), roll(rs(x));
}
void rotate(int x) {
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  k[x].fa = z, k[y].fa =x, upd(y);
}
void Push(int x) {
  if (nrt(x)) Push(k[x].fa);
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(fa) ^ kd(x) ? x : fa);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y, upd(x);
}
void makert(int x) {
  access(x), splay(x), roll(x);
}
int findrt(int x) {
  access(x), splay(x);
  while (ls(x)) pushdown(x), x = ls(x);
  return x;
}
void link(int x, int y) {
  cout << "link: " << x << "," << y << endl;
  makert(x), k[x].fa = y;
}
void cut(int x, int y) {
  cout << "cut: " << x << "," << y << endl;
  makert(x), access(y), splay(y);
  ls(y) = k[x].fa = 0, upd(y);
}
void Print(int x) {
  if (!x) return;
  Print(ls(x)), cout << x << " " << k[x].v << " " << k[x].Max << endl, Print(rs(x));
}
int query(int x, int y) {
  makert(x), access(y), splay(y);
  //Print(y);
  upd(y);
  cout << x << " " << y << " " << k[y].Max << endl;
  return k[y].Max;
}
}  // namespace LCT

namespace Input {
void main() {
  n = cnt = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read(), a = read();
    k[++cnt].v = read();
    e[cnt] = (edge){u, v, a};
  }
}
}  // namespace Input

namespace Init {
bool cmp(edge x, edge y) { return x.a < y.a; }
void main() {
  sort(e + n + 1, e + cnt + 1, cmp);
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) fa[i] = i;
  for (int i = n + 1; i <= 7; i++) {
    int u = e[i].u, v = e[i].v;
    if (find(u) != find(v)) {
      LCT::link(i, u), LCT::link(i, v);
      fa[find(u)] = find(v);
    } else {
      int x = LCT::query(u, v);
      if (k[x].v > k[i].v) {
        LCT::cut(x, e[x].u), LCT::cut(x, e[x].v);
        LCT::link(i, u), LCT::link(i, v);
      }
    }
    if (find(1) == find(n)) {
      ans = min(ans, e[i].a + k[LCT::query(1, n)].v);
      //cout << ans << " " << LCT::query(1, n) << endl;
    }
  }
  //cout << (ans == 1e9 ? -1 : ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2387.in", "r", stdin);
  freopen("2387.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
