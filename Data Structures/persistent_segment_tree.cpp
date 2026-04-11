//to use this change the merge function 
struct node{
    node *l, *r;
    int val;
    node(int _val): l(nullptr),r(nullptr),val(_val){};
    node(node *_l, node *_r, function<int(node*,node*)> merge): l(_l), r(_r),val(merge(l,r)){};
};

struct SegTree {
    static const int DEFAULT = 0;
    int sz;
    SegTree(int n) : sz(4*n){};
    static int merge(int a, int b){
        return a+b;
    }
    static int nodeMerge(node *l, node *r){
        int a = (l==nullptr) ? DEFAULT : l->val;
        int b = (r==nullptr) ? DEFAULT : r->val;
        return merge(a,b);
    }
    node* build(const vector<int> &arr){
        return build(arr,0,sz);
    }
    node* build(const vector<int> &arr, int lx, int rx){
        if(rx-lx==1) return new node( (lx <arr.size()) ? arr[lx] : DEFAULT);
        int m = (lx+rx)/2;
        return new node(build(arr,lx,m),build(arr,m,rx),nodeMerge);
    }
    node* update(node* root,int i, int val){
        return update(root,i,val,0,sz);
    }
    node* update(node* cur, int i, int val, int lx, int rx ){
        if(rx-lx==1){
            return new node(val);
        }
        int m = (rx+lx)/2;
        if(i<m) return new node(update(cur->l,i,val,lx,m) , cur->r, nodeMerge);
        else return new node(cur->l, update(cur->r,i,val,m,rx), nodeMerge);
    }
    int query(node* root, int l, int r){
        return query(root, l, r+1, 0, sz);
    }
    int query(node* cur, int l, int r, int lx, int rx){
        if(rx<=l ||lx>=r ||cur==nullptr) return DEFAULT;
        if(rx<=r && lx>=l) return cur->val;
        int m = (rx+lx)/2;
        return merge(query(cur->l, l, r, lx, m) , query(cur->r, l, r, m, rx));
    }
};
