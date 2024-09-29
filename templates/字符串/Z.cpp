void Z(int n)
{
    z[1] = 0;
    int l = 1,r = 0;
    for(int i = 2;i <= n;i++) {
        if(i > r) {
            z[i] = 0;
        }
        else {
            z[i] = min(z[i - l + 1],r - i + 1);
        }
        while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
        if(i + z[i] - 1 > r) {
            l = i,r = i + z[i] - 1;
        }
    }
}

vector<int> Z(string S) {
    S = ' ' + S;
    int len = (int)S.length();
    vector<int> z(len);
    int L = 1, R = 0;
    for (int i = 2; i < len; i++) {
        if (i > R) z[i] = 0;
        else z[i] = min(z[i - L + 1], R - i + 1);
        while (i + z[i] <= len && S[i + z[i]] == S[z[i] + 1]) z[i]++;
        if (i + z[i] - 1 > R) L = i, R = i + z[i] - 1;
    }
    return z;
}