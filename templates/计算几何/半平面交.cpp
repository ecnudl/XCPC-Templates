vector<L> _halfinter(vector<L> l)
{
    constexpr int LIM=1e9;
    const auto check=[](const L &a,const L &b,const L &c){return a.toleft(b.inter(c))<0;};
    // const auto check=[](const Line &a,const Line &b,const Line &c)   //无精度损失版本，但是大小达到了n^3有可能会爆
    // {
    //     const auto t=b.v^c.v;
    //     const Point x=a.v*t,y=b.p*t+b.v*(c.v^(b.p-c.p))-a.p*t;
    //     return x.toleft(y)<0;
    // };
    l.push_back({{-LIM,0},{0,-1}}); l.push_back({{0,-LIM},{1,0}});
    l.push_back({{LIM,0},{0,1}}); l.push_back({{0,LIM},{-1,0}});
    sort(l.begin(),l.end());
    deque<L> q;
    for (size_t i=0;i<l.size();i++)
    {
        if (i>0 && l[i-1].v.toleft(l[i].v)==0 && l[i-1].v*l[i].v>eps) continue;
        while (q.size()>1 && check(l[i],q.back(),q[q.size()-2])) q.pop_back();
        while (q.size()>1 && check(l[i],q[0],q[1])) q.pop_front();
        q.push_back(l[i]);
    }
    while (q.size()>1 && check(q[0],q.back(),q[q.size()-2])) q.pop_back();
    while (q.size()>1 && check(q.back(),q[0],q[1])) q.pop_front();
    if (q.size()<=2) return vector<L>();
    return vector<L>(q.begin(),q.end());
}

Poly halfinter(const vector<L> &l)        //直接返回多边形或者凸包
{
    const auto lines=_halfinter(l);
    Poly poly; poly.p.resize(lines.size());
    if (lines.empty()) return poly;
    for (size_t i=0;i<lines.size();i++)
    {
        const size_t j=(i==lines.size()-1?0:i+1);
        poly.p[i]=lines[i].inter(lines[j]);
    }
    poly.p.erase(unique(poly.p.begin(),poly.p.end()),poly.p.end());
    if (poly.p.front()==poly.p.back()) poly.p.pop_back();
    return poly;
}