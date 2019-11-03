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
int x[Max_n], y[Max_n];
LL Ans[Max_n << 1];
bool qt[Max_n << 1];
vector<int> que[Max_n], pad[Max_n];

LL id(int x, int y) { return 1ll * (x - 1) * m + y; }

struct Tree {
  int t1, t2, ad[Max_n], dl[Max_n];
  int c[LIM + 1];
#define mid (l + r >> 1)
#define ls (o - (lowbit(o) >> 1))
#define rs (o + (lowbit(o) >> 1))
  void Init() {
    for (int p = 1; p < m; p++)
      for (int i = p; i <= LIM; i += i & -i) c[i]++;
  }
  void add(int k, int x) {
    if (x > 0)
      ad[++t1] = k;
    else
      dl[++t2] = k;
    for (int i = k; i <= LIM; i += i & -i) c[i] += x;
  }
  int lowbit(int x) { return x & -x; }
  int find(int k) {
    int l = 1, r = LIM, o = LIM >> 1;
    while (l < r) {
      if (c[o] >= k)
        o = ls, r = mid;
      else
        k -= c[o], o = rs, l = mid + 1;
    }
    return l;
  }
  void init() {
    while (t1)
      for (int i = ad[t1--]; i <= LIM; i += i & -i) c[i]--;
    while (t2)
      for (int i = dl[t2--]; i <= LIM; i += i & -i) c[i]++;
  }
} s;

namespace Input {
void main() {
  n = read(), m = read(), Q = read();
  for (int i = 1; i <= Q; i++) x[i] = read(), y[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) Ans[i] = id(i, m), s.add(i, 1);
  for (int i = 1; i <= Q; i++) {
    que[x[i]].push_back(i);
    int p = s.find(x[i]);
    pad[x[i]].push_back(p), s.add(p, -1), s.add(s.find(n - 1) + 1, 1);
  }
  s.init();
  s.Init();
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < que[i].size(); j++) {
      int x = que[i][j], p = s.find(y[x]);
      cout << i << " " << x << " " << y[x] << " " << p << endl;
      if (p < m) {
        cout << i << " " << x << " " << y[x] << " " << p << endl;
        Ans[n + x] = id(i, p);
      } else
        qt[x] = 1, Ans[x] = pad[i][p - m - 1];
      s.add(p, -1), s.add(s.find(m - 1) + 1, 1);
    }
    s.init();
  }
  for (int i = n + 1; i <= n + Q; i++) {
    if (qt[i]) Ans[i] = Ans[Ans[i]];
    printf("%lld\n", Ans[i]);
  }
}
}  // namespace Solve

int main() {
#ifdef Thyu
  freopen("3960.in", "r", stdin);
  freopen("3960.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
