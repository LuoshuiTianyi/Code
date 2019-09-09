#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
bool book[26];
char S[1001], T[1001], ym[5] = {'a', 'o', 'e', 'i', 'u'};
int main() {
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
  for (int i = 0; i < 5; i++)
    book[ym[i] - 'a'] = true;
  cin >> S >> T;
  int lens = strlen(S), lent = strlen(T);
  if (lens != lent) {
    cout << "No";
    return 0;
  }
  for (int i = 0; i < lens; i++)
    if (book[S[i] - 'a'] != book[T[i] - 'a']) {
      cout << "No";
      return 0;
    }
  cout << "Yes";
}
