#include <cstdio>
#include <iostream>
using namespace std;
int n, a, b, A, B, ans = 1;
int main() {
  // freopen("B.in","r",stdin);
  // freopen("B.out","w",stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &A, &B);
    if (a < b && A >= b)
      ans++, a = b;
    else if (b < a && B >= a)
      ans++, b = a;
    if (a == b)
      ans += min(A, B) - a;
    a = A, b = B;
  }
  cout << ans;
}
