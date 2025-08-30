#include <bits/stdc++.h>

using i64 = long long;

template <class T>
struct Graph {
    /*
    Prim 求最小生成树
    */
    int n;
    std::vector<std::vector<std::pair<int, T>>> adj;

    Graph(int n) {
        this->n = n;
        adj.assign(n + 1, {});
    }

    void addEdge(int u, int v, T w) {
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }

    void addArc(int u, int v, T w) {
        adj[u].emplace_back(v, w);
    }

    std::pair<T, std::vector<int>> prim(int s, int &reached) {
        constexpr T INF = std::numeric_limits<T>::max() / 4;
        std::vector<int> pre(n + 1, -1); // 树上节点的前驱
        std::vector<int> inMST(n + 1);
        std::vector<T> cost(n + 1, INF);

        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

        T minCost = 0;
        reached = 0;

        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (inMST[u]) {
                continue;
            }
            inMST[u] = 1, cost[u] = d, minCost += d, reached++;
            for (auto [v, w] : adj[u]) {
                if (!inMST[v] && cost[v] > w) {
                    cost[v] = w, pre[v] = u;
                    pq.emplace(w, v);
                }
            }
        }
        return {minCost, pre};
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    Graph<i64> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int r = -1;
    auto [ans, _] = g.prim(1, r);

    if (r < n) {
        std::cout << "orz" << '\n';
    } else {
        std::cout << ans << '\n';
    }

    return 0;
}
