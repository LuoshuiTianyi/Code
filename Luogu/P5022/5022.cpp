#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, top, a[5001], book[5001], U[5001], V[5001], ans[5001],
    road[5001][5001], Tp[5001], Ren;
bool flag;
void dfs(int x) {
  book[x] = 1;
  a[++top] = x;
  for (int i = 1; i <= Tp[x]; i++)
    if (!book[road[x][i]]) {
      if ((x == U[Ren] && road[x][i] == V[Ren]) ||
          (x == V[Ren] && road[x][i] == U[Ren]))
        continue;
      dfs(road[x][i]);
    }
}
void work() {
  int ff = false;
  for (int i = 1; i <= n; i++)
    if (a[i] > ans[i] && !ff)
      break;
    else if (a[i] < ans[i])
      ff = true;
  if (ff)
    for (int i = 1; i <= n; i++)
      ans[i] = a[i];
}
int main() {
  freopen("5022.in", "r", stdin);
  freopen("5022.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &U[i], &V[i]);
    road[U[i]][++Tp[U[i]]] = V[i];
    road[V[i]][++Tp[V[i]]] = U[i];
  }
  for (int i = 1; i <= n; i++)
    ans[i] = n;
  for (int i = 1; i <= n; i++)
    sort(road[i] + 1, road[i] + Tp[i] + 1);
  if (m == n - 1) {
    dfs(1);
    for (int i = 1; i <= n; i++)
      cout << a[i] << " ";
    return 0;
  } else {
    for (int i = 1; i <= n; i++) {
      top = 0;
      memset(book, 0, sizeof(book));
      Ren = i;
      dfs(1);
      if (top == n)
        work();
    }
    for (int i = 1; i <= n; i++)
      cout << ans[i] << " ";
  }
}
