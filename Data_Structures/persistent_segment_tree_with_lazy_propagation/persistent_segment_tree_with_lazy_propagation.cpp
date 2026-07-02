#include <vector>

using namespace std;

struct LazySegTree {
    static long long merge(long long a, long long b) { // customize
        return a + b;
    }
    static const long long DEFAULT = 0; // customize

    struct Node {
        int l, r;
        long long val;
        long long lazy; 
    };

    vector<Node> tree;
    int sz;

    LazySegTree(int n) : sz(n) {
        tree.push_back({0, 0, DEFAULT, 0});
    }

    int createNode(long long val, int l = 0, int r = 0, long long lazy = 0) {
        tree.push_back({l, r, val, lazy});
        return tree.size() - 1;
    }

    int cloneNode(int cur) {
        tree.push_back(tree[cur]);
        return tree.size() - 1;
    }

    int build(const vector<int> &arr) {
        return build(arr, 0, sz);
    }

    int build(const vector<int> &arr, int lx, int rx) {
        if (rx - lx == 1) {
            long long val = (lx < arr.size()) ? arr[lx] : DEFAULT;
            return createNode(val);
        }
        int m = lx + (rx - lx) / 2;
        int left_child = build(arr, lx, m);
        int right_child = build(arr, m, rx);
        return createNode(merge(tree[left_child].val, tree[right_child].val), left_child, right_child);
    }

    int update(int root, int l, int r, long long val) {
        return update(root, l, r + 1, val, 0, sz);
    }

    int update(int cur, int l, int r, long long val, int lx, int rx) {
        if (rx <= l || lx >= r) return cur;

        int new_cur = cur ? cloneNode(cur) : createNode(DEFAULT);

        if (rx <= r && lx >= l) {
            tree[new_cur].lazy += val;
            tree[new_cur].val += val * (rx - lx); // customize
            return new_cur;
        }

        int m = lx + (rx - lx) / 2;
        tree[new_cur].l = update(tree[new_cur].l, l, r, val, lx, m);
        tree[new_cur].r = update(tree[new_cur].r, l, r, val, m, rx);

        long long left_val = tree[new_cur].l ? tree[tree[new_cur].l].val : DEFAULT;
        long long right_val = tree[new_cur].r ? tree[tree[new_cur].r].val : DEFAULT;

        tree[new_cur].val = merge(left_val, right_val) + tree[new_cur].lazy * (rx - lx); // customize

        return new_cur;
    }

    long long query(int root, int l, int r) {
        return query(root, l, r + 1, 0, sz, 0);
    }

    long long query(int cur, int l, int r, int lx, int rx, long long lazy_acc) {
        if (rx <= l || lx >= r) return DEFAULT;

        if (rx <= r && lx >= l) {
            long long cur_val = cur ? tree[cur].val : DEFAULT;
            return cur_val + lazy_acc * (rx - lx); // customize
        }

        int m = lx + (rx - lx) / 2;
        long long next_lazy = lazy_acc + (cur ? tree[cur].lazy : 0);

        return merge(
            query(cur ? tree[cur].l : 0, l, r, lx, m, next_lazy),
            query(cur ? tree[cur].r : 0, l, r, m, rx, next_lazy)
        );
    }
};
