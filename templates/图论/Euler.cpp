vector<int> path
for(int i = 0;i < (int)edge.size();i++) {
	auto [u, v] = edge[i];
    ng[u].push_back({v, i});
    ng[v].push_back({u, i});
}
function<void(int)> dfs_euler = [&] (int x) {
		while(!ng[x].empty()) {
		auto [y, id] = ng[x].back();
		ng[x].pop_back();
		if(used[id]) continue;
		used[id] = 1;
		dfs_euler(y);
	}
	path.push_back(x);
};
dfs_euler(1);