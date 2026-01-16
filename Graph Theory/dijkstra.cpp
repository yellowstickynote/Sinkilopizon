const int INF = 1e18;

void dijkstra(int s, int n, const vector<vector<pair<int, int>>>& adj, 
              vector<int>& dist, vector<int>& par, vector<int>& cnt) {
    dist.assign(n, INF);
    par.assign(n, -1);
    cnt.assign(n, 0);

    dist[s] = 0;
    cnt[s] = 1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (d + w < dist[v]) {
                dist[v] = d + w;
                par[v] = u;
                cnt[v] = cnt[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % mod;
            }
        }
    }
}

/*
USAGE GUIDE:
------------------------------------------------------------------
Parameters:
  s    : Source node (0-based index)
  n    : Total number of nodes
  adj  : Adjacency list where adj[u] = {{v, weight}, ...}
  dist : Vector reference to store shortest distances (will be resized)
  par  : Vector reference to store parents (for path reconstruction)
  cnt  : Vector reference to store number of shortest paths modulo 'mod'

Returns:
  Void. The results are stored in dist, par, and cnt.

Output Details:
  dist[i] : Shortest distance from s to i. (INF if unreachable)
  par[i]  : The node preceding i in the shortest path. (-1 if unreachable or s)
  cnt[i]  : Number of shortest paths from s to i % mod.

Assumptions:
  - 'mod' is defined globally.
  - 'int' handles standard overflow (e.g., #define int long long).
  - Graph weights are non-negative.
------------------------------------------------------------------
*/
