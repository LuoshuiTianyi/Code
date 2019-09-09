#include <cstdio>
#include <iostream>
using namespace std;
int n, ans, len, Len, a[1001], s[2000001];
int M = 2000, sa[2000001], rk[2000001], tp[2000001], tag[2000001],
    height[2000001], belong[2000001];
void Sort() {
  for (int i = 0; i <= M; i++)
    tag[i] = 0;
  for (int i = 1; i <= Len; i++)
    tag[rk[i]]++;
  for (int i = 1; i <= M; i++)
    tag[i] += tag[i - 1];
  for (int i = Len; i >= 1; i--)
    sa[tag[rk[tp[i]]]--] = tp[i];
}
bool Work(int l, int r) {
  if (l > r)
    return false;
  bool book[1001] = {0};
  for (register int i = l; i <= r; i++)
    book[belong[i]] |= true, book[belong[i - 1]] |= true;
  for (register int i = 1; i <= n; i++)
    if (!book[i])
      return false;
  return true;
}
bool pd(int x) {
  int l = 1, r = 0;
  for (register int i = 1; i <= Len; i++) {
    if (height[i] >= x)
      r = i;
    else {
      if (Work(l, r))
        return true;
      l = i + 1;
    }
  }
  return false;
}
int main() {
  freopen("2463.in", "r", stdin);
  freopen("2463.out", "w", stdout);
  cin >> n;
  for (register int i = 1; i <= n; i++) {
    scanf("%d", &len);
    for (register int j = 1; j <= len; j++)
      scanf("%d", &a[j]);
    for (register int j = 2; j <= len; j++)
      s[++Len] = a[j] - a[j - 1];
    s[++Len] = 2000;
  }
  for (register int i = 1; i <= Len; i++)
    rk[i] = s[i], tp[i] = i;
  Sort();
  for (register int w = 1, cnt = 0; cnt < Len; w <<= 1, M = cnt) {
    cnt = 0;
    for (register int i = Len - w + 1; i <= Len; i++)
      tp[++cnt] = i;
    for (register int i = 1; i <= Len; i++)
      if (sa[i] > w)
        tp[++cnt] = sa[i] - w;
    Sort();
    swap(tp, rk);
    rk[sa[1]] = cnt = 1;
    for (register int i = 2; i <= Len; i++)
      rk[sa[i]] =
          tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + w] == tp[sa[i - 1] + w]
              ? cnt
              : ++cnt;
  }
  for (register int i = 1, same = 0; i <= Len; i++) {
    if (same)
      same--;
    int now = sa[rk[i] - 1];
    while (s[now + same] == s[i + same])
      same++;
    height[rk[i]] = same;
  }
  int now = 1, l = 1, r = 1000;
  for (register int i = 1; i <= Len; i++)
    if (s[i] == 2000)
      now++;
    else
      belong[rk[i]] = now;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (pd(mid))
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  cout << ans + 1;
}
