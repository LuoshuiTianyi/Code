#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char s[1 << 26], *S = s;
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
  fread(s, 1, 1 << 26, stdin); 
  read(n), read(m), ans;
  for (int i = 1; i <= m; i++)
    read(e[i].u), read(e[i].v), read(e[i].w);
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= m; i++)
    ans = max(ans, e[i].w), M[e[i].w].push_back(i);
}
}  // namespace Init

namespace Solve {
int fa[Max_n], sz[Max_n];
int top, stk[Max_n], x[Max_n], y[Max_n];
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void merge(int id) {
  int u = e[id].u, v = e[id].v;
  //cout << "link: " << u << ", " << v << endl;
  u = find(u), v = find(v);
  if (find(u) == find(v)) return;
  if (sz[v] < sz[u]) swap(u, v);
  top++, stk[top] = id, x[top] = u, y[top] = v;
  fa[u] = v, sz[v] += sz[u];
}
void divid(int id) {
  if (stk[top] != id) return;
  //cout << "cut: " << e[id].u << ", " << e[id].v << endl;
  sz[y[top]] -= sz[x[top]], fa[x[top]] = x[top];
  top--;
}
void Enter(int x) {
  for (int i = M[x].size() - 1; ~i; i--) merge(M[x][i]);
}
void Back(int x) {
  for (int i = 0; i < M[x].size(); i++) divid(M[x][i]);
}
void dfs(int l, int r) {
  //cout << l << " " << r << endl;
  if (l == r) {
    if (sz[find(1)] == n) {
      cout << l;
      exit(0);
    }
    return;
  }
  int mid = l + r >> 1;
  for (int i = mid + 1; i <= r; i++) Enter(i);
  dfs(l, mid);
  for (int i = r; i > mid; i--) Back(i);
  for (int i = l; i <= mid; i++) Enter(i);
  dfs(mid + 1, r);
  for (int i = mid; i >= l; i--) Back(i);
}
void main() {
  ans++;
  for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
  dfs(0, V);
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
