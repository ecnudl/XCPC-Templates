template<typename T> struct point {
    T x,y;
    bool operator==(const point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    bool operator<(const point &a) const {if (abs(x-a.x)<=eps) return y<a.y-eps; return x<a.x-eps;}
    point operator+(const point &a) const {return {x+a.x,y+a.y};}
    point operator-(const point &a) const {return {x-a.x,y-a.y};}
    point operator-() const {return {-x,-y};}
    point operator*(const T k) const {return {k*x,k*y};}
    point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const point &a) const {return x*a.x+y*a.y;}
    T operator^(const point &a) const {return x*a.y-y*a.x;}
    int toleft(const point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}
    T len2() const {return (*this)*(*this);}
    T dis2(const point &a) const {return (a-(*this)).len2();}
    double len() const {return sqrt(len2());}
    double dis(const point &a) const {return sqrt(dis2(a));}
    double ang(const point &a) const {return acos(max(-1.0,min(1.0,((*this)*a)/(len()*a.len()))));}
    point rot(const double rad) const {return {x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad)};}
};