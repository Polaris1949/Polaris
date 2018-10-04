#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int n,m;

inline int get(){
    register int x=0,o=0;register char ch=getchar();
    while(ch!='-'&&(ch<'0'||'9'<ch)) ch=getchar();
    if(ch=='-') o=1,ch=getchar();
    while('0'<=ch&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return o?-x:x;
}

struct Tree{
  int l,r;
}tr[200010*30];

class persistent_union_set{
private:
	int fa[200010*30],deep[200010*30],tot;
	inline void update(int &rt,register int last,register int l,register int r,register int pos,register int ff){
	    rt=++tot;
	    if(l==r){
	        fa[rt]=ff;
	        deep[rt]=deep[last];
	        return;
	    }
	    tr[rt].l=tr[last].l;tr[rt].r=tr[last].r;
	    register int mid=l+r>>1;
	    if(pos<=mid) update(tr[rt].l,tr[last].l,l,mid,pos,ff);
	    else update(tr[rt].r,tr[last].r,mid+1,r,pos,ff);
	}
	inline int query_fa(register int rt,register int l,register int r,register int pos) {
	    if(l==r) return rt;
	    register int mid=l+r>>1;
	    if(pos<=mid) return query_fa(tr[rt].l,l,mid,pos);
	    else return query_fa(tr[rt].r,mid+1,r,pos);
	}
	inline void add(register int rt,register int l,register int r,register int pos){
	    if(l==r){
	        ++deep[rt];
	        return;
	    }
	    register int mid=l+r>>1;
	    if(pos<=mid) add(tr[rt].l,l,mid,pos);
	    else add(tr[rt].r,mid+1,r,pos);
	}
	inline int find_fa(register int ed,register int x) {
	    register int ff=query_fa(ed,1,n,x);
	    if(x==fa[ff]) return ff;
	    return find_fa(ed,fa[ff]);
	}
public:
	int edge[200010];
	inline void build(int &rt,register int l,register int r){
	    rt=++tot;
	    if(l==r){
	        fa[rt]=l;
	        return;
	    }
	    register int mid=l+r>>1;
	    build(tr[rt].l,l,mid);
	    build(tr[rt].r,mid+1,r);
	}
	inline void unite(int i,int a,int b){
		edge[i]=edge[i-1];
        register int f1=find_fa(edge[i],a);
        register int f2=find_fa(edge[i],b);
        if(fa[f1]==fa[f2]) return;
        if(deep[f1]>deep[f2]) swap(f1,f2);
        update(edge[i],edge[i-1],1,n,fa[f1],fa[f2]);
        if(deep[f1]==deep[f2]) add(edge[i],1,n,fa[f2]);
	}
	inline void return_to(int i,int k){
		edge[i]=edge[k];
	}
	inline bool judge(int i,int a,int b){
		edge[i]=edge[i-1];
		register int f1=find_fa(edge[i],a);
        register int f2=find_fa(edge[i],b);
        return  !(fa[f1]^fa[f2]);
	}
}s;

int main(){
    n=get(),m=get();
    s.build(s.edge[0],1,n);
    for(register int opt,i=1;i<=m;++i){
    	int k,a,b;
        opt=get();
        if(opt==1) a=get(),b=get(),s.unite(i,a,b);
        if(opt==2) k=get(),s.return_to(i,k);
        if(opt==3){
            a=get(),b=get();
            if(s.judge(i,a,b)) puts("1");
            else puts("0");
        }
    }
}
