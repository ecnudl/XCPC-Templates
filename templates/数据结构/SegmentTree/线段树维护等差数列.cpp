#include<bits/stdc++.h>

#define int long long
#define mid (l + r >> 1)
using namespace std;
const int N = 3e5 + 1;
int T[N << 2], b[N << 2], k[N << 2];
int n, m, q, a[N], pos[N];
set<int> S;

int read() {
    int x = 0;
    char c = 0;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c & 15), c = getchar();
    return x;
}

void pushup(int rt) {
    T[rt] = T[rt << 1] + T[rt << 1 | 1];
}

int f(int x, int y, int l) {
    if ((x + y) % 2) return l / 2 * (x + y);
    else return (x + y) / 2 * l;
}

void pushdown(int rt, int l, int r) {
    if (k[rt]) {
        k[rt << 1] = k[rt], b[rt << 1] = b[rt], T[rt << 1] = f(b[rt], b[rt] + (mid - l) * k[rt], mid - l + 1);
        k[rt << 1 | 1] = k[rt], b[rt << 1 | 1] = b[rt] + (mid - l + 1) * k[rt], T[rt << 1 | 1] = f(b[rt << 1 | 1], b[rt] + (r - l) * k[rt], r - mid);
        k[rt] = 0;
    }
}

void build(int rt, int l, int r) {
    if (l == r) {
        if (a[l]) T[rt] = 0;
        else {
            auto it = S.lower_bound(l);
            T[rt] = (*it) - l, it--, T[rt] *= a[*it];
        }
        return;
    }
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void modify(int rt, int l, int r, int s, int t, int x, int y) {
    if (s > t) return;
    if (s == l && r == t) return T[rt] = f(x, x + (r - l) * y, r - l + 1), b[rt] = x, k[rt] = y, void();
    pushdown(rt, l, r);
    if (t <= mid) modify(rt << 1, l, mid, s, t, x, y);
    else if (mid < s) modify(rt << 1 | 1, mid + 1, r, s, t, x, y);
    else {
        modify(rt << 1, l, mid, s, mid, x, y);
        modify(rt << 1 | 1, mid + 1, r, mid + 1, t, x + (mid - s + 1) * y, y);
    }
    pushup(rt);
}

int query(int rt, int l, int r, int s, int t) {
    if (s <= l && r <= t) return T[rt];
    pushdown(rt, l, r);
    if (t <= mid) return query(rt << 1, l, mid, s, t);
    if (mid < s) return query(rt << 1 | 1, mid + 1, r, s, t);
    return query(rt << 1, l, mid, s, t) + query(rt << 1 | 1, mid + 1, r, s, t);
}

signed main() {
    memset(k, 0, sizeof k);
    n = read(), m = read(), q = read();
    for (int i = 0, x; i < m; i++) S.insert(pos[i] = read());
    for (int i = 0; i < m; i++) a[pos[i]] = read();
    build(1, 1, n);
    while (q--) {
        int o = read(), x = read(), y = read();
        if (o == 1) {
            S.insert(x), a[x] = y;
            auto it = S.lower_bound(x), l = it, r = it;
            l--, r++;
            int L = *l, R = *r;
            modify(1, 1, n, L + 1, x - 1, a[L] * (x - L - 1), -a[L]);
            modify(1, 1, n, x + 1, R - 1, a[x] * (R - x - 1), -a[x]);
            modify(1, 1, n, x, x, 0, 0);
        } else printf("%lld\n", query(1, 1, n, x, y));
    }
    return 0;
}