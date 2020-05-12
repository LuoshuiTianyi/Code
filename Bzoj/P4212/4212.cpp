#include <cstdio>
#include <cstring>
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

const int Max_n = 2e6 + 5, M = 26;
int n, m, ans, node[Max_n];
string s[2005];
char S[Max_n];

namespace Trie {
int rt[200000], ch[Max_n << 1][M], cnt;
int cntd, top, dfn[Max_n], sz[Max_n], bel[Max_n], nu[Max_n], f[Max_n << 1];
void add(int x, int &o, int dep, string &s) {
  o = ++cnt;
  if (dep < 0) {
    f[o] = 1;
    return;
  }
  for (int i = 0; i < M; i++) ch[o][i] = ch[x][i];
  add(ch[x][s[dep] - 'a'], ch[o][s[dep] - 'a'], dep - 1, s);
}
void build(int x) {
  dfn[x] = ++cntd, sz[x] = 1;
  if (bel[x]) {
    top++;
    add(rt[top - 1], rt[top], s[bel[x]].length() - 1, s[bel[x]]);
  }
  for (int i = 0; i < M; i++)
    if (ch[x][i]) build(ch[x][i]), sz[x] += ch[x][i];
}
}  // namespace Trie
using namespace Trie;

namespace Input {
void main() {
  ios::sync_with_stdio(false);
  n = read(), cnt = 1;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    int now = 1;
    for (int j = 0; j < s[i].length(); j++) {
      int to = s[i][j] - 'a';
      if (!ch[now][to]) ch[now][to] = ++cnt;
      now = ch[now][to];
    }
    bel[now] = i, nu[now]++;
  }
}
}  // namespace Input

namespace Init {
void main() { build(1); }
}  // namespace Init

namespace Solve {
void main() {
  while (m--) {
    scanf(
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4212.in", "r", stdin);
  freopen("4212.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
