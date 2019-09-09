#include <cstdio>
#include <iostream>
using namespace std;
int n;
long long now = 1;
int main() {
  freopen("1134.in", "r", stdin);
  freopen("1134.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    now *= 1ll * i;
    while (now % 10 == 0)
      now /= 10;
    now %= 50000000;
  }
  cout << now % 10;
}
