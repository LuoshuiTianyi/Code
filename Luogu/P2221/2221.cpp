#include <cstdio>
#include <iostream>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
int n, m;
long long x, L, R, ans[4], a[100001], q1[100001], q2[100001], adv[400001],
    sum[4][400001];
char opt;
void pushup(int o) {
  for (int i = 1; i <= 3; i++)
    sum[i][o] = sum[i][ls] + sum[i][rs];
}
void pushdown(int o, int l, int r) {
  sum[1][ls] += 1ll * adv[o] * (mid - l + 1);
  sum[2][ls] += adv[o] * (q1[mid] - q1[l - 1]);
  sum[3][ls] += adv[o] * (q2[mid] - q2[l - 1]);
  sum[1][rs] += 1ll * adv[o] * (r - mid);
  sum[2][rs] += adv[o] * (q1[r] - q1[mid]);
  sum[3][rs] += adv[o] * (q2[r] - q2[mid]);
  adv[ls] += adv[o], adv[rs] += adv[o];
  adv[o] = 0;
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o] += x;
    sum[1][o] += 1ll * x * (r - l + 1);
    sum[2][o] += x * (q1[r] - q1[l - 1]);
    sum[3][o] += x * (q2[r] - q2[l - 1]);
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    add(ls, l, mid);
  if (mid < R)
    add(rs, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    for (int i = 1; i <= 3; i++)
      ans[i] += sum[i][o];
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    query(ls, l, mid);
  if (mid < R)
    query(rs, mid + 1, r);
  pushup(o);
}
long long gcd(long long a, long long b) { return !b ? a : gcd(b, a % b); }
int main() {
  freopen("2221.in", "r", stdin);
  freopen("2221.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    q1[i] = q1[i - 1] + 1ll * i;
    q2[i] = q2[i - 1] + 1ll * i * i;
  }
  while (m--) {
    scanf("%s%lld%lld", &opt, &L, &R);
    R--;
    if (opt == 'C') {
      scanf("%lld", &x);
      add(1, 1, n);
    } else {
      ans[1] = ans[2] = ans[3] = 0;
      query(1, 1, n);
      long long Ans = (R - L + 1 - R * L) * ans[1] + (L + R) * ans[2] - ans[3],
                Tot = (R - L + 2) * (R - L + 1) / 2;
      long long Gcd = gcd(Ans, Tot);
      printf("%lld/%lld\n", Ans / Gcd, Tot / Gcd);
    }
  }
}
