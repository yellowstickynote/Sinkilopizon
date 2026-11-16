vector<int> to_vec(const string &s, int norm = 0) {
    vector<int> v(s.size());
    for (int i = 0; i < (int)s.size(); i++) v[i] = s[i] - norm;
    return v;
}

struct AhoCorasick {
    struct Node { int back = 0, start = -1, end = -1, nmatches = 0; };
    int sigma;
    vector<Node> N;
    vector<int> nxt, backp, order, endNode, len;

    int &go(int v, int c) { return nxt[v * sigma + c]; }
    int go(int v, int c) const { return nxt[v * sigma + c]; }

    AhoCorasick(const vector<vector<int>> &pat, int sigma)
        : sigma(sigma), N(1), nxt(sigma, -1), endNode(pat.size()), len(pat.size()) {
        for (int j = 0; j < (int)pat.size(); j++) insert(pat[j], j);
        N[0].back = N.size();
        N.emplace_back();
        nxt.insert(nxt.end(), sigma, 0);
        order.push_back(0);
        for (int h = 0; h < (int)order.size(); h++) {
            int n = order[h], prev = N[n].back;
            for (int c = 0; c < sigma; c++) {
                int &ed = go(n, c), y = go(prev, c);
                if (ed == -1) ed = y;
                else {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    order.push_back(ed);
                }
            }
        }
    }

    void insert(const vector<int> &s, int j) {
        assert(!s.empty());
        int n = 0;
        for (int c : s) {
            int m = go(n, c);
            if (m == -1) {
                m = N.size();
                N.emplace_back();
                nxt.insert(nxt.end(), sigma, -1);
                go(n, c) = m;
            }
            n = m;
        }
        endNode[j] = n, len[j] = s.size();
        if (N[n].end == -1) N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }

    vector<int> find(const vector<int> &t) const {
        vector<int> res;
        int n = 0;
        for (int c : t) n = go(n, c), res.push_back(N[n].end);
        return res;
    }

    vector<vector<int>> find_all(const vector<int> &t) const {
        vector<int> r = find(t);
        vector<vector<int>> res(t.size());
        for (int i = 0; i < (int)t.size(); i++)
            for (int j = r[i]; j != -1; j = backp[j]) res[i - len[j] + 1].push_back(j);
        return res;
    }

    // val[v] = merge of val over the whole subtree of v in the suffix-link tree
    template <class T, class Merge> void push_up(vector<T> &val, Merge merge) const {
        for (int i = (int)order.size() - 1; i > 0; i--) merge(val[N[order[i]].back], val[order[i]]);
    }
    // val[v] = merge of val over v and all its suffix-link ancestors
    template <class T, class Merge> void push_down(vector<T> &val, Merge merge) const {
        for (int i = 1; i < (int)order.size(); i++) merge(val[order[i]], val[N[order[i]].back]);
    }

    // visit(cell, i) runs on the state reached after t[i]; merge(into, from) folds up the tree
    template <class T, class Visit, class Merge>
    vector<T> per_pattern(const vector<int> &t, T id, Visit visit, Merge merge) const {
        vector<T> val(N.size(), id);
        int n = 0;
        for (int i = 0; i < (int)t.size(); i++) n = go(n, t[i]), visit(val[n], i);
        push_up(val, merge);
        vector<T> res(endNode.size());
        for (int j = 0; j < (int)res.size(); j++) res[j] = val[endNode[j]];
        return res;
    }
};
