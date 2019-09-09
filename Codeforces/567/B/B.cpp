#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
int l, pos1, pos2;
int len1, len2, s[100001], ans1[100001], ans2[100001];
char S[100001];
bool pd() {
  if (len1 < len2) return 1;
  if (len1 > len2) return 0;
  for (int i = len1; i >= 1; i--) {
    if (ans1[i] > ans2[i]) return 0;
    if (ans1[i] < ans2[i]) return 1;
  }
  return 1;
}
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  cin >> l;
  scanf("%s", S + 1);
  for (int i = 1; i <= l; i++) s[i] = S[i] - '0';
  for (int i = (l + 1) / 2; i > 1; i--)
    if (S[i] != '0') {
      pos1 = i;
      break;
    }
  for (int i = (l + 1) / 2 + 1; i <= l; i++)
    if (S[i] != '0') {
      pos2 = i;
      break;
    }
  len1 = len2 = l;
  if (pos1) {
    int x;
    for (int i = pos1 - 1, cnt = 1; i >= 1; i--, cnt++) ans1[cnt] = s[i];
    x = 0;
    for (int i = l, cnt = 1; i >= pos1; i--, cnt++) {
      ans1[cnt] += s[i] + x;
      x = ans1[cnt] / 10;
      ans1[cnt] %= 10;
    }
    len1 = l - pos1 + 1;
    if (x) ans1[++len1] = x;
  } else
    for (int i = 1; i <= l; i++) ans1[i] = 9;
  if (pos2) {
    int x;
    for (int i = pos2 - 1, cnt = 1; i >= 1; i--, cnt++) ans2[cnt] = s[i];
    x = 0;
    for (int i = l, cnt = 1; i >= pos2; i--, cnt++) {
      ans2[cnt] += s[i] + x;
      x = ans2[cnt] / 10;
      ans2[cnt] %= 10;
    }
    len2 = pos2 + 1;
    if (x) ans2[++len2] += x;
  } else
    for (int i = 1; i <= l; i++) ans2[i] = 9;
  if (pd())
    for (int i = len1; i >= 1; i--) cout << ans1[i];
  else
    for (int i = len2; i >= 1; i--) cout << ans2[i];
  cout<<endl;
}
