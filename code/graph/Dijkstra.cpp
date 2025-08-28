#include <bits/stdc++.h>

using i64 = long long;

template <class T>
struct Graph {
    /*
    正权图, dijstra 求最短路
    Graph<i64> g(n);
    g.addEdge(u, v, w); // 无向边
    g.addArc(u, v, w); // 有向边

    std::vector<int> par;
    g.dijkstra(s, &par); // 求最短路, 并记录路径
    */
    int n;
    std::vector<std::vector<std::pair<int, T>>> adj;
    std::vector<T> dist;

    Graph(int n) {
        this->n = n;
        adj.assign(n + 1, {});
        dist.assign(n + 1, -1);
    }

    void addEdge(int u, int v, T w) {
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }

    void addArc(int u, int v, T w) {
        adj[u].emplace_back(v, w);
    }

    void dijkstra(int s, std::vector<int> *par = nullptr) {
        dist.assign(n + 1, -1);
        if (par) {
            par->assign(n + 1, -1);
        }

        using P = std::pair<T, int>;

        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (dist[u] != -1 && d > dist[u]) {
                continue;
            }
            for (auto [v, w] : adj[u]) {
                T nd = d + w;
                if (dist[v] == -1 || nd < dist[v]) {
                    dist[v] = nd;
                    pq.emplace(nd, v);
                    if (par) {
                        (*par)[v] = u;
                    }
                }
            }
        }
    }

    static std::vector<int> get_path(int s, int t, std::vector<int> &par) {
        std::vector<int> path;
        for (int v = t; v != -1; v = par[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());

        return path;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s;
    std::cin >> n >> m >> s;

    Graph<i64> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        g.addArc(u, v, w);
    }

    g.dijkstra(s);

    for (int i = 1; i <= n; i++) {
        std::cout << g.dist[i] << " \n"[i == n];
    }

    return 0;
}
