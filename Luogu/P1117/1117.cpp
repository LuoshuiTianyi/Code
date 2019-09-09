#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int p, T, n, M, cnt, tag[30001], sa[2][30001], rk[2][30001], h[2][30001],
    tp[2][30001], rmq[2][30001][16], Log[40001], a[30002], b[30002];
long long ans;
char s[2][30002];
void Sort(int x) {
  for (int i = 1; i <= M; i++)
    tag[i] = 0;
  for (int i = 1; i <= n; i++)
    tag[rk[x][i]]++;
  for (int i = 1; i <= M; i++)
    tag[i] += tag[i - 1];
  for (int i = n; i >= 1; i--)
    sa[x][tag[rk[x][tp[x][i]]]--] = tp[x][i];
}
int find(int x, int l, int r) {
  if (l > r)
    swap(l, r);
  l++;
  int L = Log[r - l + 1];
  return min(rmq[x][l][L], rmq[x][r - (1 << L) + 1][L]);
}
int main() {
  freopen("1117.in", "r", stdin);
  freopen("1117.out", "w", stdout);
  cin >> T;
  int now = 1, num = -1, top = 2;
  Log[1] = 0;
  for (int i = 1; i <= 15; i++) {
    now <<= 1, num++;
    while (top <= now)
      Log[top++] = num;
  }
  while (T--) {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(rk, 0, sizeof(rk));
    memset(tp, 0, sizeof(tp));
    scanf("%s", s[0] + 1);
    n = strlen(s[0] + 1);
    for (int i = 1; i <= n; i++)
      s[1][i] = s[0][n - i + 1];
    M = 76;
    for (int i = 1; i <= n; i++)
      rk[0][i] = s[0][i] - 'a' + 1, tp[0][i] = i;
    for (int i = n; i >= 1; i--)
      rk[1][i] = s[1][i] - 'a' + 1, tp[1][i] = i;
    Sort(0), Sort(1);
    for (int l = 0; l < 2; l++) {
      cnt = 0;
      for (int len = 1; cnt < n; len <<= 1, M = cnt) {
        cnt = 0;
        for (int i = n - len + 1; i <= n; i++)
          tp[l][++cnt] = i;
        for (int i = 1; i <= n; i++)
          if (sa[l][i] > len)
            tp[l][++cnt] = sa[l][i] - len;
        Sort(l);
        swap(tp[l], rk[l]);
        rk[l][sa[l][1]] = cnt = 1;
        for (int i = 2; i <= n; i++)
          rk[l][sa[l][i]] =
              tp[l][sa[l][i]] == tp[l][sa[l][i - 1]] &&
                      tp[l][sa[l][i] + len] == tp[l][sa[l][i - 1] + len]
                  ? cnt
                  : ++cnt;
      }
    }
    for (int l = 0; l < 2; l++) {
      for (int i = 1, len = 0; i <= n; i++) {
        if (len)
          len--;
        int now = sa[l][rk[l][i] - 1];
        while (s[l][now + len] == s[l][i + len])
          len++;
        rmq[l][rk[l][i]][0] = len;
      }
      for (int j = 1; j <= 15; j++)
        for (int i = 1; i <= n; i++)
          if (i + (1 << (j - 1)) <= n)
            rmq[l][i][j] =
                min(rmq[l][i][j - 1], rmq[l][i + (1 << (j - 1))][j - 1]);
    }
    for (int len = 1; len <= n / 2; len++)
      for (int i = len; i + len <= n; i += len) {
        int l = i, r = i + len;
        int LCS = find(1, rk[1][n - r + 2], rk[1][n - l + 2]),
            LCP = find(0, rk[0][l], rk[0][r]);
        LCS = min(LCS, len - 1), LCP = min(LCP, len);
        if (LCS + LCP >= len) {
          int same = LCS + LCP - len + 1;
          b[l - LCS]++, b[l - LCS + same]--;
          a[l - LCS + 2 * len - 1]++, a[l - LCS + same + 2 * len - 1]--;
        }
      }
    for (int i = 1; i <= n; i++)
      a[i] += a[i - 1], b[i] += b[i - 1];
    ans = 0;
    for (int i = 1; i < n; i++)
      ans += a[i] * b[i + 1];
    cout << ans << endl;
  }
}
