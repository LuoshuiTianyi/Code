#include <cstdio>
#include <iostream>
using namespace std;
int n, a[100001];
struct node {
  int size, nx, be, Min;
  int l;
} k[351];
int main() {
  freopen("1552.in", "r", stdin);
  freopen("1552.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
}
