namespace network
{
    const int maxn = 1e4 + 5, inf = 1e9;
    queue<int> que;
    int src, dst, maxFlow, minCost;
    array<int, maxn> pos, vis, dis, cur;
    array<vector<tuple<int, int, int, int>>, maxn> nxt;

    void addEdge(int u, int v, int w, int x)
    {
        nxt[u].emplace_back(v, w, +x, pos[v]++);
        nxt[v].emplace_back(u, 0, -x, pos[u]++);
        return;
    }

    bool bfs()
    {
        cur.fill(0), dis.fill(inf), vis.fill(0);
        dis[src] = 0, que.emplace(src);
        for (int u; !que.empty(); que.pop())
        {
            vis[u = que.front()] = 0;
            for (auto [v, w, x, k] : nxt[u])
                if (dis[v] > dis[u] + x && w)
                {
                    dis[v] = dis[u] + x;
                    if (!vis[v])
                        que.emplace(v), vis[v] = 1;
                }
        }
        return dis[dst] != inf;
    }

    int dfs(int u, int low)
    {
        if (u == dst || !low)
            return low;
        int use = 0;
        vis[u] = 1;
        for (int& i = cur[u]; i < pos[u]; i++)
        {
            auto [v, w, x, j] = nxt[u][i];
            if (dis[v] == dis[u] + x && !vis[v])
                if (w = dfs(v, min(w, low)); w)
                {
                    get<1>(nxt[u][i]) -= w, low -= w;
                    get<1>(nxt[v][j]) += w, use += w;
                    if (minCost += w * x; !low)
                        break;
                }
        }
        vis[u] = 0;
        return use;
    }

    void dinic()
    {
        while (bfs())
            maxFlow += dfs(src, inf);
        return;
    }

} // namespace network