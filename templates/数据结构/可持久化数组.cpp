#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long
using ll = long long;
constexpr int maxn = 2e6 + 10;

array<int, maxn> a, root;
int top, n, m;

struct Info {
    int l, r, val;
} tree[maxn * 20];

int clone(int node) {
    top++;
    tree[top] = tree[node];//全部信息都传到新节点
    return top;
}

int build (int node, int l, int r) {
    node = ++top;
    if (l == r) {
        tree[node].val = a[l];
        return top;
    }
    int mid = (l + r) >> 1;
    tree[node].l = build(tree[node].l, l, mid);
    tree[node].r = build(tree[node].r, mid + 1, r);
    return node;
}

int update(int node, int l, int r, int x, int val) {
    node = clone(node);    //更新就要新建节点
    if (l == r) {
        tree[node].val = val;
    } else {
        int mid = (l + r) >> 1;
        if (x <= mid)
            tree[node].l = update(tree[node].l, l, mid, x, val);    //访问左子树
        else
            tree[node].r = update(tree[node].r, mid + 1, r, x, val);    //访问右子树
    }
    return node;
}

int query(int node, int l, int r, int x) {
    if (l == r) {
        return tree[node].val;
    } else {
        int mid = (l + r) >> 1;
        if (x <= mid)
            return query(tree[node].l, l, mid, x);    //访问左子树
        else
            return query(tree[node].r, mid + 1, r, x);    //访问右子树
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    root[0] = build(0, 1, n);    //root[i]为i版本的根编号，刚开始编号为0
    int rt, mode, x, y;
    for (int i = 1; i <= m; i++) {
        cin >> rt >> mode >> x;
        if (mode == 1) {
            cin >> y;
            root[i] = update(root[rt], 1, n, x, y);    //保存版本
        } else {
            cout << query(root[rt], 1, n, x) << endl;    //输出
            root[i] = root[rt];                    //新建版本
        }
    }
}