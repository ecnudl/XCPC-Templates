int fpow(int x, int t = mod - 2) {
	int res = 1;
	for (; t; t >>= 1, x = 1ll * x * x % mod)
		if (t & 1) res = 1ll * res * x % mod;
	return res;
}

int fac[N], ifac[N];

int C(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void init() //这里是处理阶乘和每个数字的逆元，fac[i]存的是i!,ifac[i]存的是i!的逆元，方便运算
{
    fac[0] = ifac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[N - 1] = fpow(fac[N - 1]);
	for (int i = N - 2; i; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}
//杨辉三角：
int C[N][N];
void init()
{
    for(int i = 0;i <= n;i++)
        C[i][i] = 1,C[i][0] = 1;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j < i;j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}