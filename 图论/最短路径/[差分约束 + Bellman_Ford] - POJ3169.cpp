/**
 * 把差分约束条件转化为最短路径问题
 * 为什么要求最大值最后转化为求最短路
 * 考虑一组不等式
 * B-A<=c
 * C-B<=a
 * C-A<=b
 * 求C-A的最大值=min(b, a+c)
 * 要同时满足3个条件就是取2个值的最小值
 * 转化为图就是
 * A到B有长为c路
 * B到C有长为a路
 * A到C有长为b路
 * 就是最短路三角形模型
 *
 * 那么这道题就是求1到n的最短路
 * d数组记录最短路径，对于一条权重为w的边e=(v, u)，有d(v) + w >= d(u)
 * 题目中给定了3种不等式
 * 1.隐含的d[i + 1] >= d[i]，这个可以不写，也能过
 * 2.关系好的d[AL] + DL >= d[BL]
 * 3.关系不好的d[AD] + DD <= d[BD]，这个要改写不等式的形式
 * 由于要判断负圈，所以不能用Dijlstra
 * 
 */
#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "algorithm"
const int MAXN = 1010;
const int MAXM = 31000;
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;
const int INF=0x3f3f3f3f;

int dis[MAXN], cnt, n;
struct edge {
    int u, v, w;
};
edge e[MAXM];
void add_edge(int u, int v, int w);
int bellman_ford(int u, int v);
int main() {
//    freopen("in.txt", "r", stdin);
    int u, v, w, a, b;
    scanf("%d%d%d", &n, &a, &b);
    // FOR(i, 1, n)
    //     add_edge(i + 1, i, 0);
    //     可省去
    FOR(i, 0, a) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }
    FOR(i, 0, b) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(v, u, -w);
    }
    int ans = bellman_ford(1, n);
    printf("%d\n", ans);
    return 0;
}

void add_edge(int u, int v, int w) {
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt++].w = w;
}

int bellman_ford(int u, int v) {
    memset(dis, 0x3f, sizeof dis);
    bool flag = 0;
    dis[u] = 0;
    FOR(k, 0, n) {
        flag = 0;
        FOR(i, 0, cnt) {
            if (dis[e[i].v] > dis[e[i].u] + e[i].w) {
                dis[e[i].v] = dis[e[i].u] + e[i].w;
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
    if (flag == 1)//有负圈，无法到达
        return -1;
    else if (dis[v] == INF)//距离无限
        return -2;
    else
        return dis[v];
}