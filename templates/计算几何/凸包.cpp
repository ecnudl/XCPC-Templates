template<typename T> struct convex: polygon<T>
{
    convex operator+(const convex &c) const {         //凸包相加
        const auto &p=this->p;
        vector<point<T>> e1(p.size()),e2(c.p.size()),edge(p.size()+c.p.size()),res;
        res.reserve(p.size()+c.p.size());
        for (size_t i=0;i<p.size();i++) e1[i]=p[i]-p[this->pre(i)];
        for (size_t i=0;i<c.p.size();i++) e2[i]=c.p[i]-c.p[c.pre(i)];
        rotate(e1.begin(),min_element(e1.begin(),e1.end(),argcmp()),e1.end());
        rotate(e2.begin(),min_element(e2.begin(),e2.end(),argcmp()),e2.end());
        merge(e1.begin(),e1.end(),e2.begin(),e2.end(),edge.begin(),argcmp());
        const auto cmp=[](const point<T> &u,const point<T> &v)
        {
            if (abs(u.y-v.y)<=eps) return u.x<v.x-eps; 
            return u.y>v.y+eps;
        };
        const auto i0=min_element(p.begin(),p.end(),cmp),j0=min_element(c.p.begin(),c.p.end(),cmp);
        auto u=*i0+*j0;
        const auto check=[](const vector<point<T>> &res,const point<T> &u)
        {
            const auto back1=res.back(),back2=*prev(res.end(),2);
            return (back1-back2).toleft(u-back1)==0 && (back1-back2)*(u-back1)>=-eps;
        };
        for (const auto &v:edge)
        {
            while (res.size()>1 && check(res,u)) res.pop_back();
            res.push_back(u);
            u=u+v;
        }
        return {res};
    }

    template<typename F> void rotcaliper(const F &func) const       //旋转卡壳,利用合适的func函数可以求出凸包内最近距离
    {
        const auto &p=this->p;
        const auto area=[](const point<T> &u,const point<T> &v,const point<T> &w){return abs((w-u)^(w-v));};
        for (size_t i=0,j=1;i<p.size();i++)
        {
            const auto nxti=this->nxt(i);
            //func(p[i],p[nxti],p[j]);
            while (area(p[this->nxt(j)],p[i],p[nxti])>=area(p[j],p[i],p[nxti]))
            {
                j=this->nxt(j);
                //func(p[i],p[nxti],p[j]);
            }
            func(p[i],p[nxti],p[j]);
        }
    }
    //const auto func=[&](const Point &u,const Point &v,const Point &w){ans=max(ans,Line{u,v-u}.dis(w));};

    T diameter2() const  //返回凸包直径的平法
    {
        const auto &p=this->p;
        if (p.size()==1) return 0;
        if (p.size()==2) return p[0].dis2(p[1]);
        T ans=0;
        auto func=[&](const point<T> &u,const point<T> &v,const point<T> &w){ans=max({ans,w.dis2(u),w.dis2(v)});};
        rotcaliper(func);
        return ans;
    }

    vector<T> sum;

    void get_sum()
    {
        const auto &p=this->p;
        vector<T> a(p.size());
        for (size_t i=0;i<p.size();i++) a[i]=p[this->pre(i)]^p[i];
        sum.resize(p.size());
        partial_sum(a.begin(),a.end(),sum.begin());
    }

    T query_sum(const size_t l,const size_t r) const
    {
        const auto &p=this->p;
        if (l<=r) return sum[r]-sum[l]+(p[r]^p[l]);
        return sum[p.size()-1]-sum[l]+sum[r]+(p[r]^p[l]);
    }
    T query_sum() const {return sum.back();}
    
    int is_in(const point<T> &a) const     //log判断点是否在凸包内部
    {
        const auto &p=this->p;
        if (p.size()==1 && a==p[0]) return -1;
        if (p.size()==2 && segment<T>{p[0],p[1]}.is_on(a)) return -1; 
        size_t l=1,r=p.size()-2;
        while (l<=r)
        {
            const auto mid=(l+r)>>1;
            const auto t1=(p[mid]-p[0]).toleft(a-p[0]),t2=(p[mid+1]-p[0]).toleft(a-p[0]);
            if (t1>=0 && t2<=0)
            {
                if (mid==1 && segment<T>{p[0],p[mid]}.is_on(a)) return -1;
                if (mid+1==p.size()-1 && segment<T>{p[0],p[mid+1]}.is_on(a)) return -1;
                if (segment<T>{p[mid],p[mid+1]}.is_on(a)) return -1;
                return (p[mid+1]-p[mid]).toleft(a-p[mid])>0;
            }
            if (t1<0) r=mid-1;
            else l=mid+1;
        }
        return false;
    }

    template<typename F> size_t extreme(const F &dir) const
    {
        const auto &p=this->p;
        const auto check=[&](const size_t i){return dir(p[i]).toleft(p[this->nxt(i)]-p[i])>=0;};
        const auto dir0=dir(p[0]); const auto check0=check(0);
        if (!check0 && check(p.size()-1)) return 0;
        size_t l=0,r=p.size()-1;
        while (l<r)
        {
            const auto mid=(l+r)>>1;
            auto checkm=check(mid);
            if (checkm==check0)
            {
                const auto t=dir0.toleft(p[mid]-p[0]);
                if ((!check0 && t<=0) || (check0 && t<0)) checkm^=1;
            }
            if (checkm) l=mid+1;
            else r=mid;
        }
        return r;
    }

    pair<size_t,size_t> tangent(const point<T> &a) const //!is_in(a)
    {
        const size_t i=extreme([&](const point<T> &u){return u-a;});
        const size_t j=extreme([&](const point<T> &u){return a-u;});
        return {i,j};
    }
};