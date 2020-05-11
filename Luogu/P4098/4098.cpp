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
int bf[Max_n], nx[Max_n];
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
  int to = stk[dep];
  add(ch[now][to], ch[o][to], dep - 1);
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
void main() {
  for (int i = 1; i <= n; i++) {
    for (int j = 0, x = a[i]; j <= 30; j++, x >>= 1) stk[j] = x & 1;
    add(rt[i - 1], rt[i], 30);
  }
  for (int i = 1; i <= n; i++)
}
}  // namespace Init

namespace Solve {
void main() {
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
