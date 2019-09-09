#include <cstdio>
#include <iostream>
#include <map>
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
const int Max_n = 2e5 + 5;
int n;
LL ans;
namespace SAM {
int cnt = 1, las = 1;
struct node {
  int fa, len;
  map<int, int> ch;
} k[Max_n << 1];
void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].len = k[p].len + 1;
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
  ans += k[np].len - k[k[np].fa].len;
}
}  // namespace SAM
int main() {
#ifndef ONLINE_JUDGE
  freopen("4070.in", "r", stdin);
  freopen("4070.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) {
    SAM::add(read());
    printf("%lld\n", ans);
  }
}
