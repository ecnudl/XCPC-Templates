int son[N],col[N],cnt[N],sz[N],ans[N],sum,Nowson;
VI e[N];

void cal(int x,int fa,int val) {
    if(!cnt[col[x]]) sum++;
    cnt[col[x]] += val;
    for(auto y : e[x]) {
        if(y == fa || y == Nowson) continue;
        cal(y,x,val);
    }
}

void dsu_on_tree(int x,int fa,bool op) {
    for(auto y : e[x]) {
        if(y == fa || y == son[x]) continue;
        dsu_on_tree(y,x,false);
    }
    if(son[x] != -1) dsu_on_tree(son[x],x,true),Nowson = son[x]; //这里顺序不能调换！
    cal(x,fa,1),Nowson = 0;
    ans[x] = sum;
    if(!op) {
        cal(x,fa,-1);
        sum = 0;
    }
}

void dfs1(int x,int fa) {
    son[x] = -1;
    sz[x] = 1;
    for(auto y : e[x]) {
        if(y == fa) continue;
        dfs1(y,x);
        sz[x] += sz[y];
        if(son[x] == -1 || sz[son[x]] < sz[y]) son[x] = y;
    }
}

void solve() {
    int n;cin >> n;
    for(int i = 1;i < n;i++) {
        int x,y;cin >> x >> y;
        e[x].pb(y);
        e[y].pb(x);
    }
    for(int i = 1;i <= n;i++) cin >> col[i];
    dfs1(1,0);
    dsu_on_tree(1,0,true);
    int m;cin >> m;
    while(m --) {
        int x;cin >> x;
        cout << ans[x] << endl;
    }
}