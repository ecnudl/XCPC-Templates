const int N = 2e5 + 10;
bool vis[N],ins[N];
vector<int> e[N];
int ne[N],n;

void dfs(int x)
{
    vis[x] = true;
    ins[x] = true;
    for(auto t : e[x])
    {
        if(ins[t])
        {
            vector<int> ans;
            int u = ne[t];
            while(u != t)
            {
                ans.pb(u);
                u = ne[u];
            }
            ans.pb(t);
            cout << ans.size() << endl;
            for(auto k : ans) cout << k << " ";
            exit(0);
        }
        if(vis[t]) continue;
        dfs(t);
    }
    ins[x] = false;
}

void solve() {
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        int x;cin >> x;
        e[i].pb(x);
        ne[i] = x;
    }
    for(int i = 1;i <= n;i++) if(!vis[i]) dfs(i);
}
const int N = 2e5 + 10;
int p[N],ne[N],ans[N];
int n,cnt;
 
int find(int x)
{
    if(x != p[x]) p[x] = find(p[x]);
    return p[x];
}
 
void solve() {
    cin >> n;
    for(int i = 1;i <= n;i++) p[i] = i;
    for(int i = 1;i <= n;i++)
    {
        int x,a,b;
        cin >> x;
        a = find(i);
        b = find(x);
        if(a == b)
        {
            cnt = 1;
            for(int j = x;j != i;j = ne[j])
            {
                ans[cnt++] = j;
            }
            cout << cnt << endl;
            for(int k = 1;k < cnt;k++) cout << ans[k] << " ";
            cout << i;
            return;
        }
        else
        {
            ne[i] = x;
            p[b] = a;
        }
    }
}

int val[maxn + 1][maxn + 1];  // 原图的邻接矩阵

int floyd(const int &n) {
  static int dis[maxn + 1][maxn + 1];  // 最短路矩阵
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) dis[i][j] = val[i][j];  // 初始化最短路矩阵
  int ans = inf;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i < k; ++i)
      for (int j = 1; j < i; ++j)
        ans = std::min(ans, dis[i][j] + val[i][k] + val[k][j]);  // 更新答案
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[i][j] = std::min(
            dis[i][j], dis[i][k] + dis[k][j]);  // 正常的 floyd 更新最短路矩阵
  }
  return ans;
}