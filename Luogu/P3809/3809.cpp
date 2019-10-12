#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, M, cnt, rk[1000001], tmp[1000001], sa[1000001], tag[1000001];
char s[1000001];
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
  freopen("3809.in", "r", stdin);
  freopen("3809.out", "w", stdout);
  M = 76;
  scanf("%s", s + 1);
  n = strlen(s + 1);
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
    swap(tmp, rk);
    rk[sa[1]] = cnt = 1;
    for (int i = 2; i <= n; i++)
      rk[sa[i]] = tmp[sa[i]] == tmp[sa[i - 1]] &&
                          tmp[sa[i] + len] == tmp[sa[i - 1] + len]
                      ? cnt
                      : ++cnt;
  }
  for (int i = 1; i <= n; i++)
    printf("%d ", sa[i]);
}
