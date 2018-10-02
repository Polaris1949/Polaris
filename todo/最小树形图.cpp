#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int n, m;
class min_tree_graph{
    private:
        int g[110][110];
        bool vis[110];
        bool flag[110];
        int pre[110];
    public:
        min_tree_graph(){
            memset(g,0x3f,sizeof(g));
        }
        int zhuliu(int root) {
            int ans = 0, i, j, cnt;
            while (1){
                for (i = 1; i <= n; ++i) {
                    if (i == root || flag[i]) continue;
                    g[i][i] = inf; pre[i] = i;
                    for (j = 1; j <= n; ++j) {
                        if (i == j) continue;
                        if (!flag[j] && g[j][i] < g[pre[i]][i])
                            pre[i] = j;
                    }
                    if (pre[i] == i) return -1;
                }
                for (i = 1; i <= n; ++i) {
                    if (i == root || flag[i]) continue;
                    j = i, cnt = 0;
                    while (j != root && pre[j] != i && cnt <= n) j = pre[j], ++cnt;
                    if (j != root && cnt <= n)  break;
                }
                if (i > n) {
                    for (i = 1; i <= n; ++i) {
                        if (i == root || flag[i]) continue;
                        ans += g[pre[i]][i];
                    }
                    return ans;
                }
                j = i;
                memset(vis,0,sizeof(vis));
                do {
                    ans += g[pre[j]][j];
                    flag[j] = vis[j] = 1;
                    j = pre[j];
                } while (i != j);
                flag[i] = 0;
                for (register int k = 1; k <= n; ++k)
                    if (vis[k])
                        for (j = 1; j <= n; ++j)
                            if (!vis[j]) {
                                g[i][j] = min(g[i][j], g[k][j]);
                                if (g[j][k] < inf && g[j][k] - g[pre[k]][k] < g[j][i]) {
                                    g[j][i] = g[j][k] - g[pre[k]][k];
                                }
                            }
            }
            return ans;
        }
        void insert(int a,int b,int w){
            g[a][b]=min(g[a][b],w);
        }
        int root;
}gr;

int main() {
    ios_base::sync_with_stdio(false);
    cin>>n>>m>>gr.root;
    for(register int i=1;i<=m;++i){
    	int a,b,w;
        cin>>a>>b>>w;
        gr.insert(a,b,w);
    }
    cout<<gr.zhuliu(gr.root);
    return 0;
}
