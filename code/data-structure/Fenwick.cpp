#include <bits/stdc++.h>

using i64 = long long;

template <class T>
struct Fenwick {
    /*
    树状数组维护单点加，区间和
    使用 Fenwick<i64> tree(a); 初始化树状数组
    单点加: tree.add(pos, val);
    区间和: tree.sum(l, r)
    */
    int n;
    std::vector<T> tr;

    Fenwick() {
        n = 0;
        tr.assign(n + 1, T());
    }

    explicit Fenwick(const std::vector<T> &a) {
        n = a.size() - 1;
        tr.assign(n + 1, T());
        if (n) {
            for (int i = 1; i <= n; ++i) {
                tr[i] += a[i];
                int j = i + (i & -i);
                if (j <= n) tr[j] += tr[i];
            }
        }
    }

    void add(int pos, const T &val) {
        for (int i = pos; i <= n; i += i & -i) {
            tr[i] += val;
        }
    }

    T prefix(int pos) {
        T res = T();
        for (int i = pos; i; i -= i & -i) {
            res += tr[i];
        }
        return res;
    }

    T sum(int l, int r) {
        if (l > r) {
            return T();
        }
        return prefix(r) - prefix(l - 1);
    }
};

template<class T>
struct DoubleFenwick {
    /*
    树状数组维护区间加，区间和
    使用 DoubleFenwick<i64> tree(a); 初始化树状数组
    区间加: tree.add(l, r, val);
    区间和: tree.sum(l, r)
    */
    int n;
    Fenwick<T> tr1, tr2; // tr1 维护 d[i] 的前缀和, tr2 维护 d[i] * i 的前缀和

    explicit DoubleFenwick(const std::vector<T> &a) {
        n = a.size() - 1;
        std::vector<T> d(n + 1);
        for (int i = 1; i <= n; ++i) {
            d[i] = a[i] - a[i - 1];
        }
        tr1 = Fenwick<T>(d);
        for (int i = 1; i <= n; i++) {
            d[i] = d[i] * i;
        }
        tr2 = Fenwick<T>(d);
    }

    void add(int l, int r, const T &val) {
        if (l > r) {
            return;
        }
        tr1.add(l, val);
        if (r + 1 <= n) {
            tr1.add(r + 1, -val);
        }

        tr2.add(l, val * l);
        if (r + 1 <= n) {
            tr2.add(r + 1, -val * (r + 1));
        }
    }

    T prefix(int pos) {
        return tr1.prefix(pos) * (pos + 1) - tr2.prefix(pos);
    }

    T sum(int l, int r) {
        if (l > r) {
            return T();
        }
        return prefix(r) - prefix(l - 1);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    DoubleFenwick<i64> tree(a);

    while (m--) {
        int o;
        std::cin >> o;

        if (o == 1) {
            int x, y;
            i64 k;
            std::cin >> x >> y >> k;
            tree.add(x, y, k);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << tree.sum(l, r) << '\n';
        }
    }

    return 0;
}
