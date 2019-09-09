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
int n, K;
long long ans;
int cnta, a[Max_n];
vector<int> buk[Max_n], c[Max_n];
struct robot {
  int x, r, q, pos;
} k[Max_n];
bool cmp(robot a, robot b) { return a.q == b.q ? a.x < b.x : a.q < b.q; }
bool cmp2(robot a, robot b) { return a.r > b.r; }
void add(int x, int k) {
  for (int i = k, lim = c[x].size(); i < lim; i += i & -i) c[x][i]++;
}
int query(int x, int k) {
  int ans = 0;
  for (int i = k; i; i -= i & -i) ans += c[x][i];
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("G.in", "r", stdin);
  freopen("G.out", "w", stdout);
#endif
  n = read(), K = read();
  for (int i = 1; i <= n; i++)
    k[i].x = read(), k[i].r = read(), k[i].q = read();
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++) c[i].push_back(0);
  k[0].q = -1;
  for (int i = 1; i <= n + 1; i++) {
    if (k[i].q != k[i - 1].q) a[cnta++] = k[i - 1].q;
    buk[cnta].push_back(k[i].x);
    c[cnta].push_back(0);
    k[i].pos = buk[cnta].size() - 1;
  }
  cnta--;
  sort(k + 1, k + n + 1, cmp2);
  for (int i = 1; i <= n; i++) {
    int l = upper_bound(a + 1, a + cnta + 1, k[i].q - K - 1) - a;
    int r = upper_bound(a + 1, a + cnta + 1, k[i].q + K) - a - 1;
    if (a[l] > k[i].q + K || a[r] < k[i].q - K) continue;
    int L = k[i].x - k[i].r, R = k[i].x + k[i].r;
    for (int j = l; j <= r; j++) {
      int rr =
          upper_bound(buk[j].begin(), buk[j].end(), R) - buk[j].begin() - 1;
      int ll =
          upper_bound(buk[j].begin(), buk[j].end(), L - 1) - buk[j].begin();
      if (buk[j][ll] > R || buk[j][rr] < L) continue;
      ans += query(j, rr + 1) - query(j, ll);
    }
    add(lower_bound(a + 1, a + cnta + 1, k[i].q) - a, k[i].pos + 1);
  }
  printf("%lld\n", ans);
}
