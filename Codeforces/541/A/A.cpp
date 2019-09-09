#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int a, b, c, d, ans;
int main() {
  // freopen("A.in","r",stdin);
  // freopen("A.out","w",stdout);
  cin >> a >> b >> c >> d;
  ans = a + c + (b + d + 2) * 2;
  ans += abs(a - c);
  cout << ans;
}
