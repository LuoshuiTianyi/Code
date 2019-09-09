#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, a[13], cnt, head[500001], nx[6000001], to[6000001], w[6000001];
bool u[500001];
long long Bn, Bx, ans1, ans2, dis[500001];
void add(int u, int v, int W, int d) {
  to[d] = v, w[d] = W, nx[d] = head[u];
  head[u] = d;
}
queue<int> q;
void SPFA() {
  q.push(0);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    u[x] = 0;
    for (int i = head[x]; i; i = nx[i])
      if (dis[to[i]] > dis[x] + w[i]) {
        dis[to[i]] = dis[x] + w[i];
        if (!u[to[i]]) {
          u[to[i]] = 1;
          q.push(to[i]);
        }
      }
  }
}
int main() {
  freopen("2371.in", "r", stdin);
  freopen("2371.out", "w", stdout);
  cin >> n >> Bn >> Bx;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + n + 1);
  for (int i = 0; i < a[1]; i++) {
    dis[i] = 2e18;
    for (int j = 2; j <= n; j++)
      add(i, (i + a[j]) % a[1], a[j], ++cnt);
  }
  dis[0] = 0;
  SPFA();
  for (int i = 0; i < a[1]; i++) {
    if (dis[i] <= Bn)
      ans1 += (Bn - dis[i]) / (long long)a[1] + 1;
    if (dis[i] <= Bx)
      ans2 += (Bx - dis[i]) / (long long)a[1] + 1;
  }
  ans2 -= ans1;
  if (dis[Bn % a[1]] <= Bn)
    ans2++;
  cout << ans2;
}
