#include <bits/stdc++.h>

using i64 = long long;

struct Z_function {
    /*
    Z 函数
    z[i] 表示 s[i:] 与 s 的最长公共前缀长度
    Z_function z_str(str);
    */
    std::string p; // 模式串
    std::vector<int> z; // 失配数组

    explicit Z_function(const std::string &pat) {
        p = pat;
        z.assign(p.size(), 0);
        for (int i = 1, l = 0, r = 0; i < (int)p.size(); i++) {
            if (i <= r) {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < (int)p.size() && p[z[i]] == p[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > r) {
                l = i, r = i + z[i] - 1;
            }
        }
    }

    static std::vector<int> calc_z(const std::string &s) {
        int n = (int)s.size();
        std::vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < (int)s.size(); i++) {
            if (i <= r) {
                z[i] = std::min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > r) {
                l = i, r = i + z[i] - 1;
            }
        }
        return z;
    }

    std::vector<int> findAll(const std::string &text) {
        // 在 text 中查找所有 p 的出现
        std::vector<int> res;
        if (p.empty()) {
            return res;
        }

        std::string s = p;
        s.push_back('#');
        s += text;
        auto zz = calc_z(s);
        int m = (int)p.size();
        for (int i = m + 1; i < (int)s.size(); i++) {
            if (zz[i] >= m) {
                res.push_back(i - (m + 1));
            }
        }
        return res;
    }

    int findFirst(const std::string &text) {
        if (p.empty()) {
            return -1;
        }

        std::string s = p;
        s.push_back('#');
        s += text;
        auto zz = calc_z(s);
        int m = (int)p.size();
        for (int i = m + 1; i < (int)s.size(); i++) {
            if (zz[i] >= m) {
                return i - (m + 1);
            }
        }
        return -1;
    }

    int findCount(const std::string &text) {
        if (p.empty()) {
            return 0;
        }

        std::string s = p;
        s.push_back('#');
        s += text;
        auto zz = calc_z(s);
        int m = (int)p.size(), cnt = 0;
        for (int i = m + 1; i < (int)s.size(); i++) {
            if (zz[i] >= m) {
                cnt++;
            }
        }
        return cnt;
    }

    std::vector<int> borders() {
        std::vector<int> res;
        int n = (int)p.size();
        for (int i = 1; i < n; i++) {
            if (i + z[i] == n) {
                res.push_back(z[i]);
            }
        }
        std::sort(res.begin(), res.end());
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string a, b;
    std::cin >> a >> b;

    Z_function zb(b);
    int nb = b.size();
    i64 ans1 = 0;
    for (int i = 0; i < nb; i++) {
        if (i == 0) {
            ans1 ^= (nb + 1);
            continue;
        }
        ans1 ^= (i + 1) * 1ll * (zb.z[i] + 1);
    }

    std::string ab = b + "#" + a;
    Z_function zab(ab);
    int nab = ab.size();
    i64 ans2 = 0;
    for (int i = 1; i <= (int)a.size(); i++) {
        ans2 ^= i * 1ll * (zab.z[i + nb] + 1);
    }

    std::cout << ans1 << '\n' << ans2 << '\n';
    return 0;
}
