#include <cstdio>
#include <iostream>
using namespace std;
int n, m, tot, ans[1000001];
long long sum, a[101], mod = 10007;
bool book[1000001];
void read(long long &x) {
  char ch = getchar();
  int t = 1;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      t = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 % mod + ch - '0';
    ch = getchar();
  }
  x *= t;
}
bool pd(int x) {
  sum = 0;
  for (int i = n; i >= 1; i--)
    sum = ((sum + a[i]) * x) % mod;
  sum = (sum + a[0]) % mod;
  return !sum;
}
int main() {
  freopen("2312.in", "r", stdin);
  freopen("2312.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0; i <= n; i++)
    read(a[i]);
  for (int i = 1; i <= m; i++) {
    if (book[i] == 1) {
      ans[++tot] = i;
      continue;
    }
    if (pd(i)) {
      for (int j = i + mod; j <= m; j += mod)
        book[j] = 1;
      ans[++tot] = i;
    }
  }
  printf("%d\n", tot);
  for (int i = 1; i <= tot; i++)
    printf("%d\n", ans[i]);
}
