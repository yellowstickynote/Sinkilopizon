template<typename T>
struct SegmentTree{
    int n;
    vector<T> tree,lazy;

    SegmentTree(int size){
        n=size;
        tree.assign(4*n,T());
        lazy.assign(4*n,T());
    }

    void push(int node,int start,int end){
        if(lazy[node]!=T()){
            tree[node]+=lazy[node]*(end-start+1);
            if(start!=end){
                lazy[node*2]+=lazy[node];
                lazy[node*2+1]+=lazy[node];
            }
            lazy[node]=T();
        }
    }

    void build(vector<T>&a,int node=1,int start=0,int end=-1){
        if(end==-1)end=n-1;
        if(start==end){
            tree[node]=a[start];
            return;
        }
        int mid=(start+end)/2;
        build(a,node*2,start,mid);
        build(a,node*2+1,mid+1,end);
        tree[node]=tree[node*2]+tree[node*2+1];
    }

    void update(int l,int r,T val,int node=1,int start=0,int end=-1){
        if(end==-1)end=n-1;
        push(node,start,end);
        if(start>r||end<l)return;
        if(start>=l&&end<=r){
            lazy[node]+=val;
            push(node,start,end);
            return;
        }
        int mid=(start+end)/2;
        update(l,r,val,node*2,start,mid);
        update(l,r,val,node*2+1,mid+1,end);
        tree[node]=tree[node*2]+tree[node*2+1];
    }

    T query(int l,int r,int node=1,int start=0,int end=-1){
        if(end==-1)end=n-1;
        push(node,start,end);
        if(start>r||end<l)return T();
        if(start>=l&&end<=r)return tree[node];
        int mid=(start+end)/2;
        return query(l,r,node*2,start,mid)+query(l,r,node*2+1,mid+1,end);
    }
};
