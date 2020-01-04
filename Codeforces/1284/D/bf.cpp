#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
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

const int Max_n = 1e5 + 5, mod = 998244353;
int n;
int cnt, t[Max_n], c1[Max_n * 10], c2[Max_n * 10];
struct q {
  int la, ra, lb, rb;
} k[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++)
    k[i].la = read(), k[i].ra = read(), k[i].lb = read(), k[i].rb = read();
}
}  // namespace Input

namespace Solve {
bool qry(int l1, int r1, int l2, int r2) {
  return max(l1, l2) <= min(r1, r2);
}
bool query(q a, q b) {
  return !(qry(a.la, a.ra, b.la, b.ra) ^ qry(a.lb, a.rb, b.lb, b.rb));
}
void main() {
  bool ans = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      ans &= query(k[i], k[j]);
    }
  cout << (ans ? "YES" : "NO");
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.ans", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
