const int maxn = 3e5 + 10, mod = 998244353;
int rev[maxn], g[maxn], inv[maxn], fac[maxn], ifac[maxn], Len;

int Pow(int x, int p)
{
	int r = 1;
	while(p)
	{
		if(p & 1) r = (LL)x * r % mod;
		x = (LL)x * x % mod; p >>= 1;
	}
	return r;
}

int get_len(int n)
{
	int len = 1;
	while(len <= n + n) len <<= 1;
	return len;
}

void get_rev(int len)
{
	int z = __builtin_ctz(len);
	for(int i = 0; i < len; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << z - 1);
}

void init(int n)
{
	Len = get_len(n);

	int G = Pow(3, (mod - 1) / Len); g[0] = 1;
	for(int i = 1; i <= Len; ++i) g[i] = (LL)g[i - 1] * G % mod;

	inv[0] = inv[1] = ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
	for(int i = 2; i <= Len; ++i)
	{
		fac[i] = (LL)fac[i - 1] * i % mod;
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
		ifac[i] = (LL)ifac[i - 1] * inv[i] % mod;
	}
}

#define ModI(x) (x >= mod ? x -= mod : 0)
#define ModD(x) (x < 0 ? x += mod : 0)

void DFT(int *A, int len, int fg)
{
	for(int i = 0; i < len; ++i)
		if(rev[i] > i) swap(A[i], A[rev[i]]);

	for(int i = 2; i <= len; i <<= 1)
	{
		int __ = Len / i, mid = i >> 1;
		for(int j = 0; j < len; j += i)
			for(int k = 0; k < mid; ++k)
			{
				int y = (LL)(fg ? g[__ * k] : g[Len - __ * k]) * A[j + k + mid] % mod;
				int x = A[j + k];
				A[j + k] = (x + y); ModI(A[j + k]);
				A[j + k + mid] = (x - y); ModD(A[j + k + mid]);
			}
	}

	if(!fg) for(int i = 0; i < len; ++i) A[i] = (LL)inv[len] * A[i] % mod;
}

void get_inv(int *A, int *B, int x)
{
	static int f[maxn], g[maxn];
	if(x == 1) return (void)(A[0] = Pow(B[0], mod - 2));
	get_inv(A, B, (x + 1) >> 1);

	int len = get_len(x - 1);
	for(int i = 0; i < (x + 1) >> 1; ++i) f[i] = A[i]; for(int i = (x + 1) >> 1; i < len; ++i) f[i] = 0;
	for(int i = 0; i < x; ++i) g[i] = B[i]; for(int i = x; i < len; ++i) g[i] = 0;

	get_rev(len); 
	DFT(f, len, 1); DFT(g, len, 1);
	for(int i = 0; i < len; ++i) f[i] = (LL)f[i] * f[i] % mod * g[i] % mod;
	DFT(f, len, 0);

	for(int i = (x + 1) >> 1; i < x; ++i) A[i] = mod - f[i];
}

void get_ln(int *A, int *B, int x)
{
	static int f[maxn], g[maxn];

	int len = get_len(x - 1);
	for(int i = 0; i < x; ++i) f[i] = B[i]; for(int i = x; i < len; ++i) f[i] = 0;
	get_inv(g, f, x); for(int i = x; i < len; ++i) g[i] = 0;
	for(int i = 0; i < x - 1; ++i) f[i] = (LL)B[i + 1] * (i + 1) % mod; f[x] = 0;

	get_rev(len);
	DFT(g, len, 1); DFT(f, len, 1);
	for(int i = 0; i < len; ++i) f[i] = (LL)f[i] * g[i] % mod;
	DFT(f, len, 0);

	for(int i = 1; i < x; ++i) A[i] = (LL)f[i - 1] * inv[i] % mod; A[0] = 0;
}

void get_exp(int *A, int *B, int x)
{
	static int f[maxn], g[maxn];
 	if(x == 1) return (void)(A[0] = 1);
	get_exp(A, B, (x + 1) >> 1);

	int len = get_len(x - 1) >> 1;
	for(int i = 0; i < (x + 1) >> 1; ++i) f[i] = A[i]; for(int i = (x + 1) >> 1; i < len; ++i) f[i] = 0;
	get_ln(g, f, x); for(int i = x; i < len; ++i) g[i] = 0;
	for(int i = 0; i < x; ++i) g[i] = B[i] - g[i], ModD(g[i]); g[0]++;

	get_rev(len);
	DFT(f, len, 1); DFT(g, len, 1);
	for(int i = 0; i < len; ++i) f[i] = (LL)f[i] * g[i] % mod;
	DFT(f, len, 0);

  	for(int i = (x + 1) >> 1; i < x; ++i) A[i] = f[i];
}
