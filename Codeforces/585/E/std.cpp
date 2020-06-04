#include "algorithm"
#include "cstdio"
#include "cstring"
#include "iostream"
#include "queue"
using namespace std;
#define MAXN 10000006
#define P 1000000007
int n;
int A[500006], c[MAXN], _[500006], mu[MAXN], s[MAXN];
int pri[MAXN], en, lim;
void sieve(int x) {
  pri[0] = 1;
  mu[1] = 1;
  for (int i = 2; i <= x; ++i) {
    if (!pri[i]) pri[++en] = i, mu[i] = -1;
    for (int j = 1; i * pri[j] <= x && j <= en; ++j) {
      pri[i * pri[j]] = 1;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        break;
      }
      mu[i * pri[j]] = -mu[i];
    }
  }
}
signed main() {
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    scanf("%d", &A[i]), ++c[A[i]], lim = max(lim, A[i]);
  lim = 1e7;
  sieve(lim);
  for (int i = 1; i <= en; ++i)
    for (int j = lim / pri[i]; j; --j) c[j] += c[j * pri[i]];
  //for (int i = 1; i <= lim; ++i) mu[i] *= c[i];
  //for (int i = 1; i <= en; ++i)
  //  for (int j = 1; j * pri[i] <= lim; ++j) (mu[j * pri[i]] += mu[j]) %= P;
  //_[0] = 1;
  //for (int i = 1; i < 500006; ++i) _[i] = _[i - 1] * 2 % P;
  //for (int i = 1; i <= lim; ++i) s[i] = _[c[i]] - 1;
  //for (int i = en; i; --i)
  //  for (int j = 1; j * pri[i] <= lim; ++j) (s[j] -= s[j * pri[i]]) %= P;
  //int ans = 0;
  //for (int i = 2; i <= lim; ++i) (ans += 1ll * s[i] * mu[i] % P) %= P;
  //cout << (ans + P) % P << endl;
}
