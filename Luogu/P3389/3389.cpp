#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 105;
int n;
double a[Max_n][Max_n];
int main() {
#ifndef ONLINE_JUDGE
  freopen("3389.in", "r", stdin);
  freopen("3389.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n + 1; j++) a[i][j] = read();
  for (int i = 1; i <= n; i++) {
    int mp = i;
    for (int j = i + 1; j <= n; j++) abs(a[mp][i]) < abs(a[j][i]) ? mp = j : mp;
    for (int j = i; j <= n + 1; j++) swap(a[i][j], a[mp][j]);
    if (!a[i][i]) {
      cout << "No Solution";
      return 0;
    }
    for (int j = 1; j <= n; j++)
      if (i != j) {
        double x = a[j][i] / a[i][i];
        for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * x;
      }
  }
  for (int i = 1; i <= n; i++)
    printf("%.2lf\n", a[i][n + 1] / a[i][i]);
}
