#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;  // 数据范围
int tot, n, m;
int sum[(maxn << 5) + 10], rt[maxn + 10], ls[(maxn << 5) + 10],
        rs[(maxn << 5) + 10];
int a[maxn + 10], ind[maxn + 10], len;

int getid(const int &val) {  // 离散化
    return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r) {  // 建树
    int root = ++tot;
    if (l == r) return root;
    int mid = l + r >> 1;
    ls[root] = build(l, mid);
    rs[root] = build(mid + 1, r);
    return root;  // 返回该子树的根节点
}

int update(int k, int l, int r, int root) {  // 插入操作
    int dir = ++tot;
    ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
    if (l == r) return dir;
    int mid = l + r >> 1;
    if (k <= mid)
        ls[dir] = update(k, l, mid, ls[dir]);
    else
        rs[dir] = update(k, mid + 1, r, rs[dir]);
    return dir;
}

int query(int u, int v, int l, int r, int k) {  // 查询操作
    int mid = l + r >> 1,
            x = sum[ls[v]] - sum[ls[u]];  // 通过区间减法得到左儿子中所存储的数值个数
    if (l == r) return l;
    if (k <= x)  // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
        return query(ls[u], ls[v], l, mid, k);
    else  // 否则说明在右儿子中
        return query(rs[u], rs[v], mid + 1, r, k - x);
}

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    memcpy(ind, a, sizeof ind);
    sort(ind + 1, ind + n + 1);
    len = unique(ind + 1, ind + n + 1) - ind - 1;
    rt[0] = build(1, len);
    for (int i = 1; i <= n; ++i) rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

void work() {
    while (m--) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]);  // 回答询问
    }
}

int main() {
    init();
    work();
    return 0;
}

//主席树板子题
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

const int N = 3e5 + 10;
int n, m, node, rt[N], val[N << 5], ls[N << 5], rs[N << 5], a[N];

void pushup(int u) {
    val[u] = val[ls[u]] + val[rs[u]];
}

void ins(int &u, int pre, int l, int r, int x) {
    u = ++node;
    val[u] = val[pre];
    ls[u] = ls[pre], rs[u] = rs[pre];
    if(l == r) {
        val[u]++;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) ins(ls[u], ls[pre], l, mid, x);
    else ins(rs[u], rs[pre], mid + 1, r, x);
    pushup(u);
}

int query(int u, int pre, int k, int l, int r) {  //实现了查询区间第k大
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int siz = val[ls[u]] - val[ls[pre]];
    if(siz < k) return query(rs[u], rs[pre], k - siz, mid + 1, r);
    else return query(ls[u], ls[pre], k, l, mid);
}

int check(int u, int pre, int x, int l, int r) { //查询某个数字在区间中出现的次数
    if(l == r) return val[u] - val[pre];
    int mid = (l + r) >> 1;
    if(x <= mid) return check(ls[u], ls[pre], x, l, mid);
    else return check(  rs[u], rs[pre], x, mid + 1, r);
}

void solve() {
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) ins(rt[i], rt[i - 1], 1, n, a[i]);
    while(m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int dis = (r - l + 1) / k + 1, rnk = 1;
        int ans = -1;
        while(rnk <= r - l + 1) {
            int now = query(rt[r], rt[l - 1], rnk, 1, n);
            if(check(rt[r], rt[l - 1], now, 1, n) >= dis) {
                ans = now;
                break;
            }
            rnk += dis;
        }
        cout << ans << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
//    cin >> T;
    while(T--) {
        solve();
    }

    return 0;
}

//查询区间中小于等于某个数的数字之和
void pushup(int u) {
    sum[u] = sum[ls[u]] + sum[rs[u]];
}
 
void modify(int &u, int pre, int l, int r, int pos) {
    u = ++tot;
    sum[u] = sum[pre], ls[u] = ls[pre], rs[u] = rs[pre];
    if(l == r) {
        sum[u] += pos;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) modify(ls[u], ls[pre], l, mid, pos);
    else modify(rs[u], rs[pre], mid + 1, r, pos);
    pushup(u);
}
 
int query(int u, int pre, int l, int r, int pos) {
    if(pos >= r) return sum[u] - sum[pre];
    int mid = (l + r) >> 1;
    return query(ls[u], ls[pre], l, mid, pos) + (pos > mid ? query(rs[u], rs[pre], mid + 1, r, pos) : 0);
}