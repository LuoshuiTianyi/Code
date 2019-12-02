#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;
const int mod = 1e9 + 7;
typedef long long LL;
inline int add(int a, int b) {
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub(int a, int b) {
  a -= b;
  return a < 000 ? a + mod : a;
}
inline int Pow(int x, int k, int re = 1) {
  for (; k; k >>= 1, x = 1LL * x * x % mod)
    if (k & 1) re = 1LL * re * x % mod;
  return re;
}
inline int Inv(int x) { return Pow(x, mod - 2); }
const int inv2 = Inv(2);
const int inv4 = Inv(4);
const int inv6 = Inv(6);
inline int C2(int x) { return 1LL * x * (x - 1) / 2 % mod; }
inline int C3(int x) {
  return 1LL * x * (x - 1) % mod * (x - 2) % mod * inv6 % mod;
}
const int N = 1e3 + 7;
struct Pair {
  int x, y;
  bool operator<(const Pair& t) const { return x < t.x; }
} p[N];
int cnt;
Pair p2[N * N];
int n, K, m;
namespace Solve2 {
int ans;
int main() {
  for (int i = 1; i <= n << 1; i++)
    for (int j = 1; j <= n << 1; j++)
      if (p[i].x + p[j].x <= m)
        ans = (ans + 1LL * p[i].y * p[j].y % mod * (m - p[i].x - p[j].x + 1)) %
              mod;
  if (~m & 1)
    for (int i = 1; i <= n << 1; i++)
      if (p[i].x << 1 <= m) ans = add(ans, mod - p[i].y);
  cout << 1LL * ans * inv2 % mod;
  return 0;
}
}  // namespace Solve2
namespace Solve3 {
int ans1;
int ans2;
int ans3;
void Calc() {
  int s1 = 0, s2 = 0, s3 = 0;
  for (int i = n << 1, j = 1; i; i--)
    if (p[i].x <= m) {
      while (p[i].x + p2[j].x <= m && j <= cnt) {
        s1 = add(s1, p2[j].y);
        s2 = (s2 + 1LL * (mod - p2[j].y) * p2[j].x) % mod;
        s3 = (s3 + 1LL * p2[j].y * C2(p2[j].x + 1)) % mod;
        j++;
      }
      int len = m - p[i].x + 2;
      ans1 =
          (ans1 + (1LL * s1 * C2(len) + 1LL * len * s2 + s3) % mod * p[i].y) %
          mod;
    }
}
int main() {
  Calc();
  for (int i = 1; i <= n << 1; i++)
    for (int j = 1; j <= n << 1; j++)
      if (2 * p[i].x + p[j].x <= m)
        ans2 = (ans2 + 1LL * ((m - 2 * p[i].x - p[j].x) / 2 + 1) * p[j].y %
                           mod * p[i].y) %
               mod;
  if (m % 3 == 0)
    for (int i = 1; i <= n << 1; i++)
      if (3 * p[i].x <= m) ans3 = add(ans3, p[i].y);
  cout << 1LL * inv6 * (ans1 - 3LL * ans2 % mod + 2LL * ans3) % mod;
  return 0;
}
};  // namespace Solve3
namespace Solve4 {
int ans1, ans2, ans3, ans4, ans5;
void Calc1111() {
  int s0 = 0, s1 = 0, s2 = 0, s3 = 0;
  for (int i = cnt, j = 1; i; i--) {
    while (j <= cnt && p2[i].x + p2[j].x <= m) {
      int t = p2[j].y;
      s0 = add(s0, t);
      t = 1LL * t * p2[j].x % mod;
      s1 = sub(s1, t);
      t = 1LL * t * p2[j].x % mod;
      s2 = add(s2, t);
      t = 1LL * t * p2[j].x % mod;
      s3 = sub(s3, t);
      j++;
    }
    int len = m - p2[i].x;
    int tmp = 1LL * (len + 3) * (len + 2) % mod * (len + 1) % mod * s0 % mod;
    tmp = (tmp + 1LL * (3ll * len * len + 12LL * len + 11) % mod * s1) % mod;
    tmp = (tmp + 1LL * (3LL * len + 6) * s2) % mod;
    ans1 = (ans1 + 1LL * p2[i].y * inv6 % mod * (tmp + s3)) % mod;
  }
}
void Calc211() {
  int s0 = 0, s1 = 0, s2 = 0;
  for (int i = cnt, j = 1; i; i--) {
    while (j <= n << 1 && p2[i].x + 2 * p[j].x <= m) {
      int t = p[j].y;
      s0 = add(s0, t);
      t = 1LL * t * p[j].x % mod;
      s1 = sub(s1, t);
      t = 1LL * t * p[j].x % mod;
      s2 = add(s2, t);
      j++;
    }
    int len = m - p2[i].x + 2;
    ans2 = (ans2 + ((1LL * len * len % mod - (len % 2)) % mod * s0 +
                    4LL * len * s1 + 4LL * s2) %
                       mod * p2[i].y) %
           mod;
  }
  ans2 = 1LL * ans2 * inv4 % mod;
}
int main() {
  if (m % 4 == 0) {
    for (int i = 1; i <= n << 1; i++)
      if (4 * p[i].x <= m) ans5 = add(ans5, p[i].y);
  }
  if (~m & 1) {
    for (int i = 1; i <= n << 1; i++)
      for (int j = 1; j <= n << 1; j++)
        if (p[i].x + p[j].x <= m / 2)
          ans4 = (ans4 +
                  1LL * p[i].y * p[j].y % mod * (m / 2 - p[i].x - p[j].x + 1)) %
                 mod;
  }
  for (int i = 1; i <= n << 1; i++)
    for (int j = 1; j <= n << 1; j++)
      if (3 * p[i].x + p[j].x <= m)
        ans3 = (ans3 + 1LL * p[i].y * p[j].y % mod *
                           ((m - p[j].x - 3 * p[i].x) / 3 + 1)) %
               mod;
  Calc211();
  Calc1111();
  cout << (1LL * Inv(24) *
               (ans1 - 6LL * ans2 + 8LL * ans3 + 3LL * ans4 - 6LL * ans5) %
               mod +
           mod) %
              mod;
  return 0;
}
}  // namespace Solve4
int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.ans", "w", stdout);
#endif
  cin >> n >> K >> m;
  for (int i = 1; i <= n; i++)
    cin >> p[i].x >> p[i + n].x, p[i].y = 1, p[i + n].y = mod - 1, p[i + n].x++;
  for (int i = 1; i <= n << 1; i++)
    for (int j = 1; j <= n << 1; j++)
      p2[++cnt] = (Pair){p[i].x + p[j].x, 1LL * p[i].y * p[j].y % mod};
  sort(p + 1, p + 1 + n * 2);
  sort(p2 + 1, p2 + 1 + cnt);
  if (K == 2) return Solve2::main();
  if (K == 3) return Solve3::main();
  if (K == 4) return Solve4::main();
  return 0;
}
