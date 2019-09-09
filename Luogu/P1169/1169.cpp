#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[2002][2002], D[2002][2002], ans1, ans2, train[2002], top;
int main() {
  freopen("1169.in", "r", stdin);
  freopen("1169.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  for (int j = 1; j <= m; j++)
    for (int i = n; i >= 1; i--) {
      D[i][j] = 1;
      if (a[i][j] != a[i + 1][j])
        D[i][j] += D[i + 1][j];
    }
  for (int i = 1; i <= n; i++) {
    int now = 1;
    while (now <= m) {
      train[0] = now - 1;
      train[++top] = now++;
      while (now <= m && (a[i][now] != a[i][now - 1])) {
        while (top && D[i][now] < D[i][train[top]]) {
          int a = now - train[top - 1] - 1, b = D[i][train[top]];
          ans1 = max(ans1, min(a, b) * min(a, b));
          ans2 = max(ans2, a * b);
          top--;
        }
        train[++top] = now++;
      }
      while (top) {
        int a = now - train[top - 1] - 1, b = D[i][train[top]];
        ans1 = max(ans1, min(a, b) * min(a, b));
        ans2 = max(ans2, a * b);
        top--;
      }
    }
  }
  cout << ans1 << endl << ans2;
}
