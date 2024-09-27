auto p = seg.findFirst(d, n, [&] (auto v) {
     return v.mx >= i;
};
//线段树二分的时候搭配这个食用
template<class Info>
struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(int n_, vector<T> init_) {
        init(n_, init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(n_, vector<Info>(n_ + 2, v_));
    }
    template<class T>
    void init(int n_, vector<T> init_) {
        n = n_;
        info.assign((4 << __lg(n)) + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            update(p);
        };
        build(1, 1, n);
    }
    void update(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        assert(x >= l && x <= r);
        if (l == r) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x <= m) modify(2 * p, l, m, x, v);
        else modify(2 * p + 1, m + 1, r, x, v);
        update(p);
    }
    void modify(int x, const Info &v) {
        modify(1, 1, n, x, v);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        assert(ql >= l && qr <= r);
        if (l == ql && r == qr) return info[p];
        int m = (l + r) / 2;
        if (qr <= m) return query(2 * p, l, m, ql, qr);
        else if (ql > m) return query(2 * p + 1, m + 1, r, ql, qr);
        return query(2 * p, l, m, ql, m) + query(2 * p + 1, m + 1, r, m + 1, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 1, n, ql, qr);
    }
    template<class F>
    int findFirst(int p, int l, int r, int ql, int qr, F pred) {
        assert(ql >= l && qr <= r);
        if (!pred(info[p])) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        if (qr <= m) return findFirst(2 * p, l, m, ql, qr, pred);
        else if (m < ql) return findFirst(2 * p + 1, m + 1, r, ql, qr, pred);
        int pos = findFirst(2 * p, l, m, ql, m, pred);
        if (pos == -1) return findFirst(2 * p + 1, m + 1, r, m + 1, qr, pred);
        return pos;
    }
    template<class F>
    int findFirst(int ql, int qr, F pred) {
        return findFirst(1, 1, n, ql, qr, pred);
    }
};

struct Info {
    int mx = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    return c;
}