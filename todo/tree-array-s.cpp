#include <iostream>

int n, m;

class tree_array
{
public:
        int tree[500005],arr[500000];
        inline int lowbit(int x){
            return x&(-x);
        }
        inline int prefix(int x){
            int tmp=0;
            for(int i=x;i;i-=lowbit(i))
            {
                std::cerr << "$ i=" << i-1 << '\n';
                tmp+=tree[i];
            }
            return tmp;
        }
    public:
        inline int num(int x){
            int tmp=0;
            for(int i=x;i;i-=lowbit(i)) tmp+=arr[i];
            return tmp;
        }
        inline void add(int x,int k){
            int tmp=k-num(x-1);
            for(int i=x;i<=n;i+=lowbit(i))
            {
                //std::cerr << "* i=" << i-1 << '\n';
                tree[i]+=k;
                arr[i]+=tmp;
            }
        }
        inline void add_range(int x,int y,int k){
            for(int i=x;i<=n;i+=lowbit(i)) arr[i]+=k;
            for(int i=y+1;i<=n;i+=lowbit(i)) arr[i]-=k;
        }
        inline int sum(int x,int y){
            std::cerr << "# x=" << x-1 << " y=" << y << '\n';
            return prefix(y)-prefix(x-1);
        }
};

tree_array a;

int main()
{
    int o, x, y;
    std::cin >> n >> m;
    //a.resize(n);
    auto check = [&a]()
    {
        std::cerr << "> ";
        for (int i=1; i<=n; ++i)
            std::cerr << a.tree[i] << ' ';
        std::cerr << '\n';
    };
    check();
    for (int i=1; i<=n; ++i)
    {
        std::cin >> x;
        a.add(i, x);
        check();
    }
    for (int i=0; i<m; ++i)
    {
        std::cin >> o >> x >> y;
        if (o==1) a.add(x, y);
        else std::cout<<a.sum(x, y)<<'\n';
        check();
    }
}
