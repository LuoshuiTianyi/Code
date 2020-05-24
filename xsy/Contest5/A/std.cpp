#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#define MAXN 50
#define MAXS 1100000
#define LL long long
using namespace std;

const LL P = 1000000007;

LL getPow(LL x, LL y) {
  LL res = 1;
  while (y) {
    if (y & 1) res = res * x % P;
    x = x * x % P;
    y >>= 1;
  }
  return res;
}

const LL inv9 = getPow(9, P - 2);

int n0, n, n1, m;
int a[MAXN][2], b[MAXN];
int pf[MAXN];
int id[MAXN];
vector<int> a1[MAXN];
LL e[MAXN][3], v[MAXS];
LL f[10][MAXS];

int getf(int x) {
  if (pf[x] == x) return x;
  return pf[x] = getf(pf[x]);
}

LL calc(int x) {
  LL res = 1;
  for (int i = 1; i <= n; i++)
    if ((x & (1 << (e[i][0] - 1))) && (x & (1 << (e[i][1] - 1))))
      (res *= e[i][2]) %= P;
  return res;
}

LL calcv(LL x) { return (getPow(10, x) - 1) * inv9 % P; }

LL solve() {
  static map<int, int> S;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a[i][0], &a[i][1]);
    S[a[i][0] - 1] = S[a[i][1]] = 0;
  }
  n = -1;
  for (auto &i : S) b[i.second = ++n] = i.first;
  for (int i = n; i; i--) b[i] -= b[i - 1];
  for (int i = 1; i <= m; i++) {
    a[i][0] = S[a[i][0] - 1] + 1;
    a[i][1] = S[a[i][1]];
    a1[a[i][1]].push_back(a[i][0]);
  }
  m = 0;
  for (int i = 0; i <= n; i++) pf[i] = i;
  for (int i = n; i; i--) {
    sort(a1[i].begin(), a1[i].end(), greater<int>());
    while (a1[i].size() > 1) {
      int t = a1[i].size() - 1;
      if (a1[i][t] < a1[i][0]) a1[a1[i][0] - 1].push_back(a1[i][t]);
      a1[i].pop_back();
    }
    if (!a1[i].empty()) {
      if (getf(a1[i][0] - 1) != getf(i)) pf[pf[i]] = pf[a1[i][0] - 1];
    }
  }
  for (int i = 0; i <= n; i++)
    if (getf(i) == i) id[pf[i]] = ++n1;
  for (int i = 0; i <= n; i++) id[i] = id[pf[i]];
  for (int i = 1; i <= n; i++) {
    e[i][0] = id[i - 1];
    e[i][1] = id[i];
    e[i][2] = (calcv(b[i]) + 1) * getPow(calcv(b[i]), P - 2) % P;
  }
  int maxs = 1 << n1;
  for (int i = 0; i < maxs; i++) v[i] = calc(i);
  for (int i = 0; i < maxs; i++)
    if (i & (1 << (id[0] - 1))) f[0][i] = v[i];
  LL t;
  for (int i = 1; i <= 8; i++)
    for (int j = 0; j < maxs; j++)
      if ((t = f[i - 1][j]))
        for (int k = j; k < maxs; k = (k + 1) | j)
          (f[i][k] += t * v[k ^ j]) %= P;
  for (int i = 1; i <= n; i++) n0 -= b[i];
  LL res = getPow(10, n0);
  for (int i = 1; i <= n; i++) (res *= calcv(b[i])) %= P;
  return f[8][maxs - 1] * res % P;
}

int main() {
  freopen("A.in", "r", stdin);
  freopen("A.ans", "w", stdout);
  scanf("%d%d", &n0, &m);
  printf("%lld\n", (solve() % P + P) % P);
  return 0;
}
