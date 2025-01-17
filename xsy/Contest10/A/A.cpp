#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 2e6 + 5, Max_k = 1e3 + 5;
int n, K;
int top, stk[Max_n], m[Max_n];
LL f[Max_k], g[Max_k];
vector<LL> a[Max_n];
bool vis[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read();
  for (int i = 1; i <= n; i++) {
    a[i].resize(1 + (m[i] = read()), 0);
    for (int j = 0; j <= m[i]; j++) a[i][j + !j] += read();
    m[i] = min(m[i], K);
    for (int j = 2; j <= m[i]; j++) a[i][j] += a[i][j - 1];
  }
}
}  // namespace Input

namespace Init {
bool cmp(vector<LL> a, vector<LL> b) { return a.size() < b.size(); }
int t;
pair<LL, int> s[Max_n];
void main() {
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1, p = 1; i <= K; i++) {
    while (p <= n && a[p].size() - 1 < i) p++;
    if (p > n) break;
    t = 0;
    for (int j = p; j <= n; j++) t++, s[t].first = a[j][i], s[t].second = j;
    int tot = min((K + i - 1) / i, n - p + 1);
    nth_element(s + 1, s + tot, s + t + 1);
    for (int i = 1; i <= tot; i++)
      if (!vis[s[i].second])
        vis[stk[++top] = s[i].second] = 1;
  }
}
}  // namespace Init

namespace Solve {
void Solve(int l, int r, int L, int R, int id) {
  if (l > r) return;
  int mid = l + r >> 1;
  int best = mid;
  f[mid] = 2e18;
  for (int i = L; i <= R; i++)
    if (i < mid && mid - i <= a[id].size() - 1)
      if (g[i] + a[id][mid - i] < f[mid])
        f[mid] = g[i] + a[id][mid - i], best = i;
  Solve(l, mid - 1, L, best, id), Solve(mid + 1, r, best, R, id);
}
void main() {
  for (int i = 1; i <= K; i++) f[i] = 2e18;
  for (int i = 1; i <= top; i++) {
    swap(f, g);
    Solve(1, K, 0, K, stk[i]);
    for (int j = 1; j <= K; j++) f[j] = min(f[j], g[j]);
  }
  for (int i = 1; i <= K; i++) cout << f[i] << " ";
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
