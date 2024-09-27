struct Node {
    Node *ch[2];
    int val, rank;
    int rep_cnt;
    int siz;

    Node(int val) : val(val), rep_cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        rank = rand();
    }

    void upd_siz() {
        siz = rep_cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
    }
};

namespace Treap {
    Node *root;

    const static int NIL = 2147483647;  // 用于表示查询的值不存在

    enum rot_type { LF = 1, RT = 0 };

    int q_prev_tmp = 0, q_nex_tmp = 0;

    void _rotate(Node *&cur, rot_type dir) {  // 0为右旋，1为左旋
        Node *tmp = cur->ch[dir];
        cur->ch[dir] = tmp->ch[!dir];
        tmp->ch[!dir] = cur;
        cur->upd_siz(), tmp->upd_siz();
        cur = tmp;
    }

    void _ins(Node *&cur, int val) {
        if (cur == nullptr) {
            cur = new Node(val);
            return;
        } else if (val == cur->val) {
            cur->rep_cnt++;
            cur->siz++;
        } else if (val < cur->val) {
            _ins(cur->ch[0], val);
            if (cur->ch[0]->rank < cur->rank) {
                _rotate(cur, RT);
            }
            cur->upd_siz();
        } else {
            _ins(cur->ch[1], val);
            if (cur->ch[1]->rank < cur->rank) {
                _rotate(cur, LF);
            }
            cur->upd_siz();
        }
    }

    void _del(Node *&cur, int val) {
        if (val > cur->val) {
            _del(cur->ch[1], val);
            cur->upd_siz();
        } else if (val < cur->val) {
            _del(cur->ch[0], val);
            cur->upd_siz();
        } else {
            if (cur->rep_cnt > 1) {
                cur->rep_cnt--, cur->siz--;
                return;
            }
            uint8_t state = 0;
            state |= (cur->ch[0] != nullptr);
            state |= ((cur->ch[1] != nullptr) << 1);
            // 00都无，01有左无右，10，无左有右，11都有
            Node *tmp = cur;
            switch (state) {
                case 0:
                    delete cur;
                    cur = nullptr;
                    break;
                case 1:  // 有左无右
                    cur = tmp->ch[0];
                    delete tmp;
                    break;
                case 2:  // 有右无左
                    cur = tmp->ch[1];
                    delete tmp;
                    break;
                case 3:
                    rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
                    _rotate(cur, dir);
                    _del(cur->ch[!dir], val);
                    cur->upd_siz();
                    break;
            }
        }
    }

    int _query_rank(Node *cur, int val) {        //返回真正的rank，如果要求比这个数小的数字有几个记得减1
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (val == cur->val)
            return less_siz + 1;
        else if (val < cur->val) {
            if (cur->ch[0] != nullptr)
                return _query_rank(cur->ch[0], val);
            else
                return 1;
        } else {
            if (cur->ch[1] != nullptr)
                return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
            else
                return cur->siz + 1;
        }
    }

    int _query_val(Node *cur, int rank) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        if (rank <= less_siz)
            return _query_val(cur->ch[0], rank);
        else if (rank <= less_siz + cur->rep_cnt)
            return cur->val;
        else
            return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
    }

    int _query_prev(Node *cur, int val) {
        if (val <= cur->val) {
            if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
        } else {
            q_prev_tmp = cur->val;
            if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
            return q_prev_tmp;
        }
        return -NIL;
    }

    int _query_nex(Node *cur, int val) {
        if (val >= cur->val) {
            if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
        } else {
            q_nex_tmp = cur->val;
            if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
            return q_nex_tmp;
        }
        return NIL;
    }
}

//非指针版本，不具有更强的封装性，但是在面对大数据时更优而且更短
const int maxn = 2e6 + 10;

struct node {
    int a, b;

    node(int a_ = 0, int b_ = 0) {
        a = a_;
        b = b_;
    }
};

int key[maxn], wei[maxn], siz[maxn], son[maxn][2];
int n, m, cnt, ans, seed = 1, root, last;

int rand1() { return seed *= 19260817; }

inline void pushup(int u) { siz[u] = siz[son[u][0]] + siz[son[u][1]] + 1; }

node split(int u, int k) {
    if (!u) return node(0, 0);
    if (key[u] < k) {
        node t = split(son[u][1], k);
        son[u][1] = t.a;
        pushup(u);
        return node(u, t.b);
    } else {
        node t = split(son[u][0], k);
        son[u][0] = t.b;
        pushup(u);
        return node(t.a, u);
    }
}

int merge(int u, int v) {
    if (!u || !v) return u + v;
    if (wei[u] < wei[v]) {
        son[u][1] = merge(son[u][1], v);
        pushup(u);
        return u;
    } else {
        son[v][0] = merge(u, son[v][0]);
        pushup(v);
        return v;
    }
}

void insert(int k) {
    key[++cnt] = k;
    wei[cnt] = rand1();
    siz[cnt] = 1;
    node t = split(root, k);
    root = merge(merge(t.a, cnt), t.b);
}

void eraser(int k) {
    node x, y;
    x = split(root, k);
    y = split(x.b, k + 1);
    y.a = merge(son[y.a][0], son[y.a][1]);
    root = merge(x.a, merge(y.a, y.b));
}

int query_rank(int k) {
    int re;
    node t = split(root, k);
    re = siz[t.a] + 1;
    root = merge(t.a, t.b);
    return re;
}

int query_val(int k) {
    int pos = root;
    while (pos) {
        if (k == siz[son[pos][0]] + 1) return key[pos];
        if (k <= siz[son[pos][0]]) pos = son[pos][0];
        else {
            k -= siz[son[pos][0]] + 1;
            pos = son[pos][1];
        }
    }
}

int lst(int k) { return query_val(query_rank(k) - 1); }

int nxt(int k) { return query_val(query_rank(k + 1)); }