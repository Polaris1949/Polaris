class tree_chain
{
    private:
        int e,beg[200010],nex[200010],to[200010],wt[200010],a[200010<<2],laz[200010<<2],son[200010],id[200010],fa[200010],cnt,dep[200010],siz[200010],top[200010],res=0;
        inline void pushdown(int rt,int lenn){
            laz[rt<<1]+=laz[rt];
            laz[rt<<1|1]+=laz[rt];
            a[rt<<1]+=laz[rt]*(lenn-(lenn>>1));
            a[rt<<1|1]+=laz[rt]*(lenn>>1);
            a[rt<<1]%=mod;
            a[rt<<1|1]%=mod;
            laz[rt]=0;
        }
        inline void build(int rt,int l,int r){
            if(l==r){
                a[rt]=wt[l];
                if(a[rt]>mod)a[rt]%=mod;
                return;
            }
            build(rt<<1,l,((l+r)>>1));
            build(rt<<1|1,((l+r)>>1)+1,r);
            a[rt]=(a[rt<<1]+a[rt<<1|1])%mod;
        }
        inline void query(int rt,int l,int r,int L,int R){
            if(L<=l&&r<=R){res+=a[rt];res%=mod;return;}
            else{
                if(laz[rt])pushdown(rt,(r-l+1));
                if(L<=((l+r)>>1))query(rt<<1,l,((l+r)>>1),L,R);
                if(R>((l+r)>>1))query(rt<<1|1,((l+r)>>1)+1,r,L,R);
            }
        }
        inline void update(int rt,int l,int r,int L,int R,int k){
            if(L<=l&&r<=R){
                laz[rt]+=k;
                a[rt]+=k*(r-l+1);
            }
            else{
                if(laz[rt])pushdown(rt,(r-l+1));
                if(L<=((l+r)>>1))update(rt<<1,l,((l+r)>>1),L,R,k);
                if(R>((l+r)>>1))update(rt<<1|1,((l+r)>>1)+1,r,L,R,k);
                a[rt]=(a[rt<<1]+a[rt<<1|1])%mod;
            }
        }
        inline void dfs1(int x,int f,int deep){
            dep[x]=deep;
            fa[x]=f;
            siz[x]=1;
            int maxson=-1;
            for(register int i=beg[x];i;i=nex[i]){
                int y=to[i];
                if(y==f)continue;
                dfs1(y,x,deep+1);
                siz[x]+=siz[y];
                if(siz[y]>maxson)son[x]=y,maxson=siz[y];
            }
        }
        inline void dfs2(int x,int topf){
            id[x]=++cnt;
            wt[cnt]=w[x];
            top[x]=topf;
            if(!son[x])return;
            dfs2(son[x],topf);
            for(register int i=beg[x];i;i=nex[i]){
                int y=to[i];
                if(y==fa[x]||y==son[x])continue;
                dfs2(y,y);
            }
        }
    public:
        int w[200010];
        inline void add_edge(int x,int y){
            to[++e]=y;
            nex[e]=beg[x];
            beg[x]=e;
        }
        inline int query_range(int x,int y){
            int ans=0;
            while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]])swap(x,y);
                res=0;
                query(1,1,n,id[top[x]],id[x]);
                ans+=res;
                ans%=mod;
                x=fa[top[x]];
            }
            if(dep[x]>dep[y])swap(x,y);
            res=0;
            query(1,1,n,id[x],id[y]);
            ans+=res;
            return ans%mod;
        }
        inline void add_range(int x,int y,int k){
            k%=mod;
            while(top[x]!=top[y]){
                if(dep[top[x]]<dep[top[y]])swap(x,y);
                update(1,1,n,id[top[x]],id[x],k);
                x=fa[top[x]];
            }
            if(dep[x]>dep[y])swap(x,y);
            update(1,1,n,id[x],id[y],k);
        }
        inline int query_son(int x){
            res=0;
            query(1,1,n,id[x],id[x]+siz[x]-1);
            return res;
        }
        inline void add_son(int x,int k){
            update(1,1,n,id[x],id[x]+siz[x]-1,k);
        }
        inline void init(int root,int num){
            dfs1(root,0,1);
            dfs2(root,root);
            build(1,1,num);
        }
};
