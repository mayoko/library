// example

//int sa[MAXN], lcp[MAXN];
//int invSA[MAXN], perm[MAXN];
//int N;
//int main() {
//    string s;
//    cin >> s;
//    int N = s.size();
//    SA::createSA(s, sa);
//    SA::LCP::createLCP(s, sa, lcp);
//    SA::LCP::initSparseTable(N, lcp);
//    for (int i = 0; i <= N; i++) invSA[sa[i]] = i;
//    cout << "SA" << endl;
//    for (int i = 0; i <= N; i++) {
//        cout << i << "  " << sa[i] << "  " << lcp[i] << endl;
//    }
//    while (1) {
//        int a, b;
//        cin >> a >> b;
//        a = invSA[a], b = invSA[b];
//        cout << SA::LCP::getLCP(a, b) << endl;
//    }
//}

const int MAXN = 100010;
namespace SA {
    int rank[MAXN], tmp[MAXN];
    int n, k;
    bool compare_sa(int i, int j) {
        if (rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = (i+k <= n) ? rank[i+k] : -1;
        int rj = (j+k <= n) ? rank[j+k] : -1;
        return ri < rj;
    }
    // suffix array を構築する
    // O(N log^2 N)
    // how to use: construct_saを呼ぶとsa配列にSuffixArrayを構築する
    void createSA(const string& s, int* sa) {
        n = s.size();
        // 最初は 1 文字ソート
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }
        for (k = 1; k <= n; k*=2) {
            sort(sa, sa+n+1, compare_sa);
            tmp[sa[0]] = 0;
            for (int i = 1; i <= n; i++) {
                tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
            }
            for (int i = 0; i <= n; i++) rank[i] = tmp[i];
        }
    }
    namespace LCP {
        int rank[MAXN];
        // suffix array の情報をもとに longest common prefix を構築する
        // O(N)
        // hot to use: construct_lcpに文字列と suffix array の情報を入れると lcp 配列を作る
        void createLCP(const string& s, const int* sa, int* lcp) {
            int n = s.size();
            for (int i = 0; i <= n; i++) rank[sa[i]] = i;
            int h = 0;
            lcp[0] = 0;
            for (int i = 0; i < n; i++) {
                int j = sa[rank[i]-1];
                h = max(0, h-1);
                for (; j+h < n && i+h < n; h++) {
                    if (s[j+h] != s[i+h]) break;
                }
                lcp[rank[i]-1] = h;
            }
        }
        // sparse table を lcp 配列をもとに構築する
        // getLCP を呼ぶ前に読んでおかないとダメ
        // st[j][i] は lcp[i], lcp[i+1], ..., lcp[i+(2^j)-1] の最小値
        // lcp は (i, i+1) の共通接頭辞を求められるので, st[j][i] は (i, j) の共通接頭辞を求められる
        int st[21][MAXN];
        void initSparseTable(int n, const int* lcp) {
            int h = 1;
            while ((1<<h) < n) h++;
            for (int i = 0; i < n; i++) st[0][i] = lcp[i];
            for (int j = 1; j <= h; j++) {
                for (int i = 0; i <= n-(1<<j); i++) {
                    st[j][i] = min(st[j-1][i], st[j-1][i+(1<<(j-1))]);
                }
            }
        }
        inline int topBit(int t) {
            for (int i = 20; i >= 0; i--) {
                if ((1<<i)&t) return i;
            }
            return -1;
        }
        // suffix array の, "辞書順で" f 番目と s 番目の文字列における longest common prefix を求める
        // s.substr(f) と s.substr(s) の lcp じゃないからね
        int getLCP(int f, int s) {
            if (f > s) swap(f, s);
            int diff = topBit(s-f);
            return min(st[diff][f], st[diff][s-(1<<diff)]);
        }
    } // namespace LCP
} // namespace SA


