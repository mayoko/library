// 0-based Binary Indexed Tree
// 数え上げ用
constexpr int mod = 1e9+7;
template<typename T> struct BIT {
    int max;
    vector<T> bit;
    BIT(int max) : max(max) {bit.resize(max+1);}
    // [0, i)
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            (s += bit[i]) %= mod;
            i ^= i&-i;
        }
        return s;
    }
    // 0-basedな座標iに値xを追加する
    void add(int i, T x) {
        ++i;
        while (i <= max) {
            (bit[i] += x) %= mod;
            i += i&-i;
        }
    }
    // [a, b)
    T sum(int a, int b) {
        return sum(b)-sum(a);
    }
    // sum(0, i) >= wとなる最小のiを求める 存在しなければmaxを返す
    int lb(T w) {
        if (w <= 0) return 0;
        int k = 1;
        while (k <= max) k <<= 1;
        int i = 0;
        for (; k > 0; k >>= 1) if (i+k <= max && bit[i+k] < w) {
            w -= bit[i+k];
            i += k;
        }
        return i+1;
    }
};
