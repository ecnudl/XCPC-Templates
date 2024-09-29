//s是base0, 返回是base1
//返回的ans数组是用#隔开后的数组，长度为2 * n + 1
VI Manacher(string &s) {
    string tmp{};
    for(auto it : s) {
        tmp += '#';
        tmp += it;
    }
    tmp += '#';
    int n = sz(tmp);
    VI d(n), ans(n + 1);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int j = l + r - i, dj = j >= 0 ? d[j] : 0;
        d[i] = max(min(dj, j - l + 1), 0ll);
        if (j - dj < l) {
            while (i - d[i] >= 0 && i + d[i] < n && tmp[i - d[i]] == tmp[i + d[i]])
                d[i]++;
            l = i - d[i] + 1, r = i + d[i] - 1;
        }
    }
    for(int i = 0;i < n;i++) ans[i + 1] = d[i];
    return ans;
}
//搭配使用判断(l, r)是否回文
string s; cin >> s;
auto it = Manacher(s);
s = ' ' + s;
auto check = [&] (int l, int r) {
    int L = r - l + 1;
    if(L & 1) {
        int md = (l + r) >> 1;
        int val = it[md * 2] / 2;
        if(val >= r - md + 1) return true;
        else return false;
    }
    else {
        int md = (l + r) >> 1;
        int val = (it[md * 2 + 1] - 1) / 2;
        if(val >= L / 2) return true;
        else return false;
    }
};