// kmp をやるための前計算
vector<int> makeTable(const string& s) {
    int n = s.size();
    vector<int> ret(n+1);
    ret[0] = -1;
    int j = -1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && s[i] != s[j]) j = ret[j];
        ret[i+1] = ++j;
    }
    return ret;
}

// str の中に word とマッチする場所のリストを返す
// ret のそれぞれの要素 el は, 「str[el] からの文字列が word と一致する」ことを示す
vector<int> kmp(const string& str, const string& word) {
    vector<int> table = makeTable(word), ret;
    int m = 0, i = 0, n = str.size();
    while (m+i < n) {
        if (word[i] == str[m+i]) {
            if (++i == (int)(word.size())) {
                ret.push_back(m);
                m = m+i-table[i];
                i = table[i];
            }
        } else {
            m = m+i-table[i];
            if (i > 0) i = table[i];
        }
    }
    return ret;
}
