/**
 * Tarjan离线处理
 * 用并查集保存lca
 * O(n+q)
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int i = a; i < b; i++)
using namespace std;
typedef long long LL;

struct edge {
    int to, cost;
    edge(int a, int b) {
        to = a;
        cost = b;
    }
};
const int MAXN = 4e4+5;
int n, q;
int par[MAXN], dis[MAXN];
int ans[205];
bool vis[MAXN];
vector<edge> G[MAXN];
vector<edge> Q[MAXN];

void lca(int x);
int dsu_find(int x);
int main() {
//    freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        memset(dis, 0, sizeof dis);
        memset(vis, 0, sizeof vis);
        memset(ans, 0, sizeof ans);
        scanf("%d%d", &n, &q);
        FOR (i, 1, n + 1) {
            G[i].clear();
            Q[i].clear();
            par[i] = i;
        }
        FOR (i, 0, n - 1) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            G[a].push_back(edge(b, c));
            G[b].push_back(edge(a, c));
        }
        FOR (i, 0, q) {
            int a, b;
            scanf("%d%d", &a, &b);
            Q[a].push_back(edge(b, i));
            Q[b].push_back(edge(a, i));
        }
        vis[1] = true;
        lca(1);
        FOR (i, 0, q)
            cout << ans[i] << "\n";
    }
    return 0;
}

int dsu_find(int x) {
    return x == par[x] ? x : par[x] = dsu_find(par[x]);
}

void lca(int x) {
    FOR (i, 0, G[x].size()) {
        int u = G[x][i].to;
        if (vis[u]) continue;
        int c = G[x][i].cost;
        dis[u] = dis[x] + c;
        lca(u);
        /**
         * 算法的思想是把属于x子节点的lca处理掉
         * 所以这时候是不能修改其父节点的
         */
        vis[u] = true;//这句话可以放到lca前面
        par[u] = x;//但是这句话必须在lca后面
    }
    FOR (i, 0, Q[x].size()) {
        int u = Q[x][i].to;
        if (vis[u]) {
            ans[Q[x][i].cost] = dis[x] + dis[u] - 2 * dis[dsu_find(u)];
        }
    }
}