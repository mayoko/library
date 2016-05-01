long long lcm(long long a, long long b){
    if(a<b) swap(a,b);
    if(b==1) return a;
    return a * (b/__gcd(a,b));
}

long long extgcd(long long a, long long b, long long &x, long long &y){
    long long d=a;
    if(b!=0){
        d = extgcd(b, a%b, y, x);
        y -= (a/b) * x;
    }else{
        x = 1;
        y = 0;
    }
    return d;
}

long long mod_inverse(long long a, long long m){
    long long x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}

// Z % Yi = Xi であるようなZを求める。Garnerのアルゴリズム O(N^2)
long long Chinese_Remainder_Theorem_Garner(vector<long long> x, vector<long long> y){
    int N = x.size();
    bool valid = true;
    //前処理
    //gcd(Yi,Yj) == 1 (i!=j) でなくてはならないので、
    //共通の因数 g = gcd(Yi,Yj) を見つけたら片側に寄せてしまう
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(i == j) continue;
            long long g = __gcd(y[i], y[j]);

            if( x[i]%g != x[j]%g ) valid = false;   //解が存在しない

            if(g != 1){
                y[i] /= g; y[j] /= g;
                long long g_ = __gcd(y[i], g);
                while(g_ != 1){
                    y[i] *= g_;
                    g /= g_;
                    g_ = __gcd(y[i], g);
                }
                y[j] *= g;

                x[i] %= y[i];
                x[j] %= y[j];
            }
        }
    }

    if(!valid){
        cerr << -1 << endl;
        return -1;
    }

    //Garner's algorithm
    vector<long long> z(N);
    for(int i=0; i<N; i++){
        z[i] = x[i];
        for(int j=0; j<i; j++){
            z[i] = mod_inverse(y[j], y[i]) % y[i] * (z[i] - z[j]) % y[i];

            z[i] = (z[i]+y[i])%y[i];
        }
    }

    long long ans = 0;
    long long tmp = 1;
    for(int i=0; i<N; i++){
        ans = (ans + z[i] * tmp)/*%MOD*/;
        tmp = (tmp * y[i])/*%MOD*/;
    }

    return ans;
}
