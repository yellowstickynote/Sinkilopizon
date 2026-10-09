struct Prim {
    int n;
    long long mst_weight = 0;
    std::vector<std::pair<int, int>> mst_edges;
    bool is_connected = false;

    Prim(int n, const std::vector<std::vector<std::pair<int, long long>>>& adj, int start_node = 0) : n(n) {
        if (n == 0) { is_connected = true; return; }
        
        std::vector<bool> visited(n, false);
        using Element = std::tuple<long long, int, int>; // {weight, to_node, from_node}
        std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pq;

        visited[start_node] = true;
        for (const auto& [neighbor, weight] : adj[start_node]) {
            pq.push({weight, neighbor, start_node});
        }

        while (!pq.empty() && (int)mst_edges.size() < n - 1) {
            auto [w, u, p] = pq.top();
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            mst_weight += w;
            mst_edges.push_back({p, u});

            for (const auto& [v, weight] : adj[u]) {
                if (!visited[v]) {
                    pq.push({weight, v, u});
                }
            }
        }
        is_connected = (n == 0) || ((int)mst_edges.size() == n - 1);
    }
};
