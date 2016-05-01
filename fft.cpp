// (畳込みをする際の)使い方
// // 多項式の数の宣言
// fft a(n*2+2), b(n*2+2);
// // 元の関数を構成する
// for (int i = 0; i < n; i++) {
//     int x, y;
//     cin >> x >> y;
//     a.d[i+1].real(x);
//     b.d[i+1].real(y);
// }
// // a, bのフーリエ変換した関数を求める
// a.f();
// b.f();
// // 畳み込みはフーリエ変換の世界では積になる
// for (int i = 0; i < a.n; i++) a.d[i] *= b.d[i];
// // 逆フーリエ変換
// a.f(-1);
// for (int i = 0; i < 2*n; i++) {
//     printf("%.0f\n", a.d[i+1].real()/a.n);
// }

const double PI = acos(-1.0);

struct fft {
    int n, l;
    vector<C> d;
    fft(int mx) {
        for (n = 1, l = 0; n < mx; n<<=1, l++);
        d.resize(n);
    }
    void f(int s = 1) {
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (int k = 0; k < l; k++) {
                if (i&(1<<k)) j |= (1<<(l-1-k));
            }
            if (i < j) swap(d[i], d[j]);
        }
        for (int t = 1; t < n; t <<= 1) {
            C w(cos(PI/t), sin(PI/t)*s);
            for (int i = 0; i < n; i += t<<1) {
                C v(1, 0);
                for (int j = 0; j < t; j++) {
                    C a = d[i+j] + d[i+t+j]*v;
                    C b = d[i+j] - d[i+t+j]*v;
                    d[i+j] = a; d[i+t+j] = b;
                    v *= w;
                }
            }
        }
    }
};
