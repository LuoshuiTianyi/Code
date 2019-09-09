#include <cstdio>
#include <iostream>
using namespace std;
int n, fa[150001], l[150001], r[150001], nx[150001];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
  // freopen("F.in","r",stdin);
  // freopen("F.out","w",stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    fa[i] = i, l[i] = i, r[i] = i;
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    u = find(u), v = find(v);
    nx[r[u]] = l[v];
    r[u] = r[v];
    fa[v] = u;
  }
  for (int now = l[find(1)]; now; now = nx[now])
    cout << now << " ";
}
