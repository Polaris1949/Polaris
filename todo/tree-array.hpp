class tree_arr{
    private:
        int tree[500005],arr[500000];
        inline int lowbit(int x){
            return x&(-x);
        }
        inline int prefix(int x){
            int tmp=0;
            for(register int i=x;i;i-=lowbit(i)) tmp+=tree[i];
            return tmp;
        }
    public:
        inline int num(int x){
            int tmp=0;
            for(register int i=x;i;i-=lowbit(i)) tmp+=arr[i];
            return tmp;
        }
        inline void add(int x,int k){
            int tmp=k-num(x-1);
            for(register int i=x;i<=n;i+=lowbit(i)) tree[i]+=k,arr[i]+=tmp;
        }
        inline void add_range(int x,int y,int k){
            for(register int i=x;i<=n;i+=lowbit(i)) arr[i]+=k;
            for(register int i=y+1;i<=n;i+=lowbit(i)) arr[i]-=k;
        }
        inline int sum(int x,int y){
            return prefix(y)-prefix(x-1);
        }
};
