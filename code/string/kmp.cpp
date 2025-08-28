#include <bits/stdc++.h>

using i64 = long long;

struct KMP {
    /*
    KMP kmp(str); // 使用模式串初始化
    auto kmp.findAll(text) -> std::vector<int>; // 在 text 中找 所有 p 出现的位置
    */
    std::string p; // 模式串
    std::vector<int> pi; // 失配数组

    explicit KMP(const std::string &pat) {
        p = pat;
        pi.assign(p.size(), 0);
        for (int i = 1; i < (int)p.size(); i++) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) {
                j = pi[j - 1];
            }
            if (p[i] == p[j]) {
                j++;
            }
            pi[i] = j;
        }
    }

    std::vector<int> findAll(const std::string &text) {
        // 在 text 中找 所有 p 出现的位置
        std::vector<int> res;
        if (p.empty()) {
            return res;
        }

        int j = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j > 0 && text[i] != p[j]) {
                j = pi[j - 1];
            }
            if (text[i] == p[j]) {
                j++;
            }
            if (j == (int)p.size()) {
                res.push_back(i - (int)p.size() + 1);
                j = pi[j - 1]; 
            }
        }
        return res;
    }

    int findFirst(const std::string &text) {
        // 在 text 中找 p 第一次出现的位置
        if (p.empty()) {
            return -1;
        }

        int j = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j > 0 && text[i] != p[j]) {
                j = pi[j - 1];
            }
            if (text[i] == p[j]) {
                j++;
            }
            if (j == (int)p.size()) {
                return i - (int)p.size() + 1;
            }
        }
        return -1;
    }

    int findCount(const std::string &text) {
        // 在 text 中找 p 出现的次数
        if (p.empty()) {
            return 0;
        }

        int j = 0, res = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j > 0 && text[i] != p[j]) {
                j = pi[j - 1];
            }
            if (text[i] == p[j]) {
                j++;
            }
            if (j == (int)p.size()) {
                res++;
                j = pi[j - 1];
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string t, p;
    std::cin >> t >> p;

    KMP kmp(p);
    auto res = kmp.findAll(t);

    for (auto i : res) {
        std::cout << i << '\n';
    }

    for (auto l : kmp.pi) {
        std::cout << l << " ";
    }
    std::cout << '\n';

    return 0;
}
