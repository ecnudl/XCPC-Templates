int d[N][N];

void Floyd()
{
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
}

int main()
{
    cin >> n >> m >> k;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(i == j) d[i][j] = 0;
            else d[i][j] = INF;
            
    for(int i = 0;i < m;i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        d[a][b] = min(d[a][b], w);
        d[b][a] = min(d[b][a], w);
    }
    
    Floyd();
    
    while(k --)
    {
        int a,b;
        cin >> a >> b;
        if(d[a][b] >= INF/2) puts("impossible");
        else cout << d[a][b] << endl;
    }
    
    return 0;
}