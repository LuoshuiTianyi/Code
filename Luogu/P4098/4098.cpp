#include <algorithm>
#include <cstdio>
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

const int Max_n = 5e4 + 5;
int n;
int a[Max_n], id[Max_n];
int bf[Max_n], nx[Max_n], L1[Max_n], L2[Max_n], R1[Max_n], R2[Max_n];
int stk[Max_n];

namespace Trie {
int cnt, rt[Max_n], ch[Max_n * 32][2], tot[Max_n * 32];
void add(int now, int &o, int dep) {
  o = ++cnt;
  if (dep < 0) {
    tot[o] = 1;
    return;
  }
  ch[o][0] = ch[now][0], ch[o][1] = ch[now][1];
  add(ch[now][stk[dep]], ch[o][stk[dep]], dep - 1);
  tot[o] = tot[ch[o][0]] + tot[ch[o][1]];
}
}  // namespace Trie
using namespace Trie;

namespace Input {
void main() { 
  n = read(); 
  for (int i = 1; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Init {
bool cmp(int x, int y) { return a[x] < a[y]; }
void main() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0, x = a[i]; j <= 30; j++, x >>= 1) stk[j] = x & 1;
    add(rt[i - 1], rt[i], 30);
  }
  for (int i = 1; i <= n; i++) nx[i] = i + 1, bf[i] = i - 1, id[i] = i;
  sort(id + 1, id + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    int x = id[i];
    L1[x] = bf[x], L2[x] = bf[bf[x]];
    R1[x] = nx[x], R2[x] = nx[nx[x]];
    bf[nx[x]] = bf[x], nx[bf[x]] = nx[x];
  }
}
}  // namespace Init

namespace Solve {
int ans;
void dfs(int x1, int x2, int dep) {
  if (dep < 0) return;
  int to = stk[dep] ^ 1;
  if (tot[ch[x2][to]] - tot[ch[x1][to]]) {
    ans += 1 << dep;
    dfs(ch[x1][to], ch[x2][to], dep - 1);
  } else {
    dfs(ch[x1][to ^ 1], ch[x2][to ^ 1], dep - 1);
  }
}
int Qry(int L, int R) {
  ans = 0;
  dfs(rt[L - 1], rt[R], 30);
  return ans;
}
void main() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0, x = a[i]; j <= 30; j++, x >>= 1) stk[j] = x & 1;
    if (L1[i]) ans = max(ans, Qry(L2[i] + 1, R1[i] - 1));
    if (R1[i] <= n) ans = max(ans, Qry(L1[i] + 1, R2[i] - 1));
  }
  cout << ans << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4098.in", "r", stdin);
  freopen("4098.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
