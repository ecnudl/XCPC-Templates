// 单哈希:
const int P = 131;
char str[N];
int n,m;
ULL h[N],p[N];

ULL count(int l,int r)
{
    return h[r] - h[l-1] * p[r - l + 1];      //此处运用一个移位思想，就比如要取出数字1234中的34，就应该让1234-12*100，就是这种原理取出l,r之间的哈希值
}

int main()
{
    cin >> n >> m >> str+1;
    p[0] = 1;
    for(int i = 1;i <= n;i++)
    {
        p[i] = P * p[i-1];
        h[i] = h[i-1] * P + str[i];
    }
    
    while(m--)
    {
        int l1,r1,l2,r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if(count(l1,r1) == count(l2,r2)) puts("Yes");
        else puts("No");
    }
    
    return 0;
}



#define rep(i, j, k) for(int i = j; i <= k; ++i)
const int C = 2; // Hash次数(只能单哈希/双哈希)
const int N = ;  // 字符串最大长度

const int Prime[] = {2333, 23333, 1000000021};  // 备用质数库
const int p[] = {233, 911, 146527, 19260817, 91815541};
const int mod[] = {9217129, 29123, 998244353, 1000000009};
int pw[C][N];

struct Hash {
    vector<int> h[C];
    // 下面两种初始化方法选一个使用即可.
    void init(int n, int* s) {
        rep(k, 0, C - 1) h[k].resize(n + 1);
        rep(k, 0, C - 1) {
            rep(i, 1, n) {
                h[k][i] = ((ll)h[k][i - 1] * p[k] + s[i]) % mod[k];
            }
        }
    }
    ll get(int l, int r) {
        ll res = 0;
        rep(k, 0, C - 1) {
            int v = (h[k][r] - (ll)h[k][l - 1] * pw[k][r - l + 1]) % mod[k];
            if (v < 0) v += mod[k];
            res += k ? ((ll)v << 30) : v; 
        }
        return res;
    }
    ll get(int l, int r, int d) {         //这个函数是计算一个字符串的一段在另一个字符串的哈希值，d是距离字符串尾部的位置。
        ll res = 0;
        rep(k, 0, C - 1) {
            int v = (h[k][r] - (ll)h[k][l - 1] * pw[k][r - l + 1]) % mod[k] * pw[k][d] % mod[k];
            if (v < 0) v += mod[k];
            res += k ? ((ll)v << 30) : v; 
        }
        return res;
    }
};

// 放在多测外面(main函数内部)
rep(k, 0, C - 1) {
    pw[k][0] = 1;
    rep(i, 1, N - 1) {
        pw[k][i] = (ll)pw[k][i - 1] * p[k] % mod[k];
    }
}