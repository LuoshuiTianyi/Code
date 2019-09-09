#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, a[35001];
int num[35001], rk[35001], c[35001], f[35001];
bool cmp(int x, int y) { return a[x] < a[y]; }
int main() {
  freopen("2501.in", "r", stdin);
  freopen("2501.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), a[i] -= i, num[i] = a[i];
  sort(num + 1, num + n + 1, cmp);
  for (int i = 1; i <= n; i++)
    rk[num[i]] = i;
}
