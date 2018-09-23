class link_cut_tree
{
    private:
        int top,c[300005][2],f[300005],q[300005],rv[300005];
        inline void pushup(int x){xr[x]=xr[c[x][0]]^xr[c[x][1]]^val[x];}
        inline void pushdown(int x){
            int l=c[x][0],r=c[x][1];
            if(rv[x]){
                rv[l]^=1;rv[r]^=1;rv[x]^=1;
                swap(c[x][0],c[x][1]);
            }
        }
        inline bool isroot(int x){return c[f[x]][0]!=x&&c[f[x]][1]!=x;}
        inline void rotate(int x){
            int y=f[x],z=f[y],l,r;
            if(c[y][0]==x)l=0;else l=1;r=l^1;
            if(!isroot(y)){if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
            f[x]=z;f[y]=x;f[c[x][r]]=y;
            c[y][l]=c[x][r];c[x][r]=y;
            pushup(y);pushup(x);
        }
        inline void splay(int x){
            top=1;q[top]=x;
            for(int i=x;!isroot(i);i=f[i])q[++top]=f[i];
            for(int i=top;i;i--)pushdown(q[i]);
            while(!isroot(x)){
                int y=f[x],z=f[y];
                if(!isroot(y)){
                    if((c[y][0]==x)^(c[z][0]==y))rotate(x);
                    else rotate(y);
                }rotate(x);
            }
        }
        inline void access(int x){for(int t=0;x;t=x,x=f[x])splay(x),c[x][1]=t,pushup(x);}
        inline void makeroot(int x){access(x);splay(x);rv[x]^=1;}
        inline int find(int x){access(x);splay(x);while(c[x][0])x=c[x][0];return x;}
        inline void split(int x,int y){makeroot(x);access(y);splay(y);}
    public:
        int xr[300005],val[300005];
        inline void cut(int x,int y){if(find(x)!=find(y)) return;split(x,y);if(c[y][0]==x&&c[x][1]==0)c[y][0]=0,f[x]=0;}
        inline void link(int x,int y){if(find(x)!=find(y)) makeroot(x),f[x]=y;}
        inline void change(int x,int y){access(x),splay(x),val[x]=y,pushup(x);}
        inline int xor_sum(int x,int y){split(x,y);return xr[y];}
};
