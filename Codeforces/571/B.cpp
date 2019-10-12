#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
int n, m, a, b, ans1, ans2;
bool bj;
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  n = read(), m = read();
  a = m / 2 + (m % 2 >= 1);
  b = m / 3 + (m % 3 >= 2);
  ans1 = (n / 3 + (n % 3 == 2)) * a + (n % 3 == 1) * b;
  if (n % 3 == 0) {
    ans1 -= a;
    ans1 += max(a, b * 2);
  }
  ans2 = (n / 2 + (n % 2 == 1)) * b;
  if (n % 2 == 1 && n > 1) {
    ans2 -= 2 * b;
    ans2 += max(a, b * 2);
  }
  cout << max(ans1, ans2);
}
