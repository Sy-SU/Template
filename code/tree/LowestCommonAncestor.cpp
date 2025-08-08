#include <bits/stdc++.h>

using i64 = long long;

struct HLD {
    /*
    使用树链剖分求 LCA, HLD tree(edge, 1) -> 初始化
    tree.lca(u, v) -> 求 u, v 的最近公共祖先
    */
    const std::vector<std::vector<int>> &edge;

    std::vector<int> fa, dep, son, sz, top;

    HLD(const std::vector<std::vector<int>> &edge_, int root = 1) : edge(edge_) {
        int n = (int)edge.size() - 1;
        fa.assign(n + 1, 0), dep.assign(n + 1, 0), son.assign(n + 1, 0), sz.assign(n + 1, 0), top.assign(n + 1, 0);

        dfs1(root, 0);
        dfs2(root, root);
    }

    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                std::swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

private:
    void dfs1(int u, int f) {
        fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, son[u] = 0;
        for (auto v : edge[u]) {
            if (v == f) {
                continue;
            }
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v]) son[u] = v;
        }
    }

    void dfs2(int u, int t) {
        top[u] = t;
        if (son[u] == 0) {
            return;
        }
        dfs2(son[u], t);
        for (auto v : edge[u]) {
            if (v == fa[u] || v == son[u]) {
                continue;
            }
            dfs2(v, v);
        }
    }
};

void solve() {
	int n;
	std::cin >> n;

	std::vector<std::vector<int>> edge(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;

		edge[u].push_back(v), edge[v].push_back(u);
	}

    HLD tree(edge, 1); // 使用邻接表和指定的根节点初始化 tree

    std::cout << tree.lca(1, 2) << '\n';

    // lca(u, v)	
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	std::cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}