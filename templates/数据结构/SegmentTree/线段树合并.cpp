// 例题来源：洛谷P3224
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long

const int N = 1e5 + 5, M = 1e7 + 10;
int fa[N], tot, R[N], P[N];

int find(int x) {
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

struct node {
    int ls, rs, v;
}seg[M];

void pushup(int u) {
    seg[u].v = seg[seg[u].ls].v + seg[seg[u].rs].v;
}

void build(int &u, int l, int r, int x, int k) {
    if(!u) u = ++tot;
    if(l == r) {
        seg[u].v += k;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) build(seg[u].ls, l, mid, x, k);
    else build(seg[u].rs, mid + 1, r, x, k);
    pushup(u);
}

int kth(int u, int l, int r, int k) {
    if(l == r) return seg[u].v >= k ? l : 0;
    int mid = (l + r) >> 1;
    if(seg[seg[u].ls].v >= k) return kth(seg[u].ls, l, mid, k);
    else return kth(seg[u].rs, mid + 1, r, k - seg[seg[u].ls].v);
}

int merge(int u, int v, int l, int r) {
    if(!u || !v) return u + v;
    if(l == r) {
        seg[u].v += seg[v].v;
        return u;
    }
    int mid = (l + r) >> 1;
    seg[u].ls = merge(seg[u].ls, seg[v].ls, l, mid);
    seg[u].rs = merge(seg[u].rs, seg[v].rs, mid + 1, r);
    pushup(u);
    return u;
}

void solve() {
    int n, m, q;
    cin >> n >> m;
    P[0] = -1;
    for(int i = 1;i <= n;i++) fa[i] = i;
    for(int i = 1;i <= n;i++) {
        int x; cin >> x;
        P[x] = i;
        build(R[i], 1, n, x, 1);
    }
    for(int i = 1;i <= m;i++) {
        int x, y;
        cin >> x >> y;
        int fx = find(x), fy = find(y);
        fa[fy] = fx;
        merge(R[fx], R[fy], 1, n);
    }
    cin >> q;
    while(q--) {
        char ty;
        int x, y;
        cin >> ty >> x >> y;
        if(ty == 'Q') {
            int fx = find(x);
            cout << P[kth(R[fx], 1, n, y)] << endl;
        }
        else {
            int fx = find(x), fy = find(y);
            if(fx == fy) continue;
            fa[fy] = fx;
            merge(R[fx], R[fy], 1, n);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
//    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}