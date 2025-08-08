// 快速幂

#include <bits/stdc++.h>

using i64 = long long;

i64 qpow(i64 a, i64 b, int mod) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // example
    i64 a = 2, b = 10, mod = 1e9 + 7;
    std::cout << qpow(a, b, mod) << '\n';

    return 0;
}