#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, a[300001];
long long ans;
int main() {
  // freopen("C.in","r",stdin);
  // freopen("C.out","w",stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n / 2; i++)
    ans += 1ll * (a[i] + a[n - i + 1]) * (a[i] + a[n - i + 1]);
  cout << ans;
}
