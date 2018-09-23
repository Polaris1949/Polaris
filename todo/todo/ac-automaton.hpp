class ac_automaton{
	private:
	    int NodeCnt,f[151*71],ch[151*71][26],cnt[151*71],val[151*71],last[151*71];
	    int c[1000010][26],val0[1000010],fail[1000010],cnts;
	    queue<int>q;
	public:
	    char s[151][71];
	    int m;
	    void clear(){
	        memset(f,0,sizeof(f));memset(ch,0,sizeof(ch));memset(cnt,0,sizeof(cnt));memset(val,0,sizeof(val));memset(last,0,sizeof(last));
	        NodeCnt=0;
	    }
	    void insert(char *s,int index){
	        int u=0,n=strlen(s);
	        for(register int i=0;i<n;++i){
	            int tmp=s[i]-'a';
	            if (!ch[u][tmp])ch[u][tmp]=++NodeCnt;
	            u=ch[u][tmp];
	        }
	        val[u]=index;
	        int len=strlen(s);int now=0;
	        for(int i=0;i<len;i++){
	            int v=s[i]-'a';
	            if(!c[now][v])c[now][v]=++cnts;
	            now=c[now][v];
	        }
	        val0[now]++;
	    }
	    void build(){
	        queue<int> Q;
	        Q.push(0);
	        while (!Q.empty()){
	            int u=Q.front(),k=f[u];Q.pop();
	            for(register int tmp=0;tmp<26;++tmp){
	                int v=ch[u][tmp];
	                if (!v){ch[u][tmp]=ch[k][tmp];continue;}
	                f[v]=u?ch[k][tmp]:0;
	                last[v]=val[f[v]]?f[v]:last[f[v]];
	                Q.push(v);
	            }
	        }
	        for(int i=0;i<26;i++)if(c[0][i])fail[c[0][i]]=0,q.push(c[0][i]);
	        while(!q.empty()){
	            int u=q.front();q.pop();
	            for(int i=0;i<26;i++)
	            if(c[u][i])fail[c[u][i]]=c[fail[u]][i],q.push(c[u][i]);
	            else c[u][i]=c[fail[u]][i];
	        }
	    }
	    void query_max(char *T){
	        int u=0,n=strlen(T),res=0;
	        for(register int i=0;i<n;++i){
	            int tmp=T[i]-'a';
	            u=ch[u][tmp];
	            if (val0[u])cnt[val[u]]++;
	            int v=last[u];
	            while (v){
	                if (val[v])cnt[val[v]]++;
	                v=last[v];
	            }
	        }
	        for(register int i=1;i<=m;++i)res=max(res,cnt[i]);
	        printf("%d\n",res);
	        for(register int i=1;i<=m;++i)if(cnt[i]==res) printf("%s\n",s[i]);
	    }
	    void query_num(char *T){
	        int len=strlen(T);int now=0,ans=0;
	        for(int i=0;i<len;i++){
	            now=c[now][T[i]-'a'];
	            for(int t=now;t&&~val0[t];t=fail[t])ans+=val0[t],val0[t]=-1;
	        }
	        printf("%d\n",ans);
	    }
};
