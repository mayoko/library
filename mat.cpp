typedef long long number;
typedef vector<number> vec;
typedef vector<vec> matrix;

const ll MOD = 1e9+7;

// O( n )
matrix identity(int n) {
    matrix A(n, vec(n));
    for (int i = 0; i < n; ++i) A[i][i] = 1;
    return A;
}
// O( n^3 )
matrix mul(const matrix &A, const matrix &B) {
    matrix C(A.size(), vec(B[0].size()));
    for (int i = 0; i < (int)C.size(); ++i)
        for (int j = 0; j < (int)C[i].size(); ++j)
            for (int k = 0; k < (int)A[i].size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] %= MOD;
            }
    return C;
}
// O( n^3 log e )
matrix pow(const matrix &A, ll e) {
    if (e == 0) return identity(A.size());
    if (e == 1) return A;
    if (e % 2 == 0) {
        matrix tmp = pow(A, e/2);
        return mul(tmp, tmp);
    } else {
        matrix tmp = pow(A, e-1);
        return mul(A, tmp);
    }
}
// O(n)
number tr(const matrix &A) {
    number ans = 0;
    for (int i = 0; i < (int)A.size(); ++i)
        ans += A[i][i];
    return ans;
}
// O( n )
number inner_product(const vec &a, const vec &b) {
    number ans = 0;
    for (int i = 0; i < (int)a.size(); ++i)
        ans += a[i] * b[i];
    return ans;
}
// O( n^2 )
vec mul(const matrix &A, const vec &x) {
    vec y(A.size());
    for (int i = 0; i < (int)A.size(); ++i)
        for (int j = 0; j < (int)A[0].size(); ++j)
            (y[i] += (A[i][j] * x[j] % MOD)) %= MOD;
    return y;
}

ll mod_pow(ll x, ll p, ll MOD) {
    ll a = 1;
    while (p) {
        if (p%2) a = a*x%MOD;
        x = x*x%MOD;
        p/=2;
    }
    return a;
}

// mod_inverse
ll mod_inverse(ll a, ll m) {
    return mod_pow(a, MOD-2, m);
}

// long long 専用 行列式を求める関数
number det(matrix A, const ll MOD) {
    const int n = A.size();
    assert(n == (int)A[0].size());
    ll ans = 1;
    for (int i = 0; i < n; i++) {
        int pivot = -1;
        for (int j = i; j < n; j++) if (A[j][i]) {
            pivot = j;
            break;
        }
        if (pivot == -1) return 0;
        if (i!=pivot) {
            swap(A[i], A[pivot]);
            ans *= -1;
        }
        ll inv = mod_inverse(A[i][i], MOD);
        for (int j = i+1; j < n; j++) {
            ll c = A[j][i]*inv % MOD;
            for (int k = i; k < n; k++) {
                A[j][k] = (A[j][k] - c*A[i][k])%MOD;
            }
        }
        (ans *= A[i][i]) %= MOD;
    }
    if (ans < 0) ans += MOD;
    return ans;
}
