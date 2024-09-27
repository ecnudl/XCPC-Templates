const int N = 5e5 + 10;
int tree[N][26];
int tag[N],idx = 0;
struct Trie{
    void add(char *s)
    {
        int p = 0;
        int len = (int)strlen(s);
        for(int i = 0;i < len;i++) {
            int c = s[i] - 'a';
            if(!tree[p][c]) {
                tree[p][c] = ++idx;
            }
            p = tree[p][c];
        }
        tag[idx] = 1;
    }
    int find(char *s)
    {
        int len = (int)strlen(s);
        int p = 0;
        for(int i = 0;i < len;i++)
        {
            int c = s[i] - 'a';
            if(!tree[p][c]) return 0;
            p = tree[p][c];
        }
        return tag[p]++;
    }
};
//01Trie树
//！son数组应该开N * 30（否则RE）
struct Trie {
    void insert(int x)
    {
        int p = 0;
        for (int i = 30; i >= 0; i -- )
        {
            int &s = son[p][x >> i & 1];
            if (!s) s = ++ idx;
            p = s;
        }
    }

    int search(int x)
    {
        int p = 0, res = 0;
        for (int i = 30; i >= 0; i -- )
        {
            int s = x >> i & 1;
            if (son[p][!s])
            {
                res += 1 << i;
                p = son[p][!s];
            }
            else p = son[p][s];
        }
        return res;
    }
};