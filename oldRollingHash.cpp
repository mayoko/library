struct RollingHash {
    static const ll mul0=10009,mul1=10007;
    static const ll add0=1000010007, add1=1003333331;
    string s; int l;
    vector<ll> hash_,pmo_;
    void init(string s) {
        this->s=s; l=s.size();
        hash_.resize(l+1); pmo_.resize(l+1);
        hash_[0]=0; pmo_[0]=1;
        for (int i = 0; i < l; i++) pmo_[i+1]=pmo_[i]*mul0;
        for (int i = 0; i < l; i++) hash_[i+1]=(hash_[i]*mul0+add0+s[i]);
    }
    ll hash(int l,int r) { // s[l..r)
        return hash_[r]-hash_[l]*pmo_[r-l];
    }
};

