class suffix_automaton
{
    private:
        int last,cnt,ch[2000005<<1][26],fa[2000005<<1],l[2000005<<1],a[2000005],c[2000005],size[2000005];
        long long ans;
        void ins(int c){
            int p=last,np=++cnt;last=np;l[np]=l[p]+1;
            for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
            if(!p)fa[np]=1;
            else{
                int q=ch[p][c];
                if(l[p]+1==l[q])fa[np]=q;
                else{
                    int nq=++cnt;l[nq]=l[p]+1;
                    memcpy(ch[nq],ch[q],sizeof(ch[q]));
                    fa[nq]=fa[q];fa[q]=fa[np]=nq;
                    for(;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
                }
            }
            size[np]=1;
        }
    public:
        char s[2000005];
        void build(){
            scanf("%s",s+1);
            int len=strlen(s+1);
            last=cnt=1;for(int i=1;i<=len;i++)ins(s[i]-'a');
        }
        long long maxium(){
            ans=0;
            for(int i=1;i<=cnt;i++)c[l[i]]++;
            for(int i=1;i<=cnt;i++)c[i]+=c[i-1];
            for(int i=1;i<=cnt;i++)a[c[l[i]]--]=i;
            for(int i=cnt;i;i--){
                int p=a[i];
                size[fa[p]]+=size[p];
                if(size[p]>1)ans=max(ans,1LL*size[p]*l[p]);
            }
            return ans;
        }
};
