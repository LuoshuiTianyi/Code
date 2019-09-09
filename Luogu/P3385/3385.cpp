#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int T, n, m, head[2001], to[6001], nx[6001], w[6001], cnt[2001], u[2001],
    dis[2001];
void add(int u, int v, int W, int d) {
  to[d] = v, nx[d] = head[u], w[d] = W;
  head[u] = d;
}
bool flag;
queue<int> q;
void spfa() {
  q.push(1);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    u[x] = 0;
    for (int i = head[x]; i; i = nx[i]) {
      if (!flag)
        break;
      int p = to[i];
      if (dis[p] > dis[x] + w[i]) {
        dis[p] = dis[x] + w[i];
        // cout<<x<<" "<<dis[x]<<" "<<p<<" "<<dis[p]<<endl;
        if (!u[p]) {
          if (cnt[p] > n)
            flag = false;
          u[p] = 1;
          q.push(p);
          cnt[p]++;
        }
      }
    }
  }
}
int main() {
  freopen("3385.in", "r", stdin);
  freopen("3385.out", "w", stdout);
  cin >> T;
  while (T--) {
    memset(head, 0, sizeof(head));
    memset(cnt, 0, sizeof(cnt));
    memset(dis, 0x7f, sizeof(dis));
    flag = true;
    cin >> n >> m;
    int u, v, W;
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", &u, &v, &W);
      add(u, v, W, i);
      if (W >= 0)
        add(v, u, W, i + m);
    }
    dis[1] = 0;
    spfa();
    if (flag)
      cout << "N0\n";
    else
      cout << "YE5\n";
  }
}
