struct ArticulationPoints {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> tin, low;
    set<int> articulations;

    ArticulationPoints(int n) : n(n), adj(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children = 0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p != -1)
                    articulations.insert(v);
                ++children;
            }
        }
        if (p == -1 && children > 1)
            articulations.insert(v);
    }

    void find_cutpoints() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        articulations.clear();
        for (int i = 0; i < n; ++i)
            if (!visited[i])
                dfs(i);
    }
};
