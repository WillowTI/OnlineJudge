/**
 * 给定一个无向图
 * 输入一些点对，说明这些点对之间有路
 * 由于路的个数和顶点的个数相同，所以一定会有通路
 * 现在查询一些点对之间的最短路径，如果没有输出-1
 *
 * 先用并查集把属于同一个通路的顶点加入进去，这样就能判断是否存在通路了
 * 还要一个数组记录一个集合的大小
 * 对于存在通路的情况，先用DFS算出一条通路来
 * 再和其反向通路的长度，也就是保存集合大小的数组减去这次的长度，相比较，输出较小值
 */
#include <bits/stdc++.h>
using namespace std;
int n, m;
int par[100005], sz[100005];
int connect[100005][2];
int vis[100005];
void un(int x, int y);
int found(int x);
int dfs(int x, int y);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (connect[x][0])
            connect[x][1] = y;
        else
            connect[x][0]= y;
        if (connect[y][0])
            connect[y][1] = x;
        else
            connect[y][0] = x;
        un(x, y);
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int fx = found(x);
        int fy = found(y);
        if (fx != fy)
            puts("-1");
        else {
            memset(vis, 0, sizeof(vis));
            int path = dfs(x, y);
            printf("%d\n", min(path, sz[fx] - path));
        }
    }
    return 0;
}

int found(int x) {
    return x == par[x] ? x : par[x] = found(par[x]);
}

void un(int x, int y) {
    x = found(x);
    y = found(y);
    if (x != y) {
        par[x] = y;
        sz[y] += sz[x];
    }
}

int dfs(int x, int y) {
    vis[x] = 1;
    if (x == y)
        return 0;
    if (!vis[connect[x][0]]) {
        vis[connect[x][0]] = 1;
        return dfs(connect[x][0], y) + 1;
    }
    else if (!vis[connect[x][1]]) {
        vis[connect[x][1]] = 1;
        return dfs(connect[x][1], y) + 1;
    }
    return 0;
}
