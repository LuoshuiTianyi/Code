#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, last = 1, tot = 1, tr[N][26], fa[N], len[N], t[N], a[N], sum[N], ans[N],
       Ans;
char s[N];
void extend(int c) {
  int v = last, u = ++tot;
  last = u;
  len[u] = len[v] + 1;
  while (v && !tr[v][c]) tr[v][c] = u, v = fa[v];
  if (!v)
    fa[u] = 1;
  else {
    int x = tr[v][c];
    if (len[x] == len[v] + 1)
      fa[u] = x;
    else {
      int y = ++tot;
      memcpy(tr[y], tr[x], sizeof(tr[y]));
      fa[y] = fa[x];
      fa[x] = fa[u] = y;
      len[y] = len[v] + 1;
      while (v && tr[v][c] == x) tr[v][c] = y, v = fa[v];
    }
  }
}
int main() {
  freopen("1812.in", "r", stdin);
  freopen("1812.ans", "w", stdout);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) extend(s[i] - 'a');
  for (int i = 1; i <= tot; ++i) ++t[len[i]];
  for (int i = 1; i <= tot; ++i) t[i] += t[i - 1];
  for (int i = 1; i <= tot; ++i) a[t[len[i]]--] = i;
  for (int i = 1; i <= tot; ++i) ans[i] = len[i];
  while (scanf("%s", s + 1) != EOF) {
    n = strlen(s + 1);
    memset(sum, 0, sizeof(sum));
    for (int i = 1, now = 1, cnt = 0; i <= n; ++i) {
      int c = s[i] - 'a';
      if (tr[now][c])
        ++cnt, now = tr[now][c];
      else {
        while (now && !tr[now][c]) now = fa[now];
        if (!now)
          cnt = 0, now = 1;
        else
          cnt = len[now] + 1, now = tr[now][c];
      }
      sum[now] = max(sum[now], cnt);
      //cout << now << " " << sum[now] << endl;
    }
    //cout << endl;
    for (int i = tot; i; --i) {
      //cout << a[i] << " " << sum[a[i]] << endl;
      sum[fa[a[i]]] = max(sum[fa[a[i]]], sum[a[i]]);
    }
    for (int i = 1; i <= tot; ++i) ans[i] = min(ans[i], sum[i]);
  }
  for (int i = 1; i <= tot; ++i) Ans = max(Ans, ans[i]);
  printf("%d", Ans);
  return 0;
}
