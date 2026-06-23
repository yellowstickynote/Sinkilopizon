struct DSU{
    vector<int> parent,sz;

    DSU(int n){
        parent.resize(n);
        sz.assign(n,1);
        iota(parent.begin(),parent.end(),0);
    }

    int find(int x){
        if(parent[x]==x)return x;
        return parent[x]=find(parent[x]);
    }

    bool unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b)return false;
        if(sz[a]<sz[b])swap(a,b);
        parent[b]=a;
        sz[a]+=sz[b];
        return true;
    }

    int size(int x){
        return sz[find(x)];
    }
};
