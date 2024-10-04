#include <bits/stdc++.h>

using ll = long long;
using namespace std;
#define endl '\n'
const int N = 2e5 + 10, P = 131, mod1 = 1e9 + 9;
int n, m;
int p1[N], sum1[N];
int b[N];

void init() {  // 预处理
    p1[0] = 1;
    sum1[0] = 1;
    for (int i = 1; i < N; i++) {
        p1[i] = 1LL * p1[i - 1] * P % mod1;
        sum1[i] = sum1[i - 1] + p1[i] % mod1;
        sum1[i] %= mod1;
    }
}

struct Node {
    ll hash1, maxn, lazy;
    int l, r;
} a[N * 4];

void pushdown(int id) {  // 更新子节点
    a[id << 1].lazy += a[id].lazy, a[id << 1 | 1].lazy += a[id].lazy;
    a[id << 1].maxn += a[id].lazy, a[id << 1 | 1].maxn += a[id].lazy;
    a[id << 1].hash1 = (a[id << 1].hash1 + (a[id].lazy * sum1[a[id << 1].r - a[id << 1].l] % mod1)) % mod1;
    a[id << 1 | 1].hash1 =
            (a[id << 1 | 1].hash1 + (a[id].lazy * sum1[a[id << 1 | 1].r - a[id << 1 | 1].l]) % mod1) % mod1;
    a[id].lazy = 0;
}

void pushup(Node &s1, Node &s2, Node &s3) {  // 更新父节点
    s3.l = s1.l, s3.r = s2.r;
    s3.maxn = max(s1.maxn, s2.maxn);
    s3.lazy = 0;
    s3.hash1 = ((1LL * s1.hash1 * p1[s2.r - s2.l + 1] % mod1) + s2.hash1) % mod1;
}

void pushup(int id) {
    pushup(a[id << 1], a[id << 1 | 1], a[id]);
}

void build(int id, int l, int r) {
    a[id].l = l, a[id].r = r;
    if (l == r) {
        a[id].hash1 = b[l];
        a[id].maxn = b[l];
        a[id].lazy = 0;
        return;
    } else {
        int mid = (l + r) >> 1;
        build(id << 1, l, mid), build(id << 1 | 1, mid + 1, r);
        pushup(id);
    }
}
/*
单点修改
void modify(int id, int x, int k) {
    if (a[id].l == a[id].r) {
        a[id].hash1 = k;
        return;
    }
    int mid = (a[id].l + a[id].r) >> 1;
    if (x <= mid) modify(id << 1,  x, k);
    else modify(id << 1 | 1, x, k);
    pushup(id);
}
*/
void modify(int id, int l, int r, int k) {  // 区间修改
    if (a[id].l >= l && a[id].r <= r) {
        a[id].lazy += k, a[id].maxn += k;
        a[id].hash1 = a[id].hash1 + sum1[a[id].r - a[id].l] * k % mod1;
        return;
    } else {
        pushdown(id);
        int mid = (a[id].l + a[id].r) >> 1;
        if (r <= mid) {
            modify(id << 1, l, r, k);
        } else if (l > mid) {
            modify(id << 1 | 1, l, r, k);
        } else {
            modify(id << 1, l, r, k);
            modify(id << 1 | 1, l, r, k);
        }
        pushup(id);
    }
}

Node query(int u, int l, int r) {
    if (a[u].l >= l && a[u].r <= r) {
        return a[u];
    } else {
        pushdown(u);
        int mid = (a[u].l + a[u].r) >> 1;
        if (r <= mid) {
            return query(u << 1, l, r);
        } else if (l > mid) {
            return query(u << 1 | 1, l, r);
        } else {
            Node s1 = query(u << 1, l, r);
            Node s2 = query(u << 1 | 1, l, r);
            Node s3;
            pushup(s1, s2, s3);
            return s3;
        }
    }
}

bool check(int l1, int l2, int len) {
    int r1 = l1 + len - 1;
    int r2 = l2 + len - 1;
    Node s1 = query(1, l1, r1);
    Node s2 = query(1, l2, r2);
    if(s1.hash1 == s2.hash1) return true;
    return false;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    cin >> n >> m;
    string s; cin >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        b[i] = s[i] - 'a' + 1;
    }
    build(1, 1, n);
    ll op;
    while (m--) {
        cin >> op;
        if (op == 1) {
            int x; char c;
            cin >> x >> c;
            modify(1, x, x, c - s[x]);
            s[x] = c;
        } else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            if(r1 - l1 != r2 - l2) {
                cout << "NO" << endl;
                continue;
            }
            int L = 1, R = r1 - l1 + 1, p = 0;
            while(L <= R) {
                int mid = (L + R) >> 1;
                if(check(l1, l2, mid)) {
                    p = mid;
                    L = mid + 1;
                }
                else R = mid - 1;
            }
            l1 = l1 + p + 1, l2 = l2 + p + 1;
            if(l1 > r1) {
                cout << "YES" << endl;
                continue;
            }
            int la = r1 - l1 + 1;
            if(check(l1, l2, la)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}