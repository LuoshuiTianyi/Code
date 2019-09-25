#include <cstdio>
#include <iostream>
using namespace std;
int main() {
  freopen("5286.out", "r", stdin);
  int a, b, cnt = 0, flag = 0;
  while (cin >> a >> b) {
    cnt++;
    if (b != a + 1 && !flag)
      flag = 1, cout << cnt << endl;
    // cout<<"!";
  }
}
