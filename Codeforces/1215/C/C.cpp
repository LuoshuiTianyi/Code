#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5;
int n;
int s[Max_n], t[Max_n];
int top, opt[2][Max_n << 1];
char S[Max_n], T[Max_n];
queue<int> q1, q2;
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read();
  scanf("%s", S + 1), scanf("%s", T + 1);
  for (int i = 1; i <= n; i++) s[i] = S[i] == 'a' ? 0 : 1;
  for (int i = 1; i <= n; i++) t[i] = T[i] == 'a' ? 0 : 1;
  for (int i = 1; i <= n; i++)
    if (s[i] ^ t[i]) {
      if (s[i])
        q1.push(i);
      else
        q2.push(i);
    }
  if ((q1.size() + q2.size()) & 1) {
    cout << "-1";
    return 0;
  }
  while (!q1.empty() || !q2.empty()) {
    if (q1.size() > 1) {
      top++, opt[0][top] = q1.front(), q1.pop();
      opt[1][top] = q1.front(), q1.pop();
    } else if (q2.size() > 1) {
      top++, opt[0][top] = q2.front(), q2.pop();
      opt[1][top] = q2.front(), q2.pop();
    } else {
      top++, opt[0][top] = q1.front(), opt[1][top] = q1.front();
      q2.push(q1.front()), q1.pop();
    }
  }
  cout << top << endl;
  for (int i = 1; i <= top; i++) printf("%d %d\n", opt[0][i], opt[1][i]);
}
