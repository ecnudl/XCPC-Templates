using Edge = int;
struct HLD{
    int n;
    vector<int> sz, top, dep, fa, dfn, out, rnk;
    vector<vector<Edge> > g;
    int ts;

    HLD(const vector<vector<Edge> > &g, int root = 1) : n(int(g.size()) - 1), g(g)  {
        ts = 0;
        sz.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        fa.resize(n + 1);
        dfn.resize(n + 1);
        out.resize(n + 1);
        rnk.resize(n + 1);
        dep[root] = 1;
        top[root] = root;
        dfs_sz(root);
        dfs_hld(root);
    }

    void dfs_sz(int u){
        if (fa[u]){
            for(auto it = g[u].begin(); it != g[u].end(); it++){
                if (*it == fa[u]){
                    g[u].erase(it);
                    break;
                }
            }
        }
        sz[u] = 1;
        for(auto &j : g[u]){
            fa[j] = u;
            dep[j] = dep[u] + 1;
            dfs_sz(j);
            sz[u] += sz[j];
            if (sz[j] > sz[g[u][0]])
                swap(j, g[u][0]);
        }
    }

    void dfs_hld(int u){
        dfn[u] = ++ts;
        rnk[dfn[u]] = u;
        for (auto j : g[u]){
            top[j] = (j == g[u][0] ? top[u] : j);
            dfs_hld(j);
        }
        out[u] = ts;
    }

    int lca(int u, int v){
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v){
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    bool in_subtree(int u, int v){
        return dfn[v] <= dfn[u] && dfn[u] <= out[v];
    }

    int jump(int u, int k) {
        if (dep[u] < k){
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d){
            u = fa[top[u]];
        }
        return rnk[dfn[u] - dep[u] + d];
    }

    int rooted_lca(int a, int b, int c){
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }

    template<typename Q>
    void modify_path(int u, int v, const Q &q, bool edge = false){
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            q(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        q(dfn[u] + edge, dfn[v]);
    }

    template<typename Q>
    void modify_subtree(int u, const Q &q){
        q(dfn[u], out[u]);
    }

    vector<array<int, 2> > query_path(int u, int v){
        vector<array<int, 2> > ans;
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            ans.push_back({dfn[top[u]], dfn[u]});
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        ans.push_back({dfn[u], dfn[v]});
        return ans;
    }
};