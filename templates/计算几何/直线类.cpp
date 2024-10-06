//前置代码: 点类
template<typename T> struct line
{
    point<T> p,v;

    bool operator==(const line &a) const {return v.toleft(a.v)==0 && v.toleft(p-a.p)==0;}
    int toleft(const point<T> &a) const {return v.toleft(a-p);}
    point<T> inter(const line &a) const {return p+v*((a.v^(p-a.p))/(v^a.v));}
    double dis(const point<T> &a) const {return abs(v^(a-p))/v.len();}
    point<T> proj(const point<T> &a) const {return p+v*((v*(a-p))/(v*v));}
    /*bool operator<(const line &a) const
    {
        if (abs(v^a.v)<=eps && v*a.v>=-eps) return toleft(a.p)==-1;
        return argcmp(v,a.v);
    }*/
};