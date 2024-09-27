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