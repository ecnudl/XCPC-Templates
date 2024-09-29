//二分排序求解，复杂度nlogn^2
const ull P = 131;
const int N = 3e5 + 10;
ull h[N], p[N];

void solve() {
    string s; cin >> s;
    int n = (int)s.size();
    s = ' ' + s;
    p[0] = 1;
    for(int i = 1;i <= n;i++) {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i];
    }
    auto count = [&] (int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    };
    auto calc = [&] (int x, int y) {
        int l1 = n - x + 1, l2 = n - y + 1;
        int l = 1, r = min(l1, l2), tmp = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(count(x, x + mid - 1) == count(y, y + mid - 1)) {
                tmp = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return tmp;
    };
    auto cmp = [&] (int x, int y) {
        int len = calc(x, y);
        if(len == min(n - x + 1, n - y + 1)) return x > y;
        else return s[x + len] < s[y + len];
    };
    vector<int> SA(n + 1);
    for(int i = 1;i <= n;i++) SA[i] = i;
    vector<int> height(n + 1);
    sort(SA.begin() + 1, SA.end(), cmp);
    for(int i = 2;i <= n;i++) height[i] = calc(SA[i - 1], SA[i]);
    for(int i = 1;i <= n;i++) cout << SA[i] - 1 << " \n"[i == n];
    for(int i = 1;i <= n;i++) cout << height[i] << " \n"[i == n];
}