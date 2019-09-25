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
const int Max_n = 1e5 + 5;
int n, b[Max_n], tot;
bool C[Max_n];
int main() {
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
  n = read();
  double x;
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &x);
    b[i] = min(ceil(x), floor(x));
    tot += b[i];
    if (ceil(x) != floor(x)) C[i] = 1;
  }
  for (int i = 1, cnt = tot; i <= n, cnt < 0; i++)
    if (C[i]) b[i]++, cnt ++;
  for (int i = 1; i <= n; i++)
    printf("%d\n", b[i]);
}
