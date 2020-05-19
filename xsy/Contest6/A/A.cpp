#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char s[1 << 25], *S = s;
#define getchar() (*S++)
template <typename T>
void read(T &x) {
  char ch = getchar();
  int fl = 0;
  x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  if (fl) x = -x;
}

const int Max_n = 2e6 + 5, V = 1e5;
int n, m, ans;
struct edge {
  int u, v, w;
} e[Max_n];
vector<int> M[(V << 2) + 10];

namespace Input {
void main() {
  fread(s, 1, 1 << 25, stdin); 
  read(n), read(m), ans = n + 1;
  for (int i = 1; i <= m; i++)
    read(e[i].u), read(e[i].v), read(e[i].w);
}
}  // namespace Input

namespace Init {
int L, R, x;
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l + r >> 1)
void add(int o, int l, int r) {
  if (R < L) return;
  if (l >= L && r <= R) {
    M[o].push_back(x);
    return;
  }
  if (mid >= L) add(ls, l, mid);
  if (mid < R) add(rs, mid + 1, r);
}
void main() {
  for (int i = 1; i <= m; i++) {
    x = i;
    L = 1, R = e[i].w - 1, add(1, 1, V);
    L = e[i].w + 1, R = V, add(1, 1, V);
  }
}
}  // namespace Init

namespace Solve {
int fa[Max_n];
int top, stk[Max_n];
void dfs(int x, int l, int r) {
  if (l == r) {
    return;
  }
}
void main() {
  for (int i = 1; i <= n; i++) 
  dfs(1, 1, V);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
