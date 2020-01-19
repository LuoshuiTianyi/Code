#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<climits>
#include<queue>
#include<set>
#include<cmath>
#include<map>
#include<bitset>
#include<fstream>
#include<tr1/unordered_map>

typedef long long LL;
using namespace std;
#define pb push_back
#define x first
#define y second

void proc_status()
{
	ifstream t("/proc/self/status");
	cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}

LL read()
{
	LL x = 0, f = 1; int c = getchar();
	while(!isdigit(c)) { if(c == '-') f = 0; c = getchar(); }
	while(isdigit(c)) { x = (x * 10) + (c ^ 48); c = getchar(); }
	return f ? x : -x;
}

LL n, ans;

inline LL Pow(LL x, LL p, LL mod)
{
	LL r = 1;
	while(p)
	{
		if(p & 1) r = (__int128)x * r % mod;
		x = (__int128)x * x % mod; p >>= 1;
	}
	return r;
}

int MR(LL N)
{
	if(N == 1) return 0;
	if(N == 2 || N == 3 || N == 5 || N == 7 || N == 11 || N == 13) return 1;
	if(N % 2 == 0 || N % 3 == 0 || N % 5 == 0 || N % 7 == 0 || N % 11 == 0 || N % 13 == 0) return 0;

	LL b = N - 1, k = 0; while(!(b & 1)) b >>= 1, ++k;
	int T = 5;
	while(T--)
	{
		LL a = rand() % (N - 1) + 1;
		a = Pow(a, b, N);
		for(int i = 1; i <= k; ++i)
		{
			LL c = (__int128)a * a % N;//mul(a, a, N);
			if(c == 1 && a != 1 && a != N - 1) return 0;
			a = c;
		}
		if(a != 1) return 0;
	}
	return 1;
}

inline LL func(LL x, LL p, LL c) { return ((__int128)x * x + c) % p; }

LL find(LL n, LL c)
{
	LL a = rand() % (n - 1) + 1, b = a;
	LL k = 1;
	int i = 0;
	while(1)
	{
		b = func(b, n, c);
		if(a == b) return 0;
		k = (__int128)abs(b - a) * k % n;
		if(!k) return 0;
		++i;
		if(!(i % 127) || __builtin_popcount(i) == 1)
		{
			LL now = __gcd(k, n);
			if(now > 1 && now < n) return now;
		}
		a = func(a, n, c); b = func(b, n, c);
	}
	return 0;
}
void Pollard_rho(LL N)
{
	if(N == 1 || N <= ans) return ;
	if(MR(N)) return (void)(ans = N);

	LL now = 0, c = 19260817;
	while(!now) now = find(N, c--);
	Pollard_rho(now); Pollard_rho(N / now);
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("4718.in", "r", stdin);
  freopen("4718.ans", "w", stdout);
#endif
  int T = read();
  while (T--) {
    n = read(), ans = 0;
    Pollard_rho(n);
    if (ans == n) puts("Prime");
    else cout << ans << endl;
  }
	return 0;
}
