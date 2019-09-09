#include <cstdio>
#include <iostream>
using namespace std;
const int size = 400;
int n, m, x, y, ans, a[150001], Ans[401][401];
char opt;
void Upd(int pos, int bef, int now) {
  a[pos] = now;
  for (int i = 1; i <= min(size, n); i++)
    Ans[i][pos % i] += now - bef;
}
int main() {
  freopen("3396.in", "r", stdin);
  freopen("3396.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x);
    Upd(i, 0, x);
  }
  while (m--) {
    scanf("%s%d%d", &opt, &y, &x);
    if (opt == 'C')
      Upd(y, a[y], x);
    else if (y <= size)
      printf("%d\n", Ans[y][x]);
    else {
      ans = 0;
      for (int i = x; i <= n; i += y)
        ans += a[i];
      printf("%d\n", ans);
    }
  }
}
