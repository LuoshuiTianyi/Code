#include <bits/stdc++.h>
using namespace std;
#define Re register
#define fo(i, a, b) for (Re int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (Re int i = (a); i >= (b); --i)
#define edge(i, u) \
  for (Re int i = head[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define pb push_back
#define F first
#define S second
#define ll long long
#define inf 1000000007
#define mp std::make_pair
#define lowbit(x) (x & -x)
#define eps 1e-4
#define itset std::set<node>::iterator
#define lb lower_bound
#define N 605
#define M 4000005
#define mod 1000000007
int n, k, pi[N], x, y, sum[N];
ll g[N], dp[N][N], ans;
inline int f(int x, int y) { return y - x + 1 - (sum[y] - sum[x - 1]); }
int main() {
  freopen("D.in", "r", stdin);
  freopen("D.ans", "w", stdout);
  scanf("%d %d", &n, &k);
  fo(i, 1, k) {
    scanf("%d %d", &x, &y);
    pi[x] = y;
    pi[y] = x;
    sum[x] = 1;
    sum[y] = 1;
  }
  n <<= 1;
  fo(i, 2, n) sum[i] += sum[i - 1];
  g[0] = 1;
  for (int i = 2; i <= n; i += 2) g[i] = (i - 1) * g[i - 2] % mod;
  fo(i, 1, n) {
    fo(j, i, n) if ((j - i) & 1) {
      bool flag = 0;
      fo(k, i, j) if (pi[k] && pi[k] < i || pi[k] > j) {
        flag = 1;
        break;
      }
      if (flag) continue;
      dp[i][j] = g[f(i, j)];
      fo(k, i + 1, j - 1) dp[i][j] =
          (dp[i][j] - dp[i][k] * g[f(k + 1, j)]) % mod;
      cout << i << " " << j << " " << dp[i][j] << " " << f(1, i - 1) + f(j + 1, n) << endl;
    }
  }
  k <<= 1;
  fo(i, 1, n) fo(j, i, n) if (dp[i][j]) ans =
      (ans + dp[i][j] * g[n - (j - i + 1) - (k - sum[j] + sum[i - 1])]) % mod;
  printf("%lld\n", ans);
  return 0;
}
