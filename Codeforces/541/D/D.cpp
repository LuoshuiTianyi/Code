#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, m, d, cnt, deep[2001], r[2001], head[2001], fa[2001], to[1000001],
    nx[1000001];
bool flag, vis[2001], book[2001], road[2001][2001];
char s[1002];
void add(int u, int v) {
  d++;
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    for (int j = 1; j <= m; j++) {
      if (s[j] == '>')
        add(n + j, i), r[i]++, road[n + j][i] = true;
      if (s[j] == '<')
        add(i, n + j), r[n + j]++, road[i][n + j] = true;
      if (s[j] == '=')
        fa[find(n + j)] = find(i);
    }
  }
  for (int i = 1; i <= n + m; i++)
    for (int j = 1; j <= n + m; j++)
      if (find(i) == find(j) && road[i][j]) {
        cout << "No";
        return 0;
      }
  cnt = n + m;
  for (int i = 1; i <= n + m; i++) {
    if (!cnt)
      break;
    for (int j = 1; j <= n + m; j++)
      if (!r[j] && !vis[j])
        deep[j] = i, cnt--, book[j] = true;
    for (int j = 1; j <= n + m; j++)
      if (book[j] && !vis[j]) {
        vis[j] = true;
        for (int p = head[j]; p; p = nx[p])
          r[to[p]]--;
      }
  }
  if (cnt > 0) {
    cout << "No";
    return 0;
  }
  cout << "Yes\n";
  for (int i = 1; i <= n; i++)
    printf("%d ", deep[i]);
  cout << endl;
  for (int i = n + 1; i <= n + m; i++)
    printf("%d ", deep[i]);
}
