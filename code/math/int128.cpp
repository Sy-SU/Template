#include <bits/stdc++.h>

using i128 = __int128_t;
using u128 = __uint128_t;

inline std::ostream& operator<<(std::ostream& os, i128 x) {
    if (x == 0) return os << '0';
    if (x < 0) { os << '-'; x = -x; }
    char s[64]; int p = 0;
    while (x) { s[p++] = char('0' + x % 10); x /= 10; }
    while (p) os << s[--p];
    return os;
}
inline std::ostream& operator<<(std::ostream& os, u128 x) {
    if (x == 0) return os << '0';
    char s[64]; int p = 0;
    while (x) { s[p++] = char('0' + x % 10); x /= 10; }
    while (p) os << s[--p];
    return os;
}

inline std::istream& operator>>(std::istream& is, i128& x) {
    is >> std::ws;
    bool neg = false;
    int c = is.peek();
    if (c == '+' || c == '-') { neg = (c == '-'); is.get(); }
    if (!std::isdigit(is.peek())) { is.setstate(std::ios::failbit); return is; }
    u128 v = 0;
    while (std::isdigit(is.peek())) v = v * 10 + (is.get() - '0');
    x = neg ? -i128(v) : i128(v);
    return is;
}
inline std::istream& operator>>(std::istream& is, u128& x) {
    is >> std::ws;
    if (!std::isdigit(is.peek())) { is.setstate(std::ios::failbit); return is; }
    x = 0;
    while (std::isdigit(is.peek())) x = x * 10 + (is.get() - '0');
    return is;
}

int main() {
    i128 a, b;
    std::cin >> a >> b;
    std::cout << a / b << '\n';

    return 0;
}