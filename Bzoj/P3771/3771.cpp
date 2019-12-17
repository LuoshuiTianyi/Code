#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define cp complex<double>
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 4e5 + 5, Ml = 1.2e5 + 5;
int Ans[Ml];
cp A[Max_n], B[Max_n], C[Max_n];

namespace Input {
void main() {
  int n = read();
  for (int i = 1, x; i <= n; i++) 
    x = read(), A[x] += 1, B[x * 2] += 1, C[x * 3] += 1;
}
}  // namespace Input

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3771.in", "r", stdin);
  freopen("3771.out", "w", stdout);
#endif
  Input::main();
  
  Solve::main();
}
