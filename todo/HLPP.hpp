#define chtholly __attribute__((always_inline)) //optmize

const int N=2e4+5,M=2e5+5,inf=0x3f3f3f3f;//size of the arries
int n,s,t;//n:number of vertexes|s:source point|t:meeting point

int tot,v[M<<1],w[M<<1],first[N],nxt[M<<1],h[N],e[N],gap[N<<1],inq[N];//variates needed

class HLPPsupport{//supporting parts of the programme
    private:
    	queue<int> q;
    	bool check() chtholly;
        struct cmp{
            inline bool operator()(int a,int b) const{
                return h[a]<h[b];
            }
        };
        priority_queue<int,vector<int>,cmp> Q;
        void push(int now) chtholly;
        void label(int now) chtholly;
    public:
        friend void add_edge(int u,int v,int w);
        friend int hlpp();
}spt;

bool HLPPsupport::check(){
    int now;
    register int tmp,i;
    for(i=1; i<=n; ++i) h[i]=inf;
    h[t]=0;
    q.push(t);
    while(!q.empty()) {
        now=q.front();
        q.pop();
        for(tmp=first[now]; tmp; tmp=nxt[tmp])
        	if(w[tmp^1]&&h[v[tmp]]>h[now]+1)
                h[v[tmp]]=h[now]+1,q.push(v[tmp]);
    }
    return h[s]!=inf;
}

void HLPPsupport::push(int now){
    int d;
    register int tmp;
    for(tmp=first[now]; tmp; tmp=nxt[tmp])
        if(w[tmp]&&h[v[tmp]]+1==h[now]) {
            d=min(e[now],w[tmp]);
            w[tmp]-=d;
            w[tmp^1]+=d;
            e[now]-=d;
        	e[v[tmp]]+=d;
            if(v[tmp]!=s&&v[tmp]!=t&&!inq[v[tmp]])
                Q.push(v[tmp]),inq[v[tmp]]=1;
            if(!e[now])
                break;
        }
}
void HLPPsupport::label(int now) {
    register int tmp;
    h[now]=inf;
    for(tmp=first[now]; tmp; tmp=nxt[tmp])
        if(w[tmp]&&h[v[tmp]]+1<h[now])
            h[now]=h[v[tmp]]+1;
}

void add_edge(int f,int toward,int fl){//adding edge
    tot+=2,v[tot+1]=f,v[tot]=toward,w[tot]=fl,w[tot+1]=0,nxt[tot]=first[f],first[f]=tot,nxt[tot+1]=first[toward],first[toward]=tot+1;
}

int hlpp(){//core of the programme
    int now,d;
    register int i,tmp;
    if(!spt.check())
        return 0;
    h[s]=n;
    for(i=1; i<=n<<1; ++i) gap[i]=0;
    for(i=1; i<=n; i++)
        if(h[i]<inf)
            ++gap[h[i]];
    for(tmp=first[s]; tmp; tmp=nxt[tmp])
        if(w[tmp]) {
            d=w[tmp];
            w[tmp]-=d;
            w[tmp^1]+=d;
            e[s]-=d;
            e[v[tmp]]+=d;
            if(v[tmp]!=s&&v[tmp]!=t&&!inq[v[tmp]])
                spt.Q.push(v[tmp]),inq[v[tmp]]=1;
        }
    while(!spt.Q.empty()) {
        inq[now=spt.Q.top()]=0;
        spt.Q.pop();
        spt.push(now);
        if(e[now]) {
            if(!--gap[h[now]])
                for(i=1; i<=n; i++)
                    if(i!=s&&i!=t&&h[i]>h[now]&&h[i]<n+1)
                        h[i]=n+1;
            spt.label(now);
            ++gap[h[now]];
            spt.Q.push(now);
            inq[now]=1;
        }
    }
    return e[t];
}
