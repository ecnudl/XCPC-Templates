//叉积排序,没有精度损失
const double eps = 0;
struct argcmp
{
    bool operator()(const P &a,const P &b) const
    {
        const auto quad=[](const P &a)
        {
            if (a.y<-eps) return 1;
            if (a.y>eps) return 4;
            if (a.x<-eps) return 5;
            if (a.x>eps) return 3;
            return 2;
        };
        const int qa=quad(a),qb=quad(b);
        if (qa!=qb) return qa<qb;
        const auto t=a^b;
        //if (abs(t)<=eps) return a*a<b*b-eps;
        return t>eps;
    }
};