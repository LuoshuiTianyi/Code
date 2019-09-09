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
#define LL long long
const int Max_l = 20;
int dig, num[Max_l];
LL a, b, lim;
LL f[Max_l][Max_l][2][2];
long long DP(int len, int sum, bool lim, bool zero) {
  LL &res = f[len][sum][lim][zero];
  if (res != -1) return res;
  res = 0;
  if (!len) return res = sum;
  for (int i = 0; i <= 9; i++) {
    if (lim && i > num[len]) break;
    res += DP(len - 1, sum + ((!zero || i) && i == dig), lim && (i == num[len]),
              zero && !i);
  }
  return res;
}
LL Solve(LL lim) {
  int w = 0;
  while (lim) {
    num[++w] = lim % 10;
    lim /= 10;
  }
  memset(f, -1, sizeof(f));
  return DP(w, 0, 1, 1);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("2602.in", "r", stdin);
  freopen("2602.out", "w", stdout);
#endif
  a = read(), b = read();
  for (int i = 0; i <= 9; i++) dig = i, printf("%lld ", Solve(b) - Solve(a - 1));
  dig = 1;
}
