struct Dijkstra {
    static const long long INF = 1e18;
    int n;
    long long MOD = 1e9 + 7; // modulus for shortest-path counting (customize)
    vector<vector<pair<int, int>>> adj; // adj[u] = {{v, weight}, ...}
    vector<long long> dist, cnt;
    vector<int> par;

    Dijkstra(int n) : n(n), adj(n) {}

    void add_edge(int u, int v, int w) { adj[u].push_back({v, w}); }

    void run(int s) {
        dist.assign(n, INF);
        par.assign(n, -1);
        cnt.assign(n, 0);
        dist[s] = 0;
        cnt[s] = 1;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    par[v] = u;
                    cnt[v] = cnt[u];
                    pq.push({dist[v], v});
                } else if (d + w == dist[v]) {
                    cnt[v] = (cnt[v] + cnt[u]) % MOD;
                }
            }
        }
    }
};
