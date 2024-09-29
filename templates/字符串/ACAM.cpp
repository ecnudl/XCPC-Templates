namespace acam {
    queue<int> q;
    int n, pre, root, cnt;
    vector<int> fail(maxn);
    vector<vector<int> >  son(maxn, vector<int> (26));
    vector<vector<int> > tr(maxn);
    vector<int> sum(maxn);
    void init() {
        root = maxn - 1;
    }
    int insert(string &s) {
        pre = root;
        for(auto c : s) {
            if(!son[pre][c - 'a'])
                son[pre][c - 'a'] = ++cnt;
            pre = son[pre][c - 'a'];
        }
        return pre;
    }
    void build() {
        for(int i = 0;i < 26;i++) {
            if(son[root][i]) {
                q.push(son[root][i]);
                fail[son[root][i]] = root;
            }
            else {
                son[root][i] = root;
            }
        }
        while(!q.empty()) {
            pre = q.front(), q.pop();
            for(int i = 0;i < 26;i++) {
                if(son[pre][i]) {
                    fail[son[pre][i]] = son[fail[pre]][i];
                    q.push(son[pre][i]);
                }
                else {
                    son[pre][i] = son[fail[pre]][i];
                }
            }
        }
    }
    void build_fail() {
        for(int i = 1;i <= cnt;i++) {
            tr[fail[i]].pb(i);
        }
    }
    void cal(int x) {
        for(auto y : tr[x]) {
            cal(y);
            sum[x] += sum[y];
        }
    }
}
//
const int N = 2e5 + 10;
int nxt[N][26], fail[N], End[N], sum[N], tot;
vector<int> tr[N];

int ins (const string &s) {
    int p = 0;
    for(auto ch : s) {
        if(!nxt[p][ch - 'a'])
            nxt[p][ch - 'a'] = ++tot;
        p = nxt[p][ch - 'a'];
    }
    return p;
}

void bfs() {
    queue<int> q;
    for(int i = 0;i < 26;i++) {
        if(nxt[0][i]) q.push(nxt[0][i]);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0;i < 26;i++) {
            if(nxt[u][i]) {
                fail[nxt[u][i]] = nxt[fail[u]][i];
                q.push(nxt[u][i]);
            }
            else nxt[u][i] = nxt[fail[u]][i];
        }
    }
}

void build_fail() {
    for(int u = 1;u <= tot;u++) {
        tr[fail[u]].push_back(u);
    }
}