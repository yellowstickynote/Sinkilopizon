struct KMP {
    string pat;
    vector<int> pi;

    KMP(const string &p) : pat(p), pi(prefix(p)) {}

    static vector<int> prefix(const string &s) {
        vector<int> pi(s.size(), 0);
        for (int i = 1, j; i < (int)s.size(); i++) {
            for (j = pi[i - 1]; j && s[i] != s[j]; j = pi[j - 1]);
            pi[i] = j + (s[i] == s[j]);
        }
        return pi;
    }

    vector<int> find_all(const string &t) const {
        vector<int> occ;
        int m = pat.size(), j = 0;
        for (int i = 0; m && i < (int)t.size(); i++) {
            for (; j && t[i] != pat[j]; j = pi[j - 1]);
            if (t[i] == pat[j] && ++j == m) occ.push_back(i - m + 1), j = pi[j - 1];
        }
        return occ;
    }

    int count(const string &t) const { return find_all(t).size(); }

    int period() const { return pat.empty() ? 0 : pat.size() - pi.back(); }

    vector<int> borders() const {
        vector<int> res;
        for (int b = pi.empty() ? 0 : pi.back(); b; b = pi[b - 1]) res.push_back(b);
        return res;
    }

    vector<vector<int>> automaton(int sigma = 26, char base = 'a') const {
        string s = pat + char(0);
        vector<int> p = prefix(s);
        vector<vector<int>> aut(s.size(), vector<int>(sigma));
        for (int i = 0; i < (int)s.size(); i++)
            for (int c = 0; c < sigma; c++)
                aut[i][c] = (i && base + c != s[i]) ? aut[p[i - 1]][c] : i + (base + c == s[i]);
        return aut;
    }
};
