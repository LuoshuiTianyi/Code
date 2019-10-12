#include <cstdio>
#include <iostream>
using namespace std;
int a, b, x, y;
int exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int d = exgcd(b, a % b, x, y);
  int tmp = x;
  x = y;
  y = tmp - (a / b) * y;
  return d;
}
int main() {
  freopen("1082.in", "r", stdin);
  freopen("1082.out", "w", stdout);
  cin >> a >> b;
  exgcd(a, b, x, y);
  cout << (x % b + b) % b;
}
