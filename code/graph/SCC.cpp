#include <bits/stdc++.h>

using i64 = long long;

struct SCC {
    /*
    tarjan 求 SCC，有向图
    scc_id[i] 表示 i 所在的 SCC 编号
    例如：对 scc 缩点之后跑 dp
    SCC scc(n);
    scc.addArc(u, v); ...
    scc.tarjan();

    std::vector<std::vector<int>> dag(scc.scc_cnt + 1);
    for (int u = 1; u <= n; u++) {
        for (auto v : scc.adj[u]) {
            if (scc.scc_id[u] != scc.scc_id[v]) {
                dag[scc.scc_id[u]].push_back(scc.scc_id[v]);
                // scc.scc_id[u] -> scc.scc_id[v]
            }
        }
    }
    */
    int n, ind, scc_cnt;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, low, in_stk, scc_id;
    std::stack<int> stk;

    SCC(int n) {
        this->n = n;
        ind = scc_cnt = 0;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        in_stk.assign(n + 1, 0);
        scc_id.assign(n + 1, 0);
    }

    void addArc(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++ind;
        stk.push(u), in_stk[u] = 1;

        for (auto v : adj[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (in_stk[v]) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            ++scc_cnt;
            while (1) {
                int x = stk.top();
                stk.pop();
                in_stk[x] = 0;
                scc_id[x] = scc_cnt;
                if (x == u) {
                    break;
                }
            }
        }
    }

    int tarjan() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
        return scc_cnt;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    SCC graph(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;

        graph.addArc(u, v);
    }

    graph.tarjan();

    std::vector<std::vector<int>> dag(graph.scc_cnt + 1);
    std::vector<int> in(graph.scc_cnt + 1);
    for (int u = 1; u <= n; u++) {
        for (auto v : graph.adj[u]) {
            if (graph.scc_id[u] != graph.scc_id[v]) {
                dag[graph.scc_id[u]].push_back(graph.scc_id[v]);
                in[graph.scc_id[v]]++;
            }
        }
    }

    std::vector<int> val(graph.scc_cnt + 1);
    for (int i = 1; i <= n; i++) {
        val[graph.scc_id[i]] += a[i];
    }

    std::vector<int> dp(graph.scc_cnt + 1);
    std::queue<int> q;

    for (int i = 1; i <= graph.scc_cnt; i++) {
        if (!in[i]) {
            q.push(i);
            dp[i] = val[i];
        }
    }

    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        for (auto v : dag[now]) {
            dp[v] = std::max(dp[v], dp[now] + val[v]);
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    int ans = *std::max_element(dp.begin() + 1, dp.end());
    std::cout << ans << '\n';
    
    return 0;
}
