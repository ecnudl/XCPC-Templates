//区间加 乘 求和
const int mod = 1e9 + 7;
struct Info{
    int mx;
    int sz;
};

struct node {
    int mul = 1, add = 0;
};

using Tag = node;

Info operator+(const Info &a, const Info &b){
    return {(a.mx + b.mx) % mod, a.sz + b.sz};
}

Tag operator + (const Tag &t1,const Tag &t2) {
    return {(t1.mul * t2.mul) % mod,(t1.add * t2.mul + t2.add) % mod};
}

void apply(Info &x, Tag &a, Tag f){
    x.mx = (x.mx * f.mul + x.sz * f.add) % mod;
    a = a + f;
}

//涉及取模的话query函数要修改一下
Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        auto ans = query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
        ans.mx %= mod;
        return ans;
}

//区间最值以及区间最值个数
struct Info{
    int mx = INF;
    int cnt = 0;
};

using Tag = int;

Info operator+(const Info &a, const Info &b){
    int mx = min(a.mx, b.mx);
    int cnt = 0;
    if(a.mx == mx) cnt += a.cnt;
    if(b.mx == mx) cnt += b.cnt;
    return {mx, cnt};
}

//单点修改， 区间修改，最大值查询：
struct Info{
    LL mx = -INF;
};

using Tag = LL;

Info operator+(const Info &a, const Info &b){
    return {max(a.mx, b.mx)};
}

void apply(Info &x, Tag &a, Tag f){
    x.mx += f;
    a += f;
}

template<class Info, class Tag>
struct LazySegmentTree{
    int n;
    vector<Info> info;
    vector<Tag> tag;

    LazySegmentTree() {}

    LazySegmentTree(int n, Info _init = Info()){
        init(vector<Info>(n, _init));
    }

    LazySegmentTree(const vector<Info> &_init){
        init(_init);
    }

    void init(const vector<Info> &_init){
        n = (int)_init.size();
        info.assign((n << 2) + 1, Info());
        tag.assign((n << 2) + 1, Tag());
        function<void(int, int, int)> build = [&](int p, int l, int r){
            if (l == r){
                info[p] = _init[l - 1];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply(int p, const Tag &v){
        ::apply(info[p], tag[p], v);
    }

    void push(int p){
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v){
        if (l == r){
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x <= m){
            modify(2 * p, l, m, x, v);
        }
        else{
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }

    Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
    }

    Info query(int l, int r){
        return query(1, 1, n, l, r);
    }

    void modify(int p, int l, int r, int x, int y, const Tag &v){
        if (l > y || r < x){
            return;
        }
        if (l >= x && r <= y){
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        modify(2 * p, l, m, x, y, v);
        modify(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void modify(int l, int r, const Tag &v){
        return modify(1, 1, n, l, r, v);
    }
};
//不带修改
struct Info{
    LL mx = -INF;
};

Info operator+(const Info &a, const Info &b){
    return {max(a.mx, b.mx)};
}
template<class Info>
struct SegmentTree{
    int n;
    vector<Info> info;
 
    SegmentTree() {}
 
    SegmentTree(int n, Info _init = Info()){
        init(vector<Info>(n, _init));
    }
 
    SegmentTree(const vector<Info> &_init){
        init(_init);
    }
 
    void init(const vector<Info> &_init){
        n = (int)_init.size();
        info.assign((n << 2) + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r){
            if (l == r){
                info[p] = _init[l - 1];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
 
    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }
 
    void modify(int p, int l, int r, int x, const Info &v){
        if (l == r){
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x <= m){
            modify(2 * p, l, m, x, v);
        } 
        else{
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
 
    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }
 
    Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
    }
 
    Info query(int l, int r){
        return query(1, 1, n, l, r);
    }
};

//下面展示线段树区间赋值，区间翻转和区间求和操作，打tag时要注意逻辑顺序，其余的操作结合也可以类比这种思维
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
int n;
const int N = 5e5 + 10;
struct que {
    int ty, l, r;
} a[N];
struct node {
    int sum;
    int l, r;
}seg[N << 2];
int tag1[N << 2], tag2[N << 2];
vector<int> vx;

void pushup(int u) {
    seg[u].sum = seg[u * 2].sum + seg[u * 2 + 1].sum;
    seg[u].l = seg[u * 2].l;
    seg[u].r = seg[u * 2 + 1].r;
}

void pushdown(int u) {
    if(tag1[u]) {
        seg[u * 2].sum = (seg[u * 2].r - seg[u * 2].l + 1) - seg[u * 2].sum;
        seg[u * 2 + 1].sum = (seg[u * 2 + 1].r - seg[u * 2 + 1].l + 1) - seg[u * 2 + 1].sum;
        if(tag2[u * 2] != -1) tag2[u * 2] ^= 1;
        else tag1[u * 2] ^= 1;
        if(tag2[u * 2 + 1] != -1) tag2[u * 2 + 1] ^= 1;
        else tag1[u * 2 + 1] ^= 1;
        tag1[u] = 0;
    }
    if(tag2[u] != -1) {
        seg[u * 2].sum = (seg[u * 2].r - seg[u * 2].l + 1) * tag2[u];
        seg[u * 2 + 1].sum = (seg[u * 2 + 1].r - seg[u * 2 + 1].l + 1) * tag2[u];
        tag2[u * 2] = tag2[u * 2 + 1] = tag2[u];
        tag1[u * 2] = tag1[u * 2 + 1] = 0;
        tag2[u] = -1;
    }
}

void build(int u, int l, int r) {
    seg[u].l = l;
    seg[u].r = r;
    if(l == r) {
        seg[u].sum = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(u * 2, l, mid);
    build(u * 2 + 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int ql, int qr, int k) {
    if(r < ql || l > qr) return;
    if(l >= ql && r <= qr) {
        if(k <= 1) {
            tag2[u] = k;
            tag1[u] = 0;
            seg[u].sum = (seg[u].r - seg[u].l + 1) * k;
        }
        else {
            if(tag2[u] != -1) {
                tag2[u] ^= 1;
            }
            else {
                tag1[u] ^= 1;
            }
            seg[u].sum = (seg[u].r - seg[u].l + 1) - seg[u].sum;
        }
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(u);
    modify(u * 2, l, mid, ql, qr, k);
    modify(u * 2 + 1, mid + 1, r, ql, qr, k);
    pushup(u);
}

int query(int u, int l, int r) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    pushdown(u);
    if(seg[u * 2].sum < mid - l + 1) return query(u * 2, l, mid);
    return query(u * 2 + 1, mid + 1, r);
}

void solve() {
    memset(tag2, -1, sizeof tag2);
    cin >> n;
    vx.push_back(1);
    for(int i = 1;i <= n;i++) {
        cin >> a[i].ty >> a[i].l >> a[i].r;
        vx.push_back(a[i].l);
        vx.push_back(a[i].r);
        vx.push_back(a[i].r + 1);
    }
    int tmp = 1e18 + 1;
    vx.push_back(tmp);
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    int M = (int)vx.size();
//    int M = 10;
    auto calc = [&] (int x) {
        return (int) (lower_bound(vx.begin(), vx.end(), x) - vx.begin() + 1);
    };
    build(1, 1, M);
    for(int i = 1;i <= n;i++) {
        auto [ty, l, r] = a[i];
        l = calc(l);
        r = calc(r);
        if(ty == 1) {
            modify(1, 1, M, l, r, 1);
        }
        else if(ty == 2) {
            modify(1, 1, M, l, r, 0);
        }
        else {
            modify(1, 1, M, l, r, 2);
        }
        cout << vx[query(1, 1, M) - 1] << endl;
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