#include <cstdio>
#include <iostream>
using namespace std;
int n, m, nx[200001], head[10001], to[200001], book[200001], cnt, ans, bk;
bool flag = false;
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void dfs(int x) {
  if (book[x] & 1)
    bk++;
  cnt++;
  for (int i = head[x]; i; i = nx[i])
    if (book[to[i]] == -1) {
      book[to[i]] = book[x] ^ 1;
      dfs(to[i]);
    }
}
int main() {
  freopen("1330.in", "r", stdin);
  freopen("1330.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= n; i++)
    book[i] = -1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    add(u, v, i);
    add(v, u, i + m);
  }
  for (int i = 1; i <= n; i++)
    if (book[i] == -1) {
      cnt = 0;
      bk = 0;
      book[i] = 0;
      dfs(i);
      ans += min(cnt - bk, bk);
    }
  for (int i = 1; i <= n; i++)
    for (int j = head[i]; j; j = nx[j])
      if (book[to[j]] == book[i])
        flag = true;
  if (flag)
    cout << "Impossible";
  else
    cout << ans;
}
