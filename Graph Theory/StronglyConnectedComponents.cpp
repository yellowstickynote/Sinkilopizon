vector<int> st,root,tin,low;
int timer;

void dfs(int v,vector<vector<int>>&adj,vector<vector<int>>&comp){
    tin[v]=low[v]=timer++;
    st.push_back(v);

    for(int u:adj[v]){
        if(tin[u]==-1){
            dfs(u,adj,comp);
            low[v]=min(low[v],low[u]);
        }else if(root[u]==-1){
            low[v]=min(low[v],tin[u]);
        }
    }

    if(low[v]==tin[v]){
        comp.push_back({});
        while(true){
            int u=st.back();
            st.pop_back();
            root[u]=v;
            comp.back().push_back(u);
            if(u==v)break;
        }
    }
}

void scc(vector<vector<int>>&adj,vector<vector<int>>&comp,vector<vector<int>>&cond){
    int n=adj.size();

    st.clear();
    root.assign(n,-1);
    tin.assign(n,-1);
    low.assign(n,-1);
    timer=0;

    for(int i=0;i<n;i++)
        if(tin[i]==-1)
            dfs(i,adj,comp);

    cond.assign(n,{});
    for(int v=0;v<n;v++)
        for(int u:adj[v])
            if(root[v]!=root[u])
                cond[root[v]].push_back(root[u]);
}
