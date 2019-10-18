#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, len, head, tail, a[50001], L[50001], que[50001];
long long f[50001], sum[50001];
long long work(int a, int b) {
  return f[a] + (0ll + sum[b] - sum[a] + b - a - 1 - len) *
                    (0ll + sum[b] - sum[a] + b - a - 1 - len);
}
int find(int x, int y) {
  int l = y, r = n + 1;
  while (l < r) {
    int mid = (l + r) / 2;
    work(x, mid) <= work(y, mid) ? r = mid : l = mid + 1;
  }
  return l;
}
int main() {
  freopen("3195.in", "r", stdin);
  freopen("3195.out", "w", stdout);
  cin >> n >> len;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
  for (int i = 1; i <= n; i++) {
    while (head < tail && L[head] <= i)
      head++;
    f[i] = work(que[head], i);
    while (head < tail && find(i, que[tail]) <= L[tail - 1])
      tail--;
    L[tail] = find(i, que[tail]);
    que[++tail] = i;
  }
  cout << f[n];
}
