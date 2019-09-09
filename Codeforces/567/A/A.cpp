#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void read(long long &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
long long x, y, z;
int main() {
  //freopen("A.in", "r", stdin);
  //freopen("A.out", "w", stdout);
  read(x), read(y), read(z);
  if (!(x % z))
    cout << x / z + y / z << " 0";
  else if (!(y % z))
    cout << x / z + y / z << " 0";
  else if (x%z+y%z<z)
    cout << x / z + y / z << " 0";
  else
    cout << (x + y) / z << " " << min(z - x % z, z - y % z);
}
