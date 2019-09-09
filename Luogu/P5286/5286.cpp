#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n;
int x[1001], y[1001];
long long ans;
struct Group {
  long long t1, t2;
} dot[1001];
long long get_dis(int u, int v) {
  return 1ll * (x[u] - x[v]) * (x[u] - x[v]) +
         1ll * (y[u] - y[v]) * (y[u] - y[v]);
}
bool cmp(Group a, Group b) { return a.t1 == b.t1 ? a.t2 < b.t2 : a.t1 < b.t1; }
int get_angle(int a, int b, int c) {
  long long d1 = get_dis(a, b), d2 = get_dis(b, c), d3 = get_dis(a, c);
  if (d1 + d2 < d3)
    return 2;
  if (d1 + d2 > d3)
    return 1;
  return 0;
}
int main() {
  freopen("5286.in", "r", stdin);
  freopen("5286.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &x[i], &y[i]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (i != j) {
        int top = 0, bef = 0;
        long long sum1 = 0, sum2 = 0;
        for (int k = 1; k <= n; k++)
          if (k != i && k != j && get_angle(k, i, j) == 1 &&
              get_angle(k, j, i) == 1)
            top++, dot[top].t1 = get_dis(i, k), dot[top].t2 = get_dis(j, k);
        sort(dot + 1, dot + top + 1, cmp);
        dot[top + 1].t1 = -1;
        for (int k = 1; k <= top + 1; k++)
          if (dot[k].t1 != dot[k - 1].t1 || dot[k].t2 != dot[k - 1].t2)
            sum1 += 1ll * (k - bef - 1) * (k - bef) / 2, bef = k;
        top = 0, bef = 0;
        for (int k = 1; k <= n; k++)
          if (k != i && k != j && get_angle(k, j, i) == 2)
            dot[++top].t1 = get_dis(j, k);
        sort(dot + 1, dot + top + 1, cmp);
        dot[top + 1].t1 = -1;
        for (int k = 1; k <= top + 1; k++)
          if (dot[k].t1 != dot[k - 1].t1)
            sum2 += 1ll * (k - bef - 1) * (k - bef) / 2, bef = k;
        ans += 4ll * sum1 * sum2;
      }
  cout << ans;
}
