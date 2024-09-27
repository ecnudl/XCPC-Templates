//1.Prim算法：
int n,m;
bool st[N];
int g[N][N];
int dist[N],pre[N];

int prim()
{
    memset(dist,0x3f,sizeof dist);
    int res = 0;
    for(int i = 0;i < n;i++)
    {
        int t = -1;
        for(int j = 1;j <= n;j++)
        {
            if(!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }
        
        if(i && dist[t] == INF) return INF;
        
        if(i) res += dist[t];
        st[t] = true;
        
        for(int j = 1;j <= n;j++)
        {
            if(dist[j] > g[t][j] && !st[j])
            {
                dist[j] = g[t][j];
                pre[j] = t;
            }
        }
    }
    return res;
}
// 2.Krusktal算法：
const int N = 2e5 + 10;
struct Edge
{
    int a,b,w;
    bool operator < (Edge &M) const
    {
        return w < M.w;
    }
}edge[N];

int p[N];
int n,m;
int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i++) p[i] = i;
    for(int i = 1;i <= m;i++)
    {
        int a,b,w;cin >> a >> b >> w;
        edge[i] = {a,b,w};
    }
    sort(edge + 1,edge + 1 + m);
    int cnt = 0,res = 0;
    for(int i = 1;i <= m;i++)
    {
        int a = edge[i].a,b = edge[i].b,w = edge[i].w;
        int x = find(a);
        int y = find(b);
        if(x != y)
        {
            p[x] = y;
            res += w;
            cnt++;
        }
        else continue;
    }
    if(cnt < n-1) puts("impossible");
    else cout << res << endl;
}