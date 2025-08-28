#include <bits/stdc++.h>

using i64 = long long;

struct DSU {
    /*
    并查集
    DSU dsu(n);
    */
    int n;
    std::vector<int> fa, sz;

    explicit DSU(int n) {
        fa.assign(n + 1, 0), sz.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            return;
        }
        if (sz[fx] < sz[fy]) {
            std::swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);

    while (m--) {
        int o, x, y;
        std::cin >> o >> x >> y;
        if (o == 1) {
            dsu.merge(x, y);
        } else {
            std::cout << (dsu.same(x, y) ? "Y" : "N") << '\n';
        }
    }

    return 0;
}
