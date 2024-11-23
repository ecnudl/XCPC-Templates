struct DSU {
    int n;
    vector<int> fa, siz;

    DSU(int n) : n(n) {
        init(n);
    }

    void init(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x) {return (x == fa[x] ? x : fa[x] = find(fa[x]));}

    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        fa[fy] = fx;
        siz[fx] += siz[fy];
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

//可撤销并查集
struct DSU{
    int n = 0, tot = 0, fa[N], sz[N], s[N * 20];
    void ins() { n++, fa[n] = n, sz[n] = 1;}//插入节点
    int F(int x) { return fa[x] == x ? x : F(fa[x]); }//即find查找函数
    void U(int x, int y){//合并函数
        x = F(x), y = F(y);
        if(x == y) return;
        if(sz[x] < sz[y]) swap(x, y);
        s[++tot] = y, fa[y] = x, sz[x] += sz[y];
    }
    void D(){//删除栈顶边
        if(!tot) return;
        int y = s[tot--]; sz[fa[y]] -= sz[y], fa[y] = y;
    }
    void back(int t = 0){while(tot > t) D();}//删除到只剩t条边
}dsu;