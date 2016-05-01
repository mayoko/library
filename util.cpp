struct Point {
    int y;
    int x;
    Point() {}
    Point(int y, int x) : y(y) , x(x) {}
    bool operator<(const Point& rhs) const {
        if (y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
    bool operator==(const Point& rhs) const {
        return y == rhs.y && x == rhs.x;
    }
};

// xがほとんど整数に近いという条件でxに近い整数を返す
inline int ROUND(double x) {return (int)(x+0.5);}
