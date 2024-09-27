struct LB
{
    int N = 60;
    ll a[61] = {0},tmp[61] = {0};
    bool flag = false;
    void add(ll x)
    {
        for(int i = N; i >= 0; i--)
        {
            if((1ll << i) & x)  {
                if(!a[i]) {
                    a[i] = x;
                    return;
                }
                else x ^= a[i];
            }
        }
        flag = true;
    }
    bool check(ll x)
    {
        for(int i = N; i >= 0; i--)
        {
            if(x & (1ll << i)) x ^= a[i];
        }
        return x == 0;
    }
    ll qmax()
    {
        ll ans = 0;
        for(int i = N;i >= 0;i--)
            ans = max(ans,ans ^ a[i]);
        return ans;
    }
    ll qmin()
    {
        if(flag) return 0;
        for(int i = 0;i <= N;i++)
            if(a[i]) return a[i];
    }
    ll query(int k)
    {
        ll res = 0,cnt = 0;
        k -= flag;
        if(!k) return 0;
        for(int i = 0;i <= N;i++)
        {
            for(int j = i - 1;j >= 0;j--)
            {
                if(a[i] & (1ll << j)) a[i] ^= a[j];
            }
            if(a[i]) tmp[cnt++] = a[i];
        }
        if(k >= (1 << cnt)) return -1;
        for(int i = 0;i < cnt;i++)
            if(k & (1ll << i)) res ^= tmp[i];
        return res;
    }
};