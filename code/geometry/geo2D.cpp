#include <bits/stdc++.h>

using i64 = long long;

constexpr long double eps = 1e-12;

template<class T>
struct Point {
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}

    template<class U> operator Point<U>() const { return Point<U>(U(x), U(y)); }

    Point& operator+=(const Point& o) {
        x += o.x, y += o.y;
        return *this; 
    }
    
    Point& operator-=(const Point& o) { 
        x -= o.x, y -= o.y; 
        return *this; 
    }

    Point& operator*=(T k) {
        x *= k, y *= k;
        return *this;
    }

    Point& operator/=(T k) {
        x /= k, y /= k;
        return *this;
    }

    friend Point operator+(Point a, const Point& b) { return a += b; }
    friend Point operator-(Point a, const Point& b) { return a -= b; }
    friend Point operator*(Point a, T k) { return a *= k; }
    friend Point operator*(T k, Point a) { return a *= k; }
    friend Point operator/(Point a, T k) { return a /= k; }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    Point<T> norm() const {
        T magnitude = abs(*this);
        return *this / magnitude;
    }
};

template<class T>
T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
T sq(Point<T> a) {
    return dot(a, a);
}

template<class T>
long double abs(Point<T> a) {
    return sqrt((long double)sq(a));
}

template<class T>
T angle_to(const Point<T> &a, const Point<T> &b) {
    T angle_a = std::atan2(a.y, a.x);
    T angle_b = std::atan2(b.y, b.x);

    T angle_diff = angle_b - angle_a;

    if (angle_diff < 0) {
        angle_diff += 2 * M_PI;
    }

    return angle_diff; // 弧度
}

template<class T>
struct Line {
    Point<T> a, b;

    Line(Point<T> a, Point<T> b) : a(a), b(b) {}
};

template<class T>
T distP2L(Point<T> p, Line<T> l) {
    Point<T> p1 = l.a, p2 = l.b;

    T nume = std::abs((p2.x - p1.x) * (p1.y - p.y) - (p1.x - p.x) * (p2.y - p1.y));
    T deno = std::sqrtl((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    
    return nume / deno;
}

// 判断两条直线是否平行
template<class T>
bool is_parallel(const Line<T>& l1, const Line<T>& l2) {
    return std::abs(cross(l1.b - l1.a, l2.b - l2.a)) < eps;
}

// 计算两条直线的交点
template<class T>
Point<T> intersection(const Line<T>& l1, const Line<T>& l2) {
    if (is_parallel(l1, l2)) {
        throw std::runtime_error("The lines are parallel, no intersection.");
    }

    return l1.a + (l1.b - l1.a) * cross(l2.b - l2.a, l1.a - l2.a) / cross(l1.b - l1.a, l2.b - l2.a);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    
    return 0;
}
