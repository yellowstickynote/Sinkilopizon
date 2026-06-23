struct KMP {
    string pat;
    vector<int> pi; // prefix function of pat

    KMP(const string &p) : pat(p), pi(prefix(p)) {}

    // Prefix function of s: pi[i] = length of the longest proper prefix of
    // s[0..i] that is also a suffix of s[0..i]. O(|s|).
    static vector<int> prefix(const string &s) {
        int n = s.size();
        vector<int> pi(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    // Start indices (0-based) of every occurrence of pat in text. O(|text| + |pat|).
    vector<int> find_all(const string &text) const {
        vector<int> occ;
        int m = pat.size();
        if (m == 0) return occ;
        int j = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            while (j > 0 && text[i] != pat[j]) j = pi[j - 1];
            if (text[i] == pat[j]) j++;
            if (j == m) {
                occ.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }
        return occ;
    }

    // Number of occurrences of pat in text. O(|text| + |pat|).
    int count(const string &text) const { return (int)find_all(text).size(); }

    // Smallest period of pat: the least p such that pat[i] == pat[i + p].
    // pat is fully periodic iff (|pat| % period() == 0).
    int period() const {
        int m = pat.size();
        return m == 0 ? 0 : m - pi[m - 1];
    }

    // All border lengths of pat (proper prefixes that are also suffixes),
    // descending. The longest border is pi.back().
    vector<int> borders() const {
        vector<int> res;
        for (int b = pi.empty() ? 0 : pi.back(); b > 0; b = pi[b - 1])
            res.push_back(b);
        return res;
    }

    // KMP automaton over an alphabet of `sigma` letters starting at `base`.
    // aut[state][c] = next state after reading character (base + c); states are
    // 0..|pat|, where reaching state |pat| means a full match just ended.
    // Handy for DP over strings. O(|pat| * sigma).
    vector<vector<int>> automaton(int sigma = 26, char base = 'a') const {
        string s = pat + char(0); // sentinel guarantees state |pat| is reachable
        int n = s.size();
        vector<int> p = prefix(s);
        vector<vector<int>> aut(n, vector<int>(sigma));
        for (int i = 0; i < n; i++)
            for (int c = 0; c < sigma; c++) {
                if (i > 0 && base + c != s[i])
                    aut[i][c] = aut[p[i - 1]][c];
                else
                    aut[i][c] = i + (base + c == s[i]);
            }
        return aut;
    }
};
