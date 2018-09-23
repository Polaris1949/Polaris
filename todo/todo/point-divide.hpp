class point_divide{
    private:
        int tot,head[100005],maxp[100005],size[100005],dis[100005],rem[100005],vis[100005],judge[10000005],q[100005],sum,root;
        node edge[100005<<1];
        void get_root(int u,int pa){
            size[u]=1; maxp[u]=0;
            for(int i=head[u];i;i=edge[i].nxt){
                int v=edge[i].v;
                if(v==pa||vis[v]) continue;
                get_root(v,u);
                size[u]+=size[v];
                maxp[u]=max(maxp[u],size[v]);
            }
            maxp[u]=max(maxp[u],sum-size[u]);
            if(maxp[u]<maxp[root]) root=u;
        }
        void get_dis(int u,int fa){
            rem[++rem[0]]=dis[u];
            for(int i=head[u];i;i=edge[i].nxt){
                int v=edge[i].v;
                if(v==fa||vis[v])continue;
                dis[v]=dis[u]+edge[i].dis;
                get_dis(v,u);
            }
        }
        void calc(int u){
            int p=0;
            for(int i=head[u];i;i=edge[i].nxt){
                int v=edge[i].v;
                if(vis[v])continue;
                rem[0]=0; dis[v]=edge[i].dis;
                get_dis(v,u);
                for(int j=rem[0];j;--j)
                for(int k=1;k<=m;++k)
                if(query[k]>=rem[j])
                test[k]|=judge[query[k]-rem[j]];
                for(int j=rem[0];j;--j)
                q[++p]=rem[j],judge[rem[j]]=1;
            }
            for(int i=1;i<=p;++i) judge[q[i]]=0;
        }
        void divide(int u){
            vis[u]=judge[0]=1; calc(u);
            for(int i=head[u];i;i=edge[i].nxt){
                int v=edge[i].v;
                if(vis[v])continue;
                sum=size[v]; maxp[root=0]=10000005;
                get_root(v,0); divide(root);
            }
        }
    public:
        int test[10000005],query[1010];
        void add_edge(int u,int v,int dis){
            edge[++tot].nxt=head[u];
            edge[tot].v=v;
            edge[tot].dis=dis;
            head[u]=tot;
        }
        void build(){
            maxp[root]=sum=n;
            get_root(1,0);
            divide(root);
        }
        bool check(int i){
            return test[i];
        }
};
