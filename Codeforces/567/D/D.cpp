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
int n, m, Q;
int que[500001], num[500001];
int q[500001],top,now;
long long D;
struct node {
  int x, d;
} k[500001];
bool cmp(node a, node b) { return a.x == b.x ? a.d < b.d : a.x < b.x; }
bool cmp2(int a, int b) { return que[a] < que[b]; }
int main() {
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
  read(n), read(m), read(Q);
  int x;
  for (int i = 1; i <= n; i++) read(x), k[x].x++;
  sort(k + 1, k + m + 1, cmp);
  for (int i = 1; i <= Q; i++) read(que[i]), num[i] = i;
  sort(num + 1, num + Q + 1, cmp2);
  now=1,k[0].x=-1;
  for(int i=1;i<=m;i++)
  {
    if(k[i].x!=k[i-1].x)
      while(que[num[now]]<D+1ll*(i-1)*(k[i].x-k[i-1].x)) {
        que[num[now]]=(que[num[now]]-D)%(i-1);
        if(!que[num[now]])que[num[now]]=q[i-1];
        now++;
      }
  }
}
