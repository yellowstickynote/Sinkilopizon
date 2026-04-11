//change merge and DEFAULT to customize
struct SegTree {
    static int merge(int a, int b) {
        return a + b;
    }
    static const int DEFAULT = 0;
    struct Node {
        int l, r;
        long long val;
    };
    vector<Node> tree;
    int sz;
    SegTree(int n) : sz(n) {
        tree.push_back({0, 0, DEFAULT});
    }
    int createNode(int val, int l = 0, int r = 0) {
        tree.push_back({l, r, val});
        return tree.size() - 1;
    }
    int build(const vector<int> &arr) {
        return build(arr, 0, sz);
    }
    int build(const vector<int> &arr, int lx, int rx) {
        if (rx - lx == 1) {
            int val = (lx < arr.size()) ? arr[lx] : DEFAULT;
            return createNode(val);
        }
        int m = lx + (rx - lx) / 2;
        int left_child = build(arr, lx, m);
        int right_child = build(arr, m, rx);
        return createNode(merge(tree[left_child].val, tree[right_child].val), left_child, right_child);
    }
    int update(int root, int i, int val) {
        return update(root, i, val, 0, sz);
    }
    int update(int cur, int i, int val, int lx, int rx) {
        if (rx - lx == 1) {
            return createNode(val);
        }
        int m = (rx + lx) / 2;
        int cur_l = cur ? tree[cur].l : 0;
        int cur_r = cur ? tree[cur].r : 0;

        if (i < m) {
            int new_l = update(cur_l, i, val, lx, m);
            return createNode(merge(tree[new_l].val, tree[cur_r].val), new_l, cur_r);
        } else {
            int new_r = update(cur_r, i, val, m, rx);
            return createNode(merge(tree[cur_l].val, tree[new_r].val), cur_l, new_r);
        }
    }

    int query(int root, int l, int r) {
        return query(root, l, r + 1, 0, sz);
    }

    int query(int cur, int l, int r, int lx, int rx) {
        if (rx <= l || lx >= r || cur == 0) return DEFAULT;
        if (rx <= r && lx >= l) return tree[cur].val;
        
        int m = lx + (rx - lx) / 2;
        return merge(
            query(tree[cur].l, l, r, lx, m), 
            query(tree[cur].r, l, r, m, rx)
        );
    }
};

