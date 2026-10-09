struct DSU {
    std::vector<int> parent, size;
    DSU(int n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) std::swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct Kruskal {
    int n;
    long long mst_weight = 0;
    std::vector<Edge> mst_edges;
    bool is_connected = false;

    Kruskal(int n, std::vector<Edge>& edges) : n(n) {
        std::sort(edges.begin(), edges.end());
        DSU dsu(n);
        for (const auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                mst_weight += edge.w;
                mst_edges.push_back(edge);
                if ((int)mst_edges.size() == n - 1) break;
            }
        }
        is_connected = (n == 0) || ((int)mst_edges.size() == n - 1);
    }
};
