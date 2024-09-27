struct Edge {
    int a,b,w;
}edge[N];

int dist[N],backup[N];
int n,m,k;

void bellman_ford() {
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    for(int i = 0;i < k;i++)
    {
        memcpy(backup,dist,sizeof(dist));
        for(int j = 1;j <= m;j++)
        {
            int a = edge[j].a,b = edge[j].b,w = edge[j].w;
            dist[b] = min(dist[b],backup[a] + w);
        }
    }
}