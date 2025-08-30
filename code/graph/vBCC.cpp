#include <bits/stdc++.h>

using i64 = long long;

struct vBCC {
    /*
    tarjan 求 vBCC，无向图
    bcc_id[i] 表示 i 所在的 BCC 编号
    bcc[i] 表示第 i 个 BCC 的顶点集合
    is_cut[i] 表示 i 是否是割点
    */
    int n, ind, bcc_cnt, root;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, low, is_cut;
    std::vector<std::vector<int>> bcc; // 每个点双的顶点集合, 编号从 0 开始
    std::stack<int> stk;

    vBCC(int n) {
        this->n = n;
        ind = bcc_cnt = 0;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        is_cut.assign(n + 1, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs(int u, int f) {
        dfn[u] = low[u] = ++ind;
        stk.push(u);

        if (u == root && adj[u].empty()) {
            bcc_cnt++;
            bcc.push_back({u});
            stk.pop();
            return;
        }

        int child = 0;
        for (auto v : adj[u]) {
            if (!dfn[v]) {
                child++;
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);

                if (low[v] >= dfn[u]) {
                    if (u != root || child > 1) {
                        is_cut[u] = 1;
                    }
                    bcc_cnt++;
                    std::vector<int> tmp;
                    int z;
                    do {
                        z = stk.top();
                        stk.pop();
                        tmp.push_back(z);
                    } while (z != v);
                    tmp.push_back(u);
                    bcc.push_back(std::move(tmp));
                }
            } else if (v != f && dfn[v] < dfn[u]) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    }

    int tarjan() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                root = i;
                dfs(i, 0);
            }
        }
        return bcc_cnt;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    vBCC graph(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u != v) {
            graph.addEdge(u, v);
        }
    }

    std::cout << graph.tarjan() << '\n';
    
    for (auto bcc : graph.bcc) {
        std::cout << bcc.size() << ' ';
        for (auto u : bcc) {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}