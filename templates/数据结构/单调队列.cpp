const int N = 1e6 + 10;
int a[N],n,k;
deque<int> q;
void getmin() {
    for(int i = 1;i < k;i++) {
        while(!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
    }
    for(int i = k;i <= n;i++) {
        while(!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        while(q.front() <= i - k) q.pop_front();
        cout << a[q.front()] << " ";
    }
}

void getmax() {
    q.clear();
    for(int i = 1;i < k;i++) {
        while(!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
    }
    for(int i = k;i <= n;i++) {
        while(!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        while(q.front() <= i - k) q.pop_front();
        cout << a[q.front()] << " ";
    }
}