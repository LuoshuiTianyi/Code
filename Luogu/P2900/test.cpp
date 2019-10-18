#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
deque<int> s;
typedef long long ll;
inline void read(ll &x) {
  x = 0;
  int sign = 1;
  char c;
  do {
    c = getchar();
    if (c == '-')
      sign = -1;
  } while (c < '0' || c > '9');
  do {
    x = x * 10 + c - '0';
    c = getchar();
  } while (c <= '9' && c >= '0');
  x *= sign;
}
const int N = 5e4 + 5;
int tot;
ll n, f[N];
struct data {
  ll x, y;
} a[N], b[N];
inline bool cmp(data a, data b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline double slop(int a, int c) {
  return double(f[c] - f[a]) / (b[a + 1].y - b[c + 1].y);
}
int main() {
  freopen("2900.in", "r", stdin);
  freopen("test.out", "w", stdout);
  read(n);
  for (int i = 1; i <= n; i++)
    read(a[i].x), read(a[i].y);
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    while (tot && a[i].y >= b[tot].y)
      tot--;
    b[++tot].x = a[i].x;
    b[tot].y = a[i].y;
  }
  s.push_back(0);
  for (int i = 1; i <= tot; i++) {
    while (s.size() > 1 && slop(s[0], s[1]) < b[i].x)
      s.pop_front();
    int t = s[0], j;
    f[i] = f[t] + b[t + 1].y * b[i].x;
    while ((j = s.size()) > 1 && slop(s[j - 1], i) < slop(s[j - 2], s[j - 1]))
      s.pop_back();
    s.push_back(i);
  }
  printf("%lld", f[tot]);
  return 0;
}
