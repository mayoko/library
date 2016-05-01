bool visit(const vector<vi>& g, int v, vector<int>& order, vector<int>& color) {
    color[v] = 1;
    for (int u : g[v]) {
        if (color[u]==2) continue;
        if (color[u]==1) return false;
        if (!visit(g, u, order, color)) return false;
    }
    order.push_back(v); color[v] = 2;
    return true;
}

// トポロジカルソートする
// 返り値が true の時のみ意味を持つ(false の場合は閉路)
bool TopologicalSort(const vector<vi>& g, vector<int>& order) {
    int n = g.size();
    vector<int> color(n);
    for (int u = 0; u < n; u++) if (!color[u] && !visit(g, u, order, color)) return false;
    reverse(order.begin(), order.end());
    return true;
}
