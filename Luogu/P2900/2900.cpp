#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, maxh, C, head, tail, que[50001];
long long f[50001];
struct node {
  int w, h;
} k[50001];
bool cmp(node a, node b) { return a.w != b.w ? a.w > b.w : a.h > b.h; }
double work(int a, int b) {
  return 1.0 * (f[b] - f[a]) / (k[b + 1].w - k[a + 1].w);
}
int main() {
  freopen("2900.in", "r", stdin);
  freopen("2900.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &k[i].w, &k[i].h);
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    if (maxh >= k[i].h)
      k[i].w = -1e9, C++;
    maxh = max(maxh, k[i].h);
  }
  sort(k + 1, k + n + 1, cmp);
  n -= C;
  for (int i = 1; i <= n; i++) {
    while (head < tail && work(que[head], que[head + 1]) > -k[i].h)
      head++;
    int x = que[head];
    f[i] = f[x] + 1ll * k[i].h * k[x + 1].w;
    while (head < tail && work(que[tail - 1], que[tail]) < work(que[tail], i))
      tail--;
    que[++tail] = i;
  }
  cout << f[n];
}
