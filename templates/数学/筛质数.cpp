//法一：复杂度为nlogn的算法也就是最普通的算法，用每一个素数和合数去把后面的筛掉
int n,cnt;
bool st[N];
int prime[N];
void get_prime()
{
    for(int i =2;i <= n;i++)
    {
        if(!st[i]) prime[cnt++] = i;
        for(int j = i;j <= n;j += i) st[j] = true;
    }
}
//法二：埃氏筛法，在法一的基础上进行了优化只需要利用每一个素数去筛后面的合数就可以，复杂度为nloglogn
int v[N],cnt;
void primes(int n)
{
    memset(v,0,sizeof v);
    for(int i = 2;i <= n;i++) {
        if(v[i]) continue;
        cnt++;
        cout << i << endl;
        for(int j = i;j <= n / i;j++) v[i * j] = 1;
    }
}
//法三：最为高效，复杂度为n，是一种线性筛法
int v[N],prime[N];
void primes(int n)
{
    memset(v,0,sizeof v);
    int m = 0;          //质数个数
    for(int i = 2;i <= n;i++) {
        if(v[i] == 0) {
            v[i] = i;
            prime[++m] = i;  //prime存储质数
        }
        for(int j = 1;j <= m;j++) {
            if(prime[j] > v[i] || prime[j] > n / i) break;
            v[i * prime[j]] = prime[j];
        }
    }
    for(int i = 1;i <= m;i++) cout << prime[i] << endl;
}