/* 
 * a b
 * c d
 * って感じで行列になっております
 */
struct Matrix2x2 {
    ll a, b, c, d;
    Matrix2x2() {}
    Matrix2x2(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {}
};

/* A*Bという行列計算 */
Matrix2x2 mult(Matrix2x2 A, Matrix2x2 B) {
    Matrix2x2 C;
    C.a = ((A.a * B.a) % MOD + (A.b * B.c) % MOD) % MOD;
    C.b = ((A.a * B.b) % MOD + (A.b * B.d) % MOD) % MOD;
    C.c = ((A.c * B.a) % MOD + (A.d * B.c) % MOD) % MOD;
    C.d = ((A.c * B.b) % MOD + (A.d * B.d) % MOD) % MOD;
    return C;
}

/* A^pという行列のべき乗計算 */
Matrix2x2 expt(Matrix2x2 A, ll p) {
    if (p == 0) {
        Matrix2x2 I;
        I.a = 1; I.b = 0; I.c = 0; I.d = 1;
        return I;
    }
    if (p == 1) {
        return A;
    } else if (p % 2) {
        Matrix2x2 T = expt(A, p-1);
        return mult(A, T);
    } else {
        Matrix2x2 T = expt(A, p/2);
        return mult(T, T);
    }
}
