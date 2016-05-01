double eps = 1e-12;

double add(double a, double b) {
    if (abs(a+b) < eps * (abs(a)+abs(b))) return 0;
    return a+b;
}

bool equal(double a, double b) {
    return add(a, -b) == 0;
}

struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {}
    P operator+(P p) const {return P(add(x, p.x), add(y, p.y));}
    P operator-(P p) const {return P(add(x, -p.x), add(y, -p.y));}
    P operator*(double d) const {return P(x*d, y*d);}
    double dot(P p) const {return add(x*p.x, y*p.y);} // 内積
    double det(P p) const {return add(x*p.y, -y*p.x);} // 外積
    double dist(P p) const {return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));} // 距離
    void normalize() {double d = sqrt(x*x+y*y); x /= d; y /= d;} // 正規化
    bool operator<(const P& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
    bool operator==(const P& rhs) const {
        return equal(x, rhs.x) && equal(y, rhs.y);
    }
};

// 線分p1-p2上に点qがあるかを判定する
bool on_seg(P p1, P p2, P q) {
    return (p1-q).det(p2-q) == 0 && (p1-q).dot(p2-q) <= 0;
}

// 直線p1-p2と直線q1-q2が平行かどうかの判定
bool parallel(P p1, P p2, P q1, P q2) {
    P a = p2-p1;
    P b = q2-q1;
    return a.det(b) == 0;
}

// 直線p1-p2と直線q1-q2が平行な場合の,2つの直線の距離
double dist(P p1, P p2, P q1, P q2) {
    P p = p2-p1;
    p = P(-p.y, p.x);
    p.normalize();
    return abs(p.dot(p1-q1));
}

// 直線p1-p2と直線q1-q2の交点
P intersection(P p1, P p2, P q1, P q2) {
    return p1+(p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
}

// 点 P が三角形の内部に存在するか
bool inTri(P p, P a, P b, P c) {
    P ab = b-a;
    P bc = c-b;
    P ca = a-c;
    P ap = p-a;
    P bp = p-b;
    P cp = p-c;
    double c1 = ab.det(bp);
    double c2 = bc.det(cp);
    double c3 = ca.det(ap);
    if (c1 > 0 && c2 > 0 && c3 > 0) return true;
    if (c1 < 0 && c2 < 0 && c3 < 0) return true;
    return false;
}

// 三角形の符号付き面積
double area(P p, P q, P r) {
    return (q-p).det(r-p)/2;
}

// 凸包
vector<P> convex_hull(vector<P> ps) {
    int n = ps.size();
    sort(ps.begin(), ps.end());
    int k = 0;         // 凸包の頂点数
    vector<P> qs(n*2); // 構築中の凸包
    // 下側凸包の作成
    for (int i = 0; i < n; i++) {
        while (k > 1 && (qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    // 上側凸包の作成
    for (int i = n-2, t = k; i >= 0; i--) {
        while (k > t && (qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k-1);
    return qs;
}

// ps からなる凸多角形の面積
double convex_area(vector<P> ps) {
    ps = convex_hull(ps);
    int n = ps.size();
    if (n <= 2) return 0;
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += ps[i].det(ps[(i+1)%n]);
    }
    return ans/2;
}
