#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
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
const int Max_n = 1e5 + 5, M = 26;
int n, ans, num[Max_n << 1];
int nu[Max_n << 1], Ans[Max_n << 1];
char S[Max_n];
namespace SAM {
int las = 1, cnt = 1;
struct node {
  int fa, len, ch[M];
} k[Max_n << 1];
void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].len = k[p].len + 1;
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
void dfs(int x, int pos, int len) {
  if (!x) x = 1, len = 0;
  nu[x] = max(nu[x], len);
  //cout << x << " " << nu[x] << endl;
  if (pos == n + 1) return;
  int v = S[pos] - 'a';
  for (; x && !k[x].ch[v]; x = k[x].fa) len = k[k[x].fa].len;
  dfs(k[x].ch[v], pos + 1, len + 1);
}
bool cmp(int a, int b) { return k[a].len < k[b].len; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("1812.in", "r", stdin);
  freopen("1812.out", "w", stdout);
#endif
  scanf("%s", S + 1);
  n = strlen(S + 1);
  for (int i = 1; i <= n; i++) {
    add(S[i] - 'a');
    //cout << las << " ";
  }
  //cout << endl;
  for (int i = 1; i <= cnt; i++) num[i] = i, Ans[i] = k[i].len;
  sort(num + 1, num + cnt + 1, cmp);
  while (~scanf(" %s", S + 1)) {
    memset(nu, 0, sizeof(nu));
    n = strlen(S + 1);
    dfs(1, 1, 0);
    for (int i = cnt; i; i--) {
      int x = num[i];
      //cout << x << " " << nu[x] << endl;
      Ans[x] = min(Ans[x], nu[x]), nu[k[x].fa] = max(nu[k[x].fa], nu[x]);
    }
    //cout << endl;
  }
  for (int i = 2; i <= cnt; i++) ans = max(ans, Ans[i]);
  cout << ans;
}
