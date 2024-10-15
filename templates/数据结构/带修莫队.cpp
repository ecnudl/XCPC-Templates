//带修莫队，相比于普通莫队多了一维时间，使用板子的时候排序函数以及莫队的框架不用改，一般只用修改add和del函数。下方给出例题代码，例题内容为求出区间的颜色种类数并且待修改。
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define int long long

int qsize;
struct query {
    long long id, t, l, r;

    bool operator < (const query& b) const {
        if (l / qsize != b.l / qsize) {
            return l / qsize > b.l / qsize;
        } else if (r / qsize != b.r / qsize) {
            return r / qsize > b.r / qsize;
        } else {
            return t > b.t;
        }
    }
} q[150009];

struct op {
    int p, x;
} r[150009];

int a[150009], n, m, c1, c2, ans[150009], cur;
int cnt[1000010];

void add(int x) {
    if(!cnt[x]) {
        cur++;
    }
    cnt[x]++;
}

void del(int x) {
    if(cnt[x] == 1) {
        cur--;
    }
    cnt[x]--;
}

void solve() {
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    qsize = (int)pow(n, 2.0 / 3.0);
    for(int i = 1;i <= m;i++) {
        char c; int x, y;
        cin >> c >> x >> y;
        if(c == 'Q') {
            c1++;
            q[c1].id = c1;
            q[c1].t = c2;
            q[c1].l = x;
            q[c1].r = y;
        }
        else {
            r[++c2].p = x;
            r[c2].x = y;
        }
    }
    sort(q + 1, q + 1 + c1);
    int L = 1, R = 0, last = 0;
    for(int i = 1;i <= c1;i++) {
        auto [id, t, l, rr] = q[i];
        while(L > l) add(a[--L]);
        while(R < rr) add(a[++R]);
        while(L < l) del(a[L++]);
        while(R > rr) del(a[R--]);
        while(last < t) {
            ++last;
            if(r[last].p >= L && r[last].p <= R) {
                del(a[r[last].p]);
                add(r[last].x);
            }
            swap(a[r[last].p], r[last].x);
        }
        while(last > t) {
            if(r[last].p >= L && r[last].p <= R) {
                del(a[r[last].p]);
                add(r[last].x);
            }
            swap(a[r[last].p], r[last].x);
            last--;
        }
        ans[id] = cur;
    }
    for(int i = 1;i <= c1;i++) cout << ans[i] << endl;
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