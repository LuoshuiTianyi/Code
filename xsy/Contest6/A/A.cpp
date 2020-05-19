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
  read(n), read(m), ans;
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
    x = i, ans = max(ans, e[i].w);
    L = 0, R = e[i].w - 1, add(1, 0, V);
    L = e[i].w + 1, R = V, add(1, 0, V);
  }
}
}  // namespace Init

namespace Solve {
int fa[Max_n], sz[Max_n];
int top, stk[Max_n], x[Max_n], y[Max_n];
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void merge(int id) {
  int u = e[id].u, v = e[id].v;
  u = find(u), v = find(v);
  if (find(u) == find(v)) return;
  top++, stk[top] = id, x[top] = u, y[top] = v;
  fa[u] = v, sz[v] += sz[u];
}
void divid(int id) {
  if (stk[top] != id) return;
  sz[y[top]] -= sz[x[top]], fa[x[top]] = x[top];
  top--;
}
void Enter(int o) {
  for (int i = M[o].size() - 1; ~i; i--) merge(M[o][i]);
}
void Back(int o) {
  for (int i = 0; i < M[o].size(); i++) divid(M[o][i]);
}
void dfs(int o, int l, int r) {
  Enter(o);
  if (l == r) {
    if (sz[find(1)] == n) ans = min(ans, l);
    Back(o);
    return;
  }
  dfs(ls, l, mid), dfs(rs, mid + 1, r);
  Back(o);
}
void main() {
  ans++;
  for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
  dfs(1, 0, V);
  cout << ans << endl;
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
