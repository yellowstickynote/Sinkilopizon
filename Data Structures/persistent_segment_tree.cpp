#include <bits/stdc++.h>
using namespace std;
#ifdef MYPC
#include "debug.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define pb push_back
#define eb emplace_back
#define fi first
#define se second
typedef pair<int, int> pint;
#define vint vector<int>
#define fast_cin()                                                           \
    ios_base::sync_with_stdio(false);                                         \
    cin.tie(NULL);                                                           \
    cout.tie(NULL)
constexpr int mod = 1e9+7;

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

void solve() {
    int n,Q; cin>>n>>Q;
    int A = 5e5+5;
    SegTree sgt(n);
    sgt.build(vint(n));
    int a[n]; for(int i = 0; i<n; i++) cin>>a[i];
    vector<int> pref(n+1);
    pref[0] = sgt.build(vint(A));
    vint mp(A,-1);
    for(int i = 0; i<n; i++){
        pref[i+1] = pref[i];
        if(mp[a[i]]!=-1) pref[i+1] = sgt.update(pref[i+1],mp[a[i]],i-mp[a[i]]);
        mp[a[i]] = i;
    }
    int ans = 0;
    while(Q--){
        int x,y; cin>>x>>y;
        int p = (x^ans)%n;
        int q = (y^ans)%n;
        int l = min(p,q);
        int r = max(p,q);
        ans = sgt.query(pref[r+1],l,r);
        cout<<ans<<endl;
    }
}
signed main() {
    fast_cin();
#ifdef MYPC
    freopen("input.in", "r", stdin);
    //freopen("input.out","w",stdout);
#else
    string filename="";
    if(!filename.empty()) {
        freopen((filename+".in").c_str(), "r", stdin);
        freopen((filename+".out").c_str(), "w", stdout);
    }
#endif
    int t;
    t=1;
    while (t--) {
        solve();
    }
    return 0;
}


