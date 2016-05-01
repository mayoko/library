// 遅延評価つきセグメント木
// update: [l, r) の区間を v に変更
// query:  [l, r) の区間の和を求める
struct ST {
    vector<ll> seg, lazy;
    int size;

    ST(int n) {
        size = 1;
        while (size < n) size *= 2;
        seg.resize(size * 2);
        lazy.resize(size * 2, -1);
    }

    void push(int k, int l, int r) {
        if (lazy[k] != -1) {
            seg[k] = lazy[k] * (r - l);
            if (r - l > 1) {
                lazy[k * 2 + 1] = lazy[k];
                lazy[k * 2 + 2] = lazy[k];
            }
            lazy[k] = -1;
        }
    }

    ll merge(ll x, ll y) {
        return x + y;
    }

    void update(int a, int b, ll v, int k, int l, int r) {
        push(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[k] = v;
            push(k, l, r);
        } else {
            update(a, b, v, k * 2 + 1, l, (l + r) / 2);
            update(a, b, v, k * 2 + 2, (l + r) / 2, r);
            seg[k] = merge(seg[k * 2 + 1], seg[k * 2 + 2]);
        }
    }

    void update(int a, int b, ll v) {
        return update(a, b, v, 0, 0, size);
    }

    ll query(int a, int b, int k, int l, int r) {
        push(k, l, r);
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return merge(x, y);
    }

    ll query(int a, int b) {
        return query(a, b, 0, 0, size);
    }
};

// 遅延評価つきセグメント木
// update: [l, r) の区間に値 v を一様に追加する
// query:  [l, r) の区間の和を求める
struct ST {
    vector<ll> seg, lazy;
    int size;

    ST(int n) {
        size = 1;
        while (size < n) size *= 2;
        seg.resize(size * 2);
        lazy.resize(size * 2);
    }

    inline void push(int k, int l, int r) {
        if (lazy[k] != 0) {
            seg[k] += lazy[k] * (r - l);
            if (r - l > 1) {
                lazy[k * 2 + 1] += lazy[k];
                lazy[k * 2 + 2] += lazy[k];
            }
            lazy[k] = 0;
        }
    }

    inline ll merge(ll x, ll y) {
        return x + y;
    }

    void update(int a, int b, ll v, int k, int l, int r) {
        push(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[k] += v;
            push(k, l, r);
        } else {
            update(a, b, v, k * 2 + 1, l, (l + r) / 2);
            update(a, b, v, k * 2 + 2, (l + r) / 2, r);
            seg[k] = merge(seg[k * 2 + 1], seg[k * 2 + 2]);
        }
    }

    void update(int a, int b, ll v) {
        return update(a, b, v, 0, 0, size);
    }

    ll query(int a, int b, int k, int l, int r) {
        push(k, l, r);
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return merge(x, y);
    }

    ll query(int a, int b) {
        return query(a, b, 0, 0, size);
    }
};

// セグメント木(RMQ 対応)
// update: k 番目の値を a に変更
// query: [l, r) の区間の最大値を求める
template<typename T>
struct ST {
    vector<T> seg;
    int size;
    ST(int n) {
        size = 1;
        while (size < n) size *= 2;
        seg.resize(2*size-1, numeric_limits<T>::min());
    }
    inline T merge(T x, T y) {
        return max(x, y);
    }
    void update(int k, T a) {
        k += size-1;
        seg[k] = a;
        while (k > 0) {
            k = (k-1)/2;
            seg[k] = merge(seg[k*2+1], seg[k*2+2]);
        }
    }
    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return numeric_limits<T>::min();
        if (a <= l && r <= b) return seg[k];
        T vl = query(a, b, k*2+1, l, (l+r)/2);
        T vr = query(a, b, k*2+2, (l+r)/2, r);
        return merge(vl, vr);
    }
    T query(int a, int b) {
        return query(a, b, 0, 0, size);
    }
};

