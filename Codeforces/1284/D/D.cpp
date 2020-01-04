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
int cnt, t[Max_n * 10], c1[Max_n * 10], c2[Max_n * 10], c3[Max_n * 10], c4[Max_n * 10];
struct q {
  int la, ra, lb, rb;
} k[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    k[i].la = read(), k[i].ra = read(), k[i].lb = read(), k[i].rb = read();
    t[++cnt] = k[i].la;
    t[++cnt] = k[i].ra;
    t[++cnt] = k[i].lb;
    t[++cnt] = k[i].rb;
  }
}
}  // namespace Input

namespace Init {
void Get(int &x) {
  x = lower_bound(t + 1, t + cnt + 1, x) - t;
}
void main() {
  srand((unsigned)time(NULL));
  sort(t + 1, t + cnt + 1);
  for (int i = 1; i <= n; i++) {
    Get(k[i].la), Get(k[i].ra), Get(k[i].lb), Get(k[i].rb);
    int x = rand() % mod;
    cout << x << endl;
    (c1[k[i].la] += x) %= mod, (c1[k[i].ra] += -x) %= mod;
    (c2[k[i].lb] += x) %= mod, (c2[k[i].rb] += -x) %= mod;
    (c3[k[i].la] += x) %= mod;
    (c4[k[i].lb] += x) %= mod;
  }
  for (int i = 1; i <= cnt; i++) ((c1[i] += c1[i - 1]) %= mod + mod) %= mod;
  for (int i = 1; i <= cnt; i++) ((c2[i] += c2[i - 1]) %= mod + mod) %= mod;
}
}  // namespace Init

namespace Solve {
void main() {
  bool ans = 1;
  for (int i = 1; i <= n; i++) {
    int x1 = query(c1, k[i].la), x2 = query(c2, k[i].lb);
    int x3 = query(c1, k[i].ra), x4 = query(c2, k[i].rb);
    cout << x1 << " " << x2 << " " << x3 << " " << x4 << endl;
    ans &= ((x1 == x2) | (x1 == x4) | (x3 == x2) | (x3 == x4));
  }
  cout << (ans ? "YES" : "NO");
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
