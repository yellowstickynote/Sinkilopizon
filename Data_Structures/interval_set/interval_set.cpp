struct IntervalSet {
    struct Interval {
        int l, r;
        bool operator<(const Interval& o) const { return l != o.l ? l < o.l : r < o.r; }
    };
    set<Interval> st;
    set<pair<int, int>> sz_st;

    void add(int l, int r) {
        st.insert({l, r});
        sz_st.insert({r - l + 1, l});
    }

    auto rem(set<Interval>::iterator it) {
        sz_st.erase({it->r - it->l + 1, it->l});
        return st.erase(it);
    }

    void ins(int l, int r) {
        auto it = st.lower_bound({l, l});
        if (it != st.begin()) { auto p = it; if ((--p)->r + 1 >= l) it = p; }
        while (it != st.end() && it->l <= r + 1) {
            l = min(l, it->l);
            r = max(r, it->r);
            it = rem(it);
        }
        add(l, r);
    }

    void del(int l, int r) {
        auto it = st.lower_bound({l, l});
        if (it != st.begin()) { auto p = it; if ((--p)->r >= l) it = p; }
        int pl = l, pr = l - 1, sl = r + 1, sr = r;
        while (it != st.end() && it->l <= r) {
            if (it->l < l) { pl = it->l; pr = l - 1; }
            if (it->r > r) { sl = r + 1; sr = it->r; }
            it = rem(it);
        }
        if (pl <= pr) add(pl, pr);
        if (sl <= sr) add(sl, sr);
    }

    int intersect(int l, int r) {
        int res = 0;
        auto it = st.lower_bound({l, l});
        if (it != st.begin()) { auto p = it; if ((--p)->r >= l) it = p; }
        while (it != st.end() && it->l <= r) {
            int il = max(l, it->l), ir = min(r, it->r);
            if (il <= ir) res += ir - il + 1;
            ++it;
        }
        return res;
    }

    pair<int, int> surrounding_range(int pos) {
        auto it = st.upper_bound({pos, 2e18});
        if (it != st.begin()) {
            auto p = it; --p;
            if (p->l <= pos && p->r >= pos) return {p->l, p->r};
        }
        return {-1, -1};
    }
};
