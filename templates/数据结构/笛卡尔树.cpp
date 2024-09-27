const int N = 1e6 + 10;
int a[N], l[N], r[N], n;

void build() {
    stack<int> st;
    int root = 0;
    for(int i = 1;i <= n;i++) {
        int last = 0;
        while(!st.empty() && a[st.top()] > a[i]) {
            last = st.top();
            st.pop();
        }
        if(!st.empty()) r[st.top()] = i;
        else root = i;
        l[i] = last;
        st.push(i);
    }
}

void solve() {
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    build();
}