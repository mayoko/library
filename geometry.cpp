Real eps = 1e-12;

Real add(Real a, Real b) {
    if (abs(a+b) < eps * (abs(a)+abs(b))) return 0;
    return a+b;
}

bool equal(Real a, Real b) {
    return add(a, -b) == 0;
}

struct P {
    Real x, y;
    P() {}
    P(Real x, Real y) : x(x), y(y) {}
    P operator+(P p) const {return P(add(x, p.x), add(y, p.y));}
    P operator-(P p) const {return P(add(x, -p.x), add(y, -p.y));}
    P operator*(Real d) const {return P(x*d, y*d);}
    Real dot(P p) const {return add(x*p.x, y*p.y);} // 内積
    Real det(P p) const {return add(x*p.y, -y*p.x);} // 外積
    Real dist(P p) const {return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));} // 距離
    void normalize() {Real d = sqrt(x*x+y*y); x /= d; y /= d;} // 正規化
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

// 直線p1-p2と直線q1-q2の交点
P intersection(P p1, P p2, P q1, P q2) {
    return p1+(p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
}
inline Real square(Real x) {return x*x;}
// 直線p1-p2と点qの距離
Real dist(P p1, P p2, P q) {
    q = q-p1;
    p2 = p2-p1;
    return sqrt((q.dot(q)*p2.dot(p2) - square(q.dot(p2))) / p2.dot(p2));
}
// 線分p1-p2と点qの距離
Real distSeg(P p1, P p2, P q) {
    Real d = (q-p1).dot(p2-p1) / p2.dist(p1);
    if (d < 0) return q.dist(p1);
    if (d > p2.dist(p1)) return q.dist(p2);
    return dist(p1, p2, q);
}

// 線分p1-p2と線分q1-q2の距離
Real distSeg(P p1, P p2, P q1, P q2) {
    if (p1==p2 && q1==q2) return q1.dist(p1);
    if (p1==p2) return distSeg(q1, q2, p1);
    if (q1==q2) return distSeg(p1, p2, q1);
    if (!parallel(p1, p2, q1, q2)) {
        P r = intersection(p1, p2, q1, q2);
        if (on_seg(p1, p2, r) && on_seg(q1, q2, r)) return 0;
    }
    Real ret = min(distSeg(p1, p2, q1), distSeg(p1, p2, q2));
    ret = min(ret, min(distSeg(q1, q2, p1), distSeg(q1, q2, p2)));
    return ret;
}

// 点 P が三角形の内部に存在するか
bool inTri(P p, P a, P b, P c) {
    P ab = b-a;
    P bc = c-b;
    P ca = a-c;
    P ap = p-a;
    P bp = p-b;
    P cp = p-c;
    Real c1 = ab.det(bp);
    Real c2 = bc.det(cp);
    Real c3 = ca.det(ap);
    if (c1 > 0 && c2 > 0 && c3 > 0) return true;
    if (c1 < 0 && c2 < 0 && c3 < 0) return true;
    return false;
}

// 三角形の符号付き面積
Real area(P p, P q, P r) {
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
Real convex_area(vector<P> ps) {
    ps = convex_hull(ps);
    int n = ps.size();
    if (n <= 2) return 0;
    Real ans = 0;
    for (int i = 0; i < n; i++) {
        ans += ps[i].det(ps[(i+1)%n]);
    }
    return ans/2;
}
