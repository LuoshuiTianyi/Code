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
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 5e3 + 5;
int n;
int s[Max_n];
char S[Max_n];
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read();
  scanf("%s", S + 1);
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] + S[i] - '0';
  while (n && S[n] == '0') n--;
  if (!n) {
    cout << "YES";
    return 0;
  }
  for (int i = 1; i < n; i++) {
    int p = s[i];
    for (int j = i; j <= n; j++)
      if (s[j] == p) p += s[i];
    if (p == s[n] + s[i]) {
      cout << "YES";
      return 0;
    }
  }
  cout << "NO";
}
