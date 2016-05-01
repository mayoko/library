constexpr int MOD = 1000000007;
struct MOD_INT{
    int x;
    MOD_INT(const int& x=0) : x((x%MOD+MOD)%MOD){}
    MOD_INT(const ll& x) : x((x%MOD+MOD)%MOD){}
    MOD_INT(const MOD_INT& o): x(o.x){}
    operator int(){return x;}
    MOD_INT pow(int e) {
        MOD_INT res(1), b(*this);
        for (; e >>1; b=b*b) if (e&1) res = res*b;
        return res;
    }
    MOD_INT inv() {return pow(MOD-2);}
    template<class T> MOD_INT operator+(T o){return MOD_INT(x+MOD_INT(o).x);}
    template<class T> MOD_INT operator-(T o){return MOD_INT(x-MOD_INT(o).x);}
    template<class T> MOD_INT operator*(T o){return MOD_INT((ll)x*MOD_INT(o).x);}
    template<class T> MOD_INT operator/(T o){return *this*MOD_INT(o).inv();}
};
#define DEFOP(OP, OPEQ) \
    template<class T> MOD_INT& operator OPEQ(MOD_INT& a, T o){return a=a OP o;}\
    template<class T> MOD_INT operator OP(T a, MOD_INT b){return MOD_INT(a).operator OP(b);}
DEFOP(+, +=); DEFOP(-, -=); DEFOP(*, *=); DEFOP(/, /=);
#undef DEFOP
typedef MOD_INT mi;
