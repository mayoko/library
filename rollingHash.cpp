std::random_device rnd;
const ull mul[2] = {10000 + (rnd()%10000), 10000 + (rnd()%10000)};
const ull mod[2] = {1000000007, 1000000009};

class RollingHash {
public:
    RollingHash() {}
    template<class T>
    RollingHash(const T& s) {
        init(s);
    }
    template<class T>
    void init(const T& s) {
        n = s.size();
        for (int i = 0; i < 2; i++) {
            pow[i].resize(n+1);
            h[i].resize(n+1);
            pow[i][0] = 1; h[i][0] = 0;
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                pow[i][j+1] = (mul[i]*pow[i][j]) % mod[i];
                h[i][j+1] = (s[j] + h[i][j]*mul[i]) % mod[i];
            }
        }
    }
    inline pair<ull, ull> hash(int i) const {return make_pair(h[0][i], h[1][i]);}
    // [l, r)
    inline pair<ull, ull> hash(int l, int r) const {
        ull p0 = (h[0][r] - (h[0][l]*pow[0][r-l]%mod[0]) + mod[0]) % mod[0];
        ull p1 = (h[1][r] - (h[1][l]*pow[1][r-l]%mod[1]) + mod[1]) % mod[1];
        return make_pair(p0, p1);
    }
private:
    int n;
    vector<ull> pow[2], h[2];
};
