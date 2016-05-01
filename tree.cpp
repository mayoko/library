class Tree {
public:
    Tree(int V, int root) : V(V), root(root) {
        T.resize(V);
        for (int i = 0; i < MAXLOGV; i++) parent[i].resize(V);
        depth.resize(V);
    }
    // uとvをつなぐ
    // lcaを求めることが主目的なので無向グラフとしている
    void unite(int u, int v) {
        T[u].push_back(v);
        T[v].push_back(u);
    }
    // initする
    // コンストラクタだけじゃなくてこれも呼ばないとlcaが求められないぞ
    void init() {
        dfs(root, -1, 0);
        for (int k = 0; k+1 < MAXLOGV; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) parent[k+1][v] = -1;
                else parent[k+1][v] = parent[k][parent[k][v]];
            }
        }
    }
    // uとvのlcaを求める
    int lca(int u, int v) const {
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < MAXLOGV; k++) {
            if ((depth[v] - depth[u])>>k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) return u;
        for (int k = MAXLOGV-1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
    // uとvの距離を求める
    // edgeを定義しないといけない時はこれじゃダメ
    int dist(int u, int v) const {
        int p = lca(u, v);
        return (depth[u]-depth[p]) + (depth[v]-depth[p]);
    }
    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (int next : T[v]) {
            if (next != p) dfs(next, v, d+1);
        }
    }
    static const int MAXLOGV = 25;
    // グラフの隣接リスト表現
    vector<vector<int> > T;
    // 頂点の数
    int V;
    // 根ノードの番号
    int root;

    // 親ノード
    vector<int> parent[MAXLOGV];
    // 根からの深さ
    vector<int> depth;
};
