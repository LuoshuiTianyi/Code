#include <cstdio>
#include <iostream>
using namespace std;
int N, a, b, c, d, cnt;
void Exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  Exgcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - (a / b) * y;
}
int main() {
  freopen("1006.in", "r", stdin);
  freopen("1006.out", "w", stdout);
  N = 23 * 28 * 33;
  while (1) {
    cin >> a >> b >> c >> d;
    if (a == b && b == c && c == d && d == -1)
      break;
    int ans = (5544 * a + 14421 * b + 1288 * c - d + N) % N;
    if (ans == 0)
      ans = N;
    cout << "Case " << ++cnt << ": the next triple peak occurs in " << ans
         << " days.\n";
  }
}
