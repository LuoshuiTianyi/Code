#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5, M = 26;
int n;
LL f[Max_n];
char S[Max_n];
namespace SAM {
int cnt = 1, las = 1;
struct node {
  int len, fa, ch[M];
} k[Max_n];
void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].len = k[p].len + 1;
  for (; p && !k[p].ch[c]; p = k[p].fa) k[p].ch[c] = np;
  if (!p) k[np].fa = 1;
  else {
    int q = k[p].ch[c];
    if (k[q].len == k[p].len + 1) k[np].fa = q;
    else {
      int nq = ++cnt;
      k[nq] = k[q], k[nq].len = k[p].len + 1;
      k[np].fa = k[q].fa = nq;
      for (; p && k[p].ch[c] == q; p = k[p].fa) k[p].ch[c] = nq;
    }
  }
}
}
int cntr, hd[Max_n], nx[Max_n], to[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
void DP(int x) {
  go(x, i, v) DP(v), f[x] += f[v];
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("2408.in", "r", stdin);
  freopen("2408.out", "w", stdout);
#endif
  n = read();
  scanf("%s", S + 1);
  for (int i = 1; i <= n; i++) SAM::add(S[i] - 'a');
  for (int i = 2; i <= SAM::cnt; i++) {
    addr(SAM::k[i].fa, i);
    f[i] = SAM::k[i].len - SAM::k[SAM::k[i].fa].len;
  }
  DP(1);
  cout << f[1];
}
