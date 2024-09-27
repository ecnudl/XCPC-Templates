//Tarjan得出的id序列是拓扑序的倒序， 可以用来拓扑序dp
const int N = 5e5 + 6;
int dfn[N], low[N], st[N], id[N];
int timestamp, ssc_cnt, n, m;
stack<int> stk;
VVI e(N), ssc(N);

void tarjan(int x) {
    dfn[x] = low[x] = ++timestamp;
    stk.push(x);
    st[x] = true;
    for(auto y : e[x]) {
        if(!dfn[y]) tarjan(y);
        if(st[y]) low[x] = min(low[y], low[x]);
    }
    if(dfn[x] == low[x]) {
        ++ssc_cnt;
        int y;
        do {
            y = stk.top();
            stk.pop();
            st[y] = false;
            id[y] = ssc_cnt;
            ssc[ssc_cnt].pb(y);
        }while(x != y);
    }
}

//封装版：
struct SCC{
    vector<vector<int> > g, scc;
    vector<int> dfn, low, stk, id;
    vector<bool> ins;
    int ts, n;

    SCC(const vector<vector<int> > &g) : g(g){
        n = (int)g.size();
        dfn.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, -1);
        ins.assign(n, false);
        stk.reserve(n);
        ts = 0;
        build();
    }

    void tarjan(int u){
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        ins[u] = 1;
        for(auto j : g[u]){
            if (!dfn[j]){
                tarjan(j);
                low[u] = min(low[u], low[j]);
            }
            else if (ins[j]) low[u] = min(low[u], dfn[j]);
        }
        if (dfn[u] == low[u]){
            int scc_cnt = scc.size();
            scc.push_back({});
            int y;
            do{
                y = stk.back();
                stk.pop_back();
                id[y] = scc_cnt;
                ins[y] = 0;
                scc.back().push_back(y);
            }while(y != u);
        }
    }

    void build(){
        for(int i = 0; i < n; i++){
            if (!dfn[i]){
                tarjan(i);
            }
        }
    }
};
//无向图强连通分量，用于找割边
const int N = 100010, M = 200010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];//每条边是不是桥
int d[N];//度数

void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;

    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])//j未遍历过
        {
            tarjan(j, i);//dfs(j)
            low[u] = min(low[u], low[j]);//用j更新u
            if (dfn[u] < low[j])//j到不了u
                is_bridge[i] = is_bridge[i ^ 1] = true;
        }
        else if (i != (from ^ 1))
            low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

void init() {
    top = dcc_cnt = timestamp = 0;
    for(int i = 0;i <= n;i++) h[i] = -1, dfn[i] = low[i] = id[i];
    for(int i = 0;i < idx;i++) e[i] = ne[i] = 0, is_bridge[i] = false;
    idx = 0;
}