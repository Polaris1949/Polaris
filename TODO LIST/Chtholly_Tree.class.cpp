class chtholly_tr{
    private:
        long long pown(long long a, long long b, long long mod) {
            long long res = 1;
            long long ans = a % mod;
            while (b) {
                if (b&1)
                    res = res * ans % mod;
                ans = ans * ans % mod;
                b>>=1;
            }
            return res;
        }
        set<node> s;
        set<node>::iterator split(int pos) {
            set<node>::iterator it = s.lower_bound(node(pos));
            if (it != s.end() && it->l == pos)
                return it;
            --it;
            int L = it->l, R = it->r;
            long long V = it->v;
            s.erase(it);
            s.insert(node(L, pos-1, V));
            return s.insert(node(pos, R, V)).first;
        }
    public:
        long long a[100007];
        void add_range(int l, int r, long long val) {
            set<node>::iterator itl = split(l),itr = split(r+1);
            for (; itl != itr; ++itl)
                itl->v += val;
        }
        void assign_range(int l, int r, long long val) {
            set<node>::iterator itl = split(l),itr = split(r+1);
            s.erase(itl, itr);
            s.insert(node(l, r, val));
        }
        long long range_rank(int l, int r, int k) {
            vector<pair<long long, int> > vp;
            set<node>::iterator itl = split(l),itr = split(r+1);
            vp.clear();
            for (; itl != itr; ++itl)
                vp.push_back(pair<long long,int>(itl->v, itl->r - itl->l + 1));
            sort(vp.begin(), vp.end());
            for (vector<pair<long long,int> >::iterator it=vp.begin(); it!=vp.end(); ++it) {
                k -= it->second;
                if (k <= 0)
                    return it->first;
            }
        }
        long long pow_sum_range(int l, int r, int ex, int mod) {
            set<node>::iterator itl = split(l),itr = split(r+1);
            long long res = 0;
            for (; itl != itr; ++itl)
                res = (res + (long long)(itl->r - itl->l + 1) * pown(itl->v, (long long)(ex), (long long)(mod))) % mod;
            return res;
        }
        void init(int x){
            for(register int i=1;i<=x;++i)
                s.insert(node(i,i,a[i]));
            s.insert(node(x+1, x+1, 0));
        }
};
