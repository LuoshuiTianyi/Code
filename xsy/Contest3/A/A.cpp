#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 3e5 + 5, mod = 998244353;
int n, m, ans = 1;
set<int> s[Max_n];
void merge(int x, int y) {
  if (s[y].size() < s[x].size()) swap(s[x], s[y]);
  for (register set<int>::iterator i = s[x].begin(); i != s[x].end(); i++) s[y].insert(*i);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  n = read(), m = read();
  int u, v, to;
  for (register int i = 1; i <= m; i++) {
    u = read(), v = read();
    s[min(u, v)].insert(max(u, v));
  }
  for (register int i = 1; i <= n; i++) {
    ans = 1ll * ans * (n - s[i].size()) % mod;
    to = *s[i].begin();
    s[i].erase(to), merge(i, to);
  }
  cout << ans;
}
