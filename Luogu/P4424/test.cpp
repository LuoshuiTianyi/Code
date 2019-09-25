#include <bits/stdc++.h>
#define fp(i, a, b) for (register int i = a, I = b + 1; i < I; ++i)
#define fd(i, a, b) for (register int i = a, I = b - 1; i > I; --i)
#define go(u)                                                                  \
  for (register int i = fi[u], v = e[i].to; i; v = e[i = e[i].nx].to)
#define file(s) freopen(s ".in", "r", stdin), freopen("test.out", "w", stdout)
template <class T> inline bool cmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}
template <class T> inline bool cmin(T &a, const T &b) {
  return a > b ? a = b, 1 : 0;
}
using namespace std;
const int N = 5005, P = 1e9 + 7;
typedef int arr[N];
int n, m, q, c[2];
arr a, b, s, t, Mi;
char p[N];
inline int pls(int a, int b) { return a += b, a < P ? a : a - P; }
inline int sub(int a, int b) { return a -= b, a < 0 ? a + P : a; }
int main() {
#ifndef ONLINE_JUDGE
  file("4424");
#endif
  scanf("%d%d%d\n", &n, &m, &q);
  Mi[1] = 1;
  fp(i, 2, n + 1) Mi[i] = (Mi[i - 1] << 1) % P;
  fp(i, 1, m) a[i] = i;
  fp(i, 1, n) {
    scanf("%s", p + 1);
    c[0] = 0, c[1] = m;
    fp(j, 1, m) p[j] == '1' ? s[j] = pls(s[j], Mi[i]) : ++c[0];
    fd(j, m, 1) b[c[p[a[j]] - 48]--] = a[j];
    swap(a, b);
  }
  fp(i, 1, m) t[i] = s[a[i]];
  register int up, dw;
  t[m + 1] = Mi[n + 1];
  while (q--) {
    scanf("%s", p + 1);
    up = m + 1, dw = 0;
    fd(i, m, 1) if (p[a[i]] == '0') {
      dw = i;
      break;
    }
    fp(i, 1, m) if (p[a[i]] == '1') {
      up = i;
      break;
    }
    printf("%d\n", up < dw ? 0 : sub(t[up], t[dw]));
  }
  return 0;
}
