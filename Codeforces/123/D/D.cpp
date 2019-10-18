#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int Max_n = 1e5 + 5;
int n, M;
long long ans;
int sa[Max_n], rk[Max_n], tp[Max_n], ht[Max_n], buk[Max_n];
int top;
char s[Max_n];
void Bsort() {
  for (int i = 1; i <= M; i++) buk[i] = 0;
  for (int i = 1; i <= n; i++) buk[rk[i]]++;
  for (int i = 1; i <= M; i++) buk[i] += buk[i - 1];
  for (int i = n; i >= 1; i--) sa[buk[rk[tp[i]]]--] = tp[i];
}
struct node {
  int x, v;
} stk[Max_n];
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  scanf("%s", s + 1);
  n = strlen(s + 1);
  M = 26;
  for (int i = 1; i <= n; i++) rk[i] = s[i] - 'a' + 1, tp[i] = i;
  Bsort();
  for (int len = 1, cnt = 0; cnt < n; M = cnt, len <<= 1) {
    cnt = 0;
    for (int i = n - len + 1; i <= n; i++) tp[++cnt] = i;
    for (int i = 1; i <= n; i++)
      if (sa[i] > len) tp[++cnt] = sa[i] - len;
    Bsort();
    swap(tp, rk);
    rk[sa[1]] = cnt = 1;
    for (int i = 2; i <= n; i++) {
      if (tp[sa[i]] != tp[sa[i - 1]] || tp[sa[i] + len] != tp[sa[i - 1] + len]) cnt++;
      rk[sa[i]] = cnt;
    }
  }
  for (int i = 1, len = 0; i <= n; i++) {
    if (len) len--;
    while (s[sa[rk[i] - 1] + len] == s[i + len]) len++;
    ht[rk[i]] = len;
  }
  for (int i = 1; i <= n; i++)
    ans += n - sa[i] + 1 - max(ht[i], ht[i + 1]);
  for (int i = 1; i <= n + 1; i++) {
    int now = i;
    while (top && ht[i] < stk[top].v) {
      int len = i - stk[top].x + 1;
      int num = stk[top].v - max(ht[i], top > 1 ? stk[top - 1].v : 0);
      ans += 1ll * len * (len + 1) / 2 * num;
      now = min(now, stk[top--].x);
    }
    stk[++top] = (node){now, ht[i]};
  }
  cout << ans;
}
