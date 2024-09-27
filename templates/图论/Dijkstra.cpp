//n^2
//适用情况，正权图
int g[N][N];    //为稠密阵所以用邻接矩阵存储
int dist[N];    //用于记录每一个点距离第一个点的距离
bool st[N];     //用于记录该点的最短距离是否已经确定
int n, m;

int Dijkstra() {
    memset(dist, 0x3f, sizeof dist);     //初始化距离  0x3f代表无限大
    dist[1] = 0;  //第一个点到自身的距离为0
    for (int i = 0; i < n; i++) {
        int t = -1;       //t存储当前访问的点

        for (int j = 1; j <= n; j++)   //这里的j代表的是从1号点开始
            if (!st[j] && (t == -1 || dist[t] > dist[j]))         //这里可以看出是在寻找最小值，但是复杂度是n，导致总复杂度是n^2所以会想到后面的用优先队列优化的方案
                t = j;

        st[t] = true;

        for (int j = 1; j <= n; j++)           //依次更新每个点所到相邻的点路径值
            dist[j] = min(dist[j], dist[t] + g[t][j]);
    }

    if (dist[n] == 0x3f3f3f3f) return -1;  //如果第n个点路径为无穷大即不存在最低路径
    return dist[n];
}

//用堆也就是优先队列优化的版本，用stl存图，用cnt数组记录边数量
//nlogn
const int N = 200010;
vector <array<int, 2> > e[N];         //存图
int dist[N], cnt[N], vis[N];
int n;
priority_queue <array<int, 2> , vector<array<int, 2> >, greater<>> heap;

void Dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    heap.push({0, 1});
    while (!heap.empty()) {
        auto [_, x] = heap.top();
        heap.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto [y, w]: e[x]) {
            if (dist[y] == dist[x] + w) cnt[y]++;
            if (dist[y] > dist[x] + w) {
                cnt[y] = 1;
                dist[t] = dist[x] + w;
                heap.push({dist[y], y});
            }
        }
    }
}