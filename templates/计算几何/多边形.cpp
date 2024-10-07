//前置知识,点类,直线类
template<typename T> struct polygon
{
    vector<point<T>> p;

    size_t nxt(const size_t i) const {return i==p.size()-1?0:i+1;}
    size_t pre(const size_t i) const {return i==0?p.size()-1:i-1;}

    //如果返回的first是true代表点在多边形的边上，否则，如果cnt是0的话就在多边形外部，不等于0则在多边形内部，具体数值代表多边形绕着点旋转的逆时针圈数减去顺时针圈数
    pair<bool,int> winding(const point<T> &a) const 
    {
        int cnt=0;
        for (size_t i=0;i<p.size();i++)
        {
            point<T> u=p[i],v=p[nxt(i)];
            if (abs((a-u)^(a-v))<=eps && (a-u)*(a-v)<=eps) return {true,0};
            if (abs(u.y-v.y)<=eps) continue;
            const L uv={u,v-u};
            if (u.y<v.y-eps && uv.toleft(a)<=0) continue;
            if (u.y>v.y+eps && uv.toleft(a)>=0) continue;
            if (u.y<a.y-eps && v.y>=a.y-eps) cnt++;
            if (u.y>=a.y-eps && v.y<a.y-eps) cnt--;
        }
        return {false,cnt};
    }

    double circ() const
    {
        double sum=0;
        for (size_t i=0;i<p.size();i++) sum+=p[i].dis(p[nxt(i)]);
        return sum;
    }

    T area() const  //返回面积*2
    {
        T sum=0;
        for (size_t i=0;i<p.size();i++) sum+=p[i]^p[nxt(i)];
        return abs(sum);
    }
};