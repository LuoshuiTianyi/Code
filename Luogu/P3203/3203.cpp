#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[200001], opt, pos, x;
int sum, size, L[100001], belong[200001], num[200001], nx[200001];
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
void init(int l, int r) {
  for (int i = r; i >= l; i--)
    if (i + a[i] > r) {
      nx[i] = i + a[i];
      num[i] = 1;
    } else {
      nx[i] = nx[i + a[i]];
      num[i] = num[i + a[i]] + 1;
    }
}
int main() {
  freopen("3203.in", "r", stdin);
  freopen("3203.out", "w", stdout);
  read(n);
  size = sqrt(n);
  for (int i = 1; i <= n; i++) {
    read(a[i]);
    belong[i] = (i + size - 1) / size;
  }
  for (int i = 1; i <= n + size - 1; i += size)
    L[(i + size - 1) / size] = i;
  for (int i = 1; i <= n; i += size)
    init(i, min(i + size - 1, n));
  read(m);
  while (m--) {
    read(opt), read(pos);
    pos++;
    if (opt == 1) {
      int ans = 0;
      while (pos <= n)
        ans += num[pos], pos = nx[pos];
      printf("%d\n", ans);
    } else {
      read(x);
      a[pos] = x;
      init(L[belong[pos]], min(L[belong[pos] + 1] - 1, n));
    }
  }
}
