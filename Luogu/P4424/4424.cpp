#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 1e9 + 7;
int n, m, Q, tag[2], ra[5002], rb[5002], num[5001], mi[1002], t[5002];
char s[5002], q[5002];
void Mod(int &x) { x = (x % mod + mod) % mod; }
int main() {
  freopen("4424.in", "r", stdin);
  freopen("4424.out", "w", stdout);
  cin >> n >> m >> Q;
  mi[1] = 1;
  for (int i = 2; i <= n + 1; i++)
    mi[i] = (mi[i - 1] << 1) % mod;
  for (int i = 1; i <= m; i++)
    ra[i] = i;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    tag[0] = 0, tag[1] = m;
    for (int j = 1; j <= m; j++) {
      Mod(num[j] += s[j] == '1' ? mi[i] : 0);
      if (s[j] == '0')
        tag[0]++;
    }
    for (int j = m; j >= 1; j--)
      rb[tag[s[ra[j]] - '0']--] = ra[j];
    swap(ra, rb);
  }
  ra[m + 1] = m + 1;
  num[m + 1] = mi[n + 1];
  while (Q--) {
    scanf("%s", q + 1);
    int l = 0, r = m + 1;
    for (int i = 1; i <= m; i++)
      if (q[ra[i]] == '1') {
        r = i;
        break;
      }
    for (int i = m; i >= 1; i--)
      if (q[ra[i]] == '0') {
        l = i;
        break;
      }
    if (l > r)
      cout << "0\n";
    else
      printf("%d\n", ((num[ra[r]] - num[ra[l]]) % mod + mod) % mod);
  }
}
