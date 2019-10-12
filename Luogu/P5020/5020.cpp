#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int T, n, a[101], ans, f[25001], maxa;
int main() {
  freopen("5020.in", "r", stdin);
  freopen("5020.out", "w", stdout);
  cin >> T;
  while (T--) {
    memset(f, 0, sizeof(f));
    f[0] = 1;
    maxa = 0;
    cin >> n;
    ans = n;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      maxa = max(maxa, a[i]);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      if (f[a[i]]) {
        ans--;
        continue;
      }
      for (int j = a[i]; j <= maxa; j++)
        f[j] = max(f[j], f[j - a[i]]);
    }
    cout << ans << endl;
  }
}
