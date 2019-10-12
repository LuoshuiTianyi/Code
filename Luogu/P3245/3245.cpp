#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, mod, size, rest[100002], L, R, cnt, now[100001], ano[10][100001],
    sum[100001];
char S[100001];
long long ans, answer[100001], q[100001];
struct Que {
  int l, r, q, d;
} k[100001];
struct node {
  int d, rest;
} ls[100002];
bool cmp(Que a, Que b) { return a.q == b.q ? a.r < b.r : a.q < b.q; }
bool cmp2(node a, node b) { return a.rest < b.rest; }
void Del(int x) { ans -= --now[rest[x]]; }
void Add(int x) { ans += now[rest[x]]++; }
int main() {
  freopen("3245.in", "r", stdin);
  freopen("3245.out", "w", stdout);
  cin >> mod >> S >> m;
  n = strlen(S);
  size = sqrt(n);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &k[i].l, &k[i].r);
    k[i].q = k[i].l / size;
    k[i].r++;
    k[i].d = i;
  }
  if (mod == 2 || mod == 5) {
    for (int i = n; i > 0; i--) {
      sum[i] = sum[i + 1];
      if ((S[i - 1] - '0') % mod == 0)
        sum[i]++;
    }
    for (int i = n; i > 0; i--)
      q[i] = sum[i] + q[i + 1];
    for (int i = 1; i <= m; i++)
      printf("%lld\n", q[k[i].l] - q[k[i].r] - (k[i].r - k[i].l) * sum[k[i].r]);
    return 0;
  }
  sort(k + 1, k + m + 1, cmp);
  for (int i = 1; i <= 9; i++) {
    ano[i][1] = i % mod;
    for (int j = 2; j <= n; j++)
      ano[i][j] = 1ll * ano[i][j - 1] * 10 % mod;
  }
  for (int i = n; i >= 1; i--) {
    ls[i].rest = (ls[i + 1].rest + ano[S[i - 1] - '0'][n - i + 1]) % mod;
    ls[i].d = i;
  }
  sort(ls + 1, ls + n + 1, cmp2);
  for (int i = 1; i <= n; i++) {
    if (ls[i].rest > ls[i - 1].rest)
      cnt++;
    rest[ls[i].d] = cnt;
  }
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= m; i++) {
    while (L < k[i].l)
      Del(L++);
    while (L > k[i].l)
      Add(--L);
    while (R < k[i].r)
      Add(++R);
    while (R > k[i].r)
      Del(R--);
    answer[k[i].d] = ans;
  }
  for (int i = 1; i <= m; i++)
    printf("%lld\n", answer[i]);
}
