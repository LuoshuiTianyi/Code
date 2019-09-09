#include <cstdio>
#include <iostream>
using namespace std;
int n, M, cnt, rk[100001], tmp[100001], sa[100001], tag[100001], height[100001];
long long ans;
char s[100002];
void Sort() {
  for (int i = 1; i <= M; i++)
    tag[i] = 0;
  for (int i = 1; i <= n; i++)
    tag[rk[i]]++;
  for (int i = 1; i <= M; i++)
    tag[i] += tag[i - 1];
  for (int i = n; i >= 1; i--)
    sa[tag[rk[tmp[i]]]--] = tmp[i];
}
int main() {
  freopen("2408.in", "r", stdin);
  freopen("2408.out", "w", stdout);
  cin >> n;
  scanf("%s", s + 1);
  M = 76;
  for (int i = 1; i <= n; i++)
    rk[i] = s[i] - '0', tmp[i] = i;
  Sort();
  for (int len = 1; cnt < n; len <<= 1, M = cnt) {
    cnt = 0;
    for (int i = n - len + 1; i <= n; i++)
      tmp[++cnt] = i;
    for (int i = 1; i <= n; i++)
      if (sa[i] > len)
        tmp[++cnt] = sa[i] - len;
    Sort();
    swap(rk, tmp);
    rk[sa[1]] = cnt = 1;
    for (int i = 2; i <= n; i++)
      rk[sa[i]] = tmp[sa[i]] == tmp[sa[i - 1]] &&
                          tmp[sa[i] + len] == tmp[sa[i - 1] + len]
                      ? cnt
                      : ++cnt;
  }
  for (int i = 1, len = 0; i <= n; i++) {
    if (len)
      len--;
    int now = sa[rk[i] - 1];
    while (s[now + len] == s[i + len])
      len++;
    height[rk[i]] = len;
  }
  for (int i = 1; i <= n; i++)
    ans += n - sa[i] + 1 - height[i];
  cout << ans;
}
