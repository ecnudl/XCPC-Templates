//法一:
const int N = 2e6 + 10;
char s[N];
int ne[N];
void solve() {
    cin >> (s + 1);
    int len = (int) strlen(s + 1);
    s[len + 1] = '#';
    for(int i = len,j = 2;i;i--) {
        s[len + j++] = s[i];
    }
    len = len + len + 1;
    ne[1] = 0;
    for(int i = 2,j = 0;i <= len;i++) {
        while(j && s[j + 1] != s[i]) j = ne[j];
        if(s[i] == s[j + 1]) j++;
        ne[i] = j;
    }
}
//法二:
char s[M], p[N];
void solve()
{
    cin >> n >> p + 1 >> m >> s + 1;

    for (int i = 2, j = 0; i <= n; i ++ )
    {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++ ;
        ne[i] = j;
    }

    for (int i = 1, j = 0; i <= m; i ++ )
    {
        while (j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j ++ ;
        if (j == n)
        {
            printf("%d ", i - n);
            j = ne[j];
        }
    }
}

//
vector<int> KMP(string &s) {
    int n = (int) s.size() - 1;
    vector<int> ne(n + 1);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }
    return ne;
}