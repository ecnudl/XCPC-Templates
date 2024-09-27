struct LCA {
    const int N;
    int n, idx;
    vector<int> id, rid, dep, fa;
    vector<vector<int>> e, st;

    LCA(int n) : N(__lg(n) + 1), n(n), idx(0), id(n, -1), rid(n), dep(n), fa(n), e(n), st(N, vector<int>(n)) {}

    void add(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    int getMin(int x, int y) {
        return dep[x] < dep[y] ? x : y;
    }

    void dfs(int u) {
        id[u] = idx;
        rid[idx] = u;
        idx++;

        for (int v : e[u]) {
            if (id[v] != -1) {
                continue;
            }

            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs(v);
        }
    }

    void work(int rt = 0) {
        dep[rt] = 1;
        dfs(rt);

        for (int i = 0; i < n; ++i) {
            st[0][i] = rid[i];
        }

        for (int i = 1; i < N; ++i) {
            for (int j = 0; j + (1 << i) - 1 < n; ++j) {
                st[i][j] = getMin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int getLca(int x, int y) {
        if (x == y) {
            return x;
        }
        x = id[x], y = id[y];
        if (x > y) {
            swap(x, y);
        }
        ++x;
        int z = __lg(y - x + 1);
        return fa[getMin(st[z][x], st[z][y - (1 << z) + 1])];
    }
};


int dist[N],dep[N],n,m,rt;
VI e[N];
int fa[N][M];
void dfs(int x,int fan)
{
    fa[x][0] = fan;
    dep[x] = dep[fan] + 1;
    for(int i = 1;i < M;i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(auto y : e[x])
    {
        if(y == fan) continue;
        dist[y] = dist[x] + 1;
        dfs(y,x);
    }
}
int LCA(int x, int y)
{
    int a = dep[x],b = dep[y];
    if(a > b) swap(x, y);
    int tmp = dep[y] - dep[x];
    for(int i = 0;i < M;i++) {
        if(Bit(i) & tmp) y = fa[y][i];
    }
    if(y == x) return x;
    for(int i = M - 1;i >= 0;i--)
    {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
void solve() {
    cin >> n >> m >> rt;
    for(int i = 1;i < n;i++)
    {
        int a,b;cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(rt,0);
    while(m --)
    {
        int a,b;cin >> a >> b;
        int c = LCA(a,b);
        cout << c << endl;
    }
}