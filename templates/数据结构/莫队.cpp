const int N = 5e5 + 6;
int Cnt[N],A[N],cur,sq;
 
void add(int p) {
    if(Cnt[A[p]] == 0) cur++;
    Cnt[A[p]]++;
}
 
void del(int p) {
    Cnt[A[p]]--;
    if(Cnt[A[p]] == 0) cur--;
}
 
struct Info {
    int l,r,x;
    bool operator < (Info &_) const {
        if(l / sq != _.l / sq) return l < _.l;
        if(l / sq & 1) {
            return r < _.r;
        }
        return r > _.r;
    }
};

//对于每一个区间的操作可以是（起初l = 1,r = 0)(base 1)
	while(l > L) add(--l); 
	while(r < R) add(++r);
	while(l < L) del(l++);
	while(r > R) del(r--);
//最后的清空还原：
for(int i = l;i <= r;i++) del(i);笛卡尔树