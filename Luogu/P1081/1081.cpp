#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, l[100001], r[100001], zx[100001], min1[100001], min2[100001],
    high[100001], answer;
long long mit, f[100001][18], A[100001][18], B[100001][18], anwe1, anwe2;
double ans = 2e9;
struct node {
  int h, d;
} k[100002];
bool cmp(node x, node y) { return x.h < y.h; }
void work(int x, long long limit) {
  for (int i = 17; i >= 0; i--)
    if (f[x][i] && A[x][i] + B[x][i] <= limit) {
      limit -= A[x][i] + B[x][i];
      anwe1 += A[x][i];
      anwe2 += B[x][i];
      x = f[x][i];
    }
  if (A[x][0] <= limit)
    anwe1 += A[x][0];
}
int main() {
  freopen("1081.in", "r", stdin);
  freopen("1081.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> k[i].h;
    k[i].d = i;
    high[i] = k[i].h;
  }
  sort(k + 1, k + n + 1, cmp);
  k[0].h = -2e9 - 1;
  k[n + 1].h = 2e9 + 1;
  r[0] = 1;
  l[n + 1] = n;
  for (int i = 1; i <= n; i++) {
    l[i] = i - 1;
    r[i] = i + 1;
    zx[k[i].d] = i;
  }
  for (int i = 1; i < n - 1; i++) {
    int m1 = 0, m2 = 0;
    int start = l[l[zx[i]]];
    for (int j = 1; j <= 5; j++, start = r[start])
      if (start != zx[i])
        if (abs(k[start].h - k[zx[i]].h) < abs(k[m1].h - k[zx[i]].h))
          m1 = start;
    start = l[l[zx[i]]];
    for (int j = 1; j <= 5; j++, start = r[start])
      if (start != zx[i] && start != m1)
        if (abs(k[start].h - k[zx[i]].h) < abs(k[m2].h - k[zx[i]].h))
          m2 = start;
    min1[i] = k[m1].d;
    min2[i] = k[m2].d;
    l[r[zx[i]]] = l[zx[i]];
    r[l[zx[i]]] = r[zx[i]];
  }
  min1[n - 1] = n;
  for (int i = 1; i <= n; i++) {
    f[i][0] = min1[min2[i]];
    A[i][0] = abs(high[min2[i]] - high[i]);
    B[i][0] = abs(high[min2[i]] - high[min1[min2[i]]]);
    if (!min2[i])
      A[i][0] = 2e9;
    if (!min1[i])
      B[i][0] = 2e9;
  }
  for (int j = 1; j <= 17; j++)
    for (int i = 1; i <= n; i++) {
      f[i][j] = f[f[i][j - 1]][j - 1];
      A[i][j] = A[i][j - 1] + A[f[i][j - 1]][j - 1];
      B[i][j] = B[i][j - 1] + B[f[i][j - 1]][j - 1];
    }
  cin >> mit >> m;
  for (int i = 1; i <= n; i++) {
    anwe1 = 0;
    anwe2 = 0;
    work(i, mit);
    if (anwe2 == 0) {
      if (ans == 2e9)
        answer = i;
    } else if (ans > (anwe1 * 0.1 / anwe2 * 0.1)) {
      ans = (anwe1 * 0.1 / anwe2 * 0.1);
      answer = i;
    }
  }
  cout << answer << endl;
  for (int i = 1; i <= m; i++) {
    anwe1 = 0;
    anwe2 = 0;
    int x;
    cin >> x >> mit;
    work(x, mit);
    cout << anwe1 << " " << anwe2 << endl;
  }
}
