struct KMP {
    vector<int> pat, pi;
    KMP(const vector<int> &p) : pat(p), pi(prefix(p)) {}
    static vector<int> prefix(const vector<int> &s) {
        vector<int> pi(s.size(), 0);
        for (int i = 1, j; i < (int)s.size(); i++) {
            for (j = pi[i - 1]; j && s[i] != s[j]; j = pi[j - 1]);
            pi[i] = j + (s[i] == s[j]);
        }
        return pi;
    }
    vector<int> find_all(const vector<int> &t) const {
        vector<int> occ;
        int m = pat.size(), j = 0;
        for (int i = 0; m && i < (int)t.size(); i++) {
            for (; j && t[i] != pat[j]; j = pi[j - 1]);
            if (t[i] == pat[j] && ++j == m) occ.push_back(i - m + 1), j = pi[j - 1];
        }
        return occ;
    }
    int count(const vector<int> &t) const { return find_all(t).size(); }
    vector<vector<int>> automaton(int sigma) const {
        vector<int> s = pat;
        s.push_back(-1);
        vector<int> p = prefix(s);
        vector<vector<int>> aut(s.size(), vector<int>(sigma));
        for (int i = 0; i < (int)s.size(); i++)
            for (int c = 0; c < sigma; c++)
                aut[i][c] = (i && c != s[i]) ? aut[p[i - 1]][c] : i + (c == s[i]);
        return aut;
    }
};
