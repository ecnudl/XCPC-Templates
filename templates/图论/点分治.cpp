vector<array<int, 2> > e[N];
array<int, N> del, sz, mx;
int n, k;
ll ans = 0;

void work(int u, int s) {
    int ms = s + 1, root = -1;
    function<void(int, int)> dfs1 = [&] (int x, int fa) {
        sz[x] = 1;
        mx[x] = 0;
        for(auto [y, w] : e[x]) {
            if(del[y] || y == fa) continue;
            dfs1(y, x);
            sz[x] += sz[y];
            mx[x] = max(mx[x], sz[y]);
        }
        mx[x] = max(mx[x], s - sz[x]);
        if(mx[x] < ms) {
            ms = mx[x];
            root = x;
        }
    };
    dfs1(u, -1);
    vector<int> d1{0}, d2;
    auto calc = [&] (vector<int> &d) {
        sort(d.begin(), d.end());
        int m = (int)d.size();
        int r = m - 1;
        ll tmp = 0;
        for(int i = 0;i < m;i++) {
            while(r >= 0 && d[i] + d[r] > k) r--;
            if(i < r) tmp += r - i;
        }
        return tmp;
    };
    for(auto [v, _] : e[root]) {
        if(del[v]) continue;
        d2.clear();
        function<void(int, int, int)> dfs2 = [&] (int x, int fa, int dep) {
            sz[x] = 1;
            d1.push_back(dep);
            d2.push_back(dep);
            for(auto [y, w] : e[x]) {
                if(del[y] || y == fa) continue;
                dfs2(y, x, dep + w);
                sz[x] += sz[y];
            }
        };
        dfs2(v, root, _);
        ans -= calc(d2);
    }
    ans += calc(d1);
    del[root] = 1;
    for(auto [v, w] : e[root]) {
        if(!del[v]) work(v, sz[v]);
    }
}
