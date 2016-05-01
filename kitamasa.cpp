typedef vector<ll> vec;
typedef vector<vec> matrix;

const ll MOD = 1e9+7;

matrix mul(const matrix& A, const matrix& B) {
    int n = A.size();
    int m = B[0].size();
    int k = A[0].size();
    matrix ret(n, vec(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                (ret[i][j] += A[i][l] * B[l][j]) %= MOD;
            }
        }
    }
    return ret;
}

// kitamasa専用でおねがいします
matrix kitamasaMul(const matrix& A, const matrix& B) {
    int n = A.size();
    assert(n == 1);
    int m = B[0].size();
    matrix ret(n, vec(m));
    ret[0][0] = A[0][m-1]*B[m-1][0] % MOD;
    for (int i = 1; i < m; i++) {
        ret[0][i] = (A[0][i-1] + A[0][m-1]*B[m-1][i]) % MOD;
    }
    return ret;
}

// Aのm乗を求める
// Aの形は一番下だけ任意の整数で良くて残りの行はA[i][i+1]のみ1
matrix kitamasa(const matrix& A, ll m) {
    int n = A.size();
    matrix B = A;
    matrix u(1, vec(n));
    u[0][0] = 1;
    matrix a(1, vec(n));
    while (m) {
        if (m&1) {
            u = mul(u, B);
        }
        for (int i = 0; i < n; i++) a[0][i] = B[0][i];
        a = mul(a, B);
        for (int i = 0; i < n; i++) B[0][i] = a[0][i];
        for (int i = 1; i < n; i++) {
            a = kitamasaMul(a, A);
            for (int j = 0; j < n; j++) {
                B[i][j] = a[0][j];
            }
        }
        m /= 2;
    }
    matrix ret(n, vec(n));
    for (int i = 0; i < n; i++) ret[0][i] = u[0][i];
    for (int i = 1; i < n; i++) {
        u = kitamasaMul(u, A);
        for (int j = 0; j < n; j++) {
            ret[i][j] = u[0][j];
        }
    }
    return ret;
}

