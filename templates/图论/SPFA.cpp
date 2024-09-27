struct node {
    int idx;
    int w;
};
vector<node> P[N];
int dist[N],cnt[N];
bool st[N];
int n,m;

void spfa()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true;
    while(q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        for(auto it : P[t])
        {
            int j = it.idx;
            int dis = it.w;
            if(dist[j] > dist[t] + dis)
            {
                dist[j] = dist[t] + dis;
                //cnt[j] = cnt[t] + 1;
                //if(cnt[j] >= n) return true;     表示有负环
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}