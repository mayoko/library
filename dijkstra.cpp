struct edge {
    int v;
    ll w;
    edge() {}
    edge(int v, ll w) : v(v), w(w) {};
};

vector<ll> dijkstra(int n, vector<vector<edge> >& G, int s) {
    vector<ll> d(n, LLONG_MAX/10); d[s] = 0;
    priority_queue<pair<ll, int> > que;
    que.push(make_pair(0ll, s));
    while (!que.empty()) {
        auto p = que.top(); que.pop();
        int u = p.second;
        ll dist = -p.first;
        if (dist > d[u]) continue;
        for (edge e : G[u]) {
            if (d[e.v] > d[u]+e.w) {
                d[e.v] = d[u] + e.w;
                que.push(make_pair(-d[e.v], e.v));
            }
        }
    }
    return d;
}
