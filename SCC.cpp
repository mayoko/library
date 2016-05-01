struct SCC {
    int V;
    vector<vi> G, rG;
    vector<int> vs, used, cmp;
    SCC(const vector<vi>& g) : V(g.size()), G(g), rG(V), used(V), cmp(V) {
        for (int i = 0; i < V; i++) for (int u : G[i]) rG[u].push_back(i);
    }
    void dfs(int v) {
        used[v] = 1;
        for (int u : G[v]) if (!used[u]) dfs(u);
        vs.push_back(v);
    }
    void rdfs(int v, int k) {
        used[v] = 1;
        cmp[v] = k;
        for (int u : rG[v]) if (!used[u]) rdfs(u, k);
    }
    int calc() {
        fill(used.begin(), used.end(), 0);
        vs.clear();
        for (int v = 0; v < V; v++) {
            if (!used[v]) dfs(v);
        }
        fill(used.begin(), used.end(), 0);
        int k = 0;
        for (int i = vs.size()-1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
};
