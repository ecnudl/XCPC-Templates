Polygon rotcaliper(Polygon &a) {
    double ans = LONG_LONG_MAX;
    Polygon ansp;
    for (int i = 0, j = 1, l = -1, r = -1; i < (int) a.p.size(); i++) {
        while (((a.p[a.nxt(j)] - a.p[i]) ^ (a.p[a.nxt(j)] - a.p[a.nxt(i)]))
               > ((a.p[j] - a.p[i]) ^ (a.p[j] - a.p[a.nxt(i)])))
            j = a.nxt(j);
        if (l == -1) l = i, r = j;
        Point v(a.p[a.nxt(i)] - a.p[i]);
        v = Point(-v.y, v.x);
        while (v.toleft(a.p[a.nxt(l)] - a.p[l]) <= 0) l = a.nxt(l);
        while (v.toleft(a.p[a.nxt(r)] - a.p[r]) >= 0) r = a.nxt(r);
        Line li(a.p[i], a.p[a.nxt(i)] - a.p[i]), lj(a.p[j], a.p[i] - a.p[a.nxt(i)]);
        Line ll(a.p[l], v), lr(a.p[r], v);
        vector<Point> t = {li.inter(ll), ll.inter(lj), lj.inter(lr), lr.inter(li)};
        Polygon pl(t);
        double s = pl.S();
        if (s < ans) ans = s, ansp = pl;
    }
    return ansp;
}