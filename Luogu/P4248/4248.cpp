#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 5e5 + 5, M = 26;
int n;
long long ans;
int num[Max_n << 1], nu[Max_n << 1];
char S[Max_n];
namespace SAM {
int las = 1, cnt = 1;
struct node {
  int len, fa, ch[M];
} k[Max_n << 1];
void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].len = k[p].len + 1, nu[np] = 1;
  for (; p && !k[p].ch[c]; p = k[p].fa) k[p].ch[c] = np;
  if (!p)
    k[np].fa = 1;
  else {
    int q = k[p].ch[c];
    if (k[q].len == k[p].len + 1)
      k[np].fa = q;
    else {
      int nq = ++cnt;
      k[nq] = k[q], k[nq].len = k[p].len + 1;
      k[q].fa = k[np].fa = nq;
      for (; p && k[p].ch[c] == q; p = k[p].fa) k[p].ch[c] = nq;
    }
  }
}
}  // namespace SAM
using namespace SAM;
bool cmp(int a, int b) { return k[a].len < k[b].len; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("4248.in", "r", stdin);
  freopen("4248.out", "w", stdout);
#endif
  scanf("%s", S + 1);
  n = strlen(S + 1);
  for (int i = n; i >= 1; i--) add(S[i] - 'a');
  for (int i = 1; i <= cnt; i++) num[i] = i;
  sort(num + 1, num + cnt + 1, cmp);
  for (int i = cnt; i; i--) {
    int x = num[i];
    nu[k[x].fa] += nu[x];
    ans += 1ll * nu[x] * (n - nu[x]) * (k[x].len - k[k[x].fa].len);
  }
  cout << ans;
}
