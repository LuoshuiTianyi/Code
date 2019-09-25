#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define db double
using namespace std;
const int M = 3e4 + 1;
int n;
int q[M], fi, la, ans = 2e9 + 1;
int sum, s[M], d[M], w[M];
db calc(int j, int k) {
  return 1.0 * (d[j] * s[j] - d[k] * s[k]) / (s[j] - s[k]);
}
int count(int i, int j) { return sum - d[j] * s[j] - d[i] * (s[i] - s[j]); }
int main() {
  freopen("4360.in", "r", stdin);
  freopen("test.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &w[i], &d[i]);
  }
  for (int i = n; i >= 1; i--)
    d[i] += d[i + 1];
  for (int i = 1; i <= n; i++)
    s[i] = s[i - 1] + w[i], sum += d[i] * w[i];
  for (int i = 1; i <= n; i++) {
    while (fi < la && calc(q[fi], q[fi + 1]) > d[i]) {
      cout << calc(q[fi], q[fi + 1]) << " " << i << " " << d[i] << endl;
      ++fi;
    }
    ans = min(ans, count(i, q[fi]));
    while (fi < la && calc(q[la - 1], q[la]) < calc(q[la], i))
      --la;
    q[++la] = i;
  }
  // printf("%d\n",ans);
  return 0;
}
