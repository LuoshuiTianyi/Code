#include <bits/stdc++.h>
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
const int Max_n = 2e6 + 5, M = 26;
namespace SAM {
int cnt = 1, las = 1;
int nu[Max_n];
struct node {
  int len, fa, ch[M];
} k[Max_n];
void add(int c) {
  int p = las, np = las = ++cnt;
  nu[np] = 1, k[np].len = k[p].len + 1;
  for (; p && !k[p].ch[c]; p = k[p].fa) k[p].ch[c] = np;
  if (!p)
    k[np].fa = 1;
  else {
    int q = k[p].ch[c];
    if (k[q].len == k[p].len + 1)
      k[np].fa = q;
    else {
      int nq = ++cnt;
      k[nq] = k[q], k[nq].len = k[p].len + 1;
      k[q].fa = k[np].fa = nq;
      for (; p && k[p].ch[c] == q; p = k[p].fa) k[p].ch[c] = nq;
    }
  }
}
}  // namespace SAM
int n;
LL ans;
char S[Max_n];
int cntr, hd[Max_n], nx[Max_n], to[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
void Count(int x) {
  go(x, i, v) Count(v), SAM::nu[x] += SAM::nu[v];
  if (SAM::nu[x] > 1) ans = max(ans, 1ll * SAM::nu[x] * SAM::k[x].len);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3804.in", "r", stdin);
  freopen("3804.out", "w", stdout);
#endif
  scanf("%s", S + 1);
  n = strlen(S + 1);
  for (int i = 1; i <= n; i++) SAM::add(S[i] - 'a');
  for (int i = 2; i <= SAM::cnt; i++) addr(SAM::k[i].fa, i);
  Count(1);
  cout << ans;
}
