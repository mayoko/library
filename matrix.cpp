/* かっこ良く書いたつもりだけどめっちゃ遅いので今のところ使わないほうが良いです 
 * 今のところは2x2行列はmat2x2.cppを,一般的な行列演算はmat.cppを使いましょう
 * いつかtemplateで高速化とかできたらまた使うかもしれません(テストにはyukicoder No.147が良いかと)
 */
template<int R, int C, ll mod>
class Mat {
public:
    Mat() : mat(R, vector<ll>(C)) {}
    Mat<R, C, mod>& operator=(const Mat<R, C, mod> rhs) {return rhs;}

    vector<ll>& operator[](int r) {return mat[r];}
    const vector<ll> operator[](int r) const {return mat[r];}

    Mat<R, C, mod>& operator+=(const Mat<R, C, mod> rhs) {
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
            mat[i][j] += rhs.mat[i][j];
            if (mat[i][j] >= mod) mat[i][j] %= mod;
        }
        return (*this);
    }
    Mat<R, C, mod>& operator-=(const Mat<R, C, mod> rhs) {
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
            mat[i][j] -= rhs.mat[i][j];
            mat[i][j] %= mod;
            if (mat[i][j] < 0) mat[i][j] += mod;
        }
        return (*this);
    }
    const Mat<R, C, mod> operator+(const Mat<R, C, mod> rhs) const {
        Mat<R, C, mod> ret = (*this);
        ret += rhs;
        return ret;
    }
    const Mat<R, C, mod> operator-(const Mat<R, C, mod> rhs) const {
        Mat<R, C, mod> ret = (*this);
        ret -= rhs;
        return ret;
    }
    const Mat<R, R, mod> operator*(const Mat<C, R, mod> rhs) const {
        Mat<R, R, mod> ret;
        for (int i = 0; i < R; i++) {
            for (int k = 0; k < C; k++) {
                for (int j = 0; j < R; k++) {
                    ret[i][j] += (*this)[i][k] * rhs[k][j];
                    if (ret[i][j] >= mod) ret[i][j] %= mod;
                }
            }
        }
        return ret;
    }

    const Mat<R, R, mod> pow(ll N) const {
        Mat<R, R, mod> a = (*this);
        Mat<R, R, mod> ret;
        for (int i = 0; i < R; i++) E[i][i] = 1;
        if (N == 0) {
            return ret;
        }
        if (N == 1) {
            return (*this);
        }
        for (int i = 0; N>0; i++) {
            if ((N>>i)&1) {
                ret = ret*a;
            }
            a = a*a;
        }
        return ret;
    }

    void print() const {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << mat[i][j] << "\t";
            }
            cout << endl;
        }
    }
private:
    vector<vector<ll> > mat;
};

typedef Mat<2, 2, MOD> Mat2x2;
