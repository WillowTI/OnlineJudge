#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef struct {
    int from, to, cap, flow;//容量。当前流量
}Edge;
Edge e[410];//储存每条边，包括反向边，反向边是反悔用的
vector<int> g[210];//g[i]记录以i为起点有哪些路径，路径是e中的下标
int resident_flow[210], route[202];
//resident_flow是从源点开始，到其余点的残余流量，resident_flow[m]就是最终要求的残余流量
//route是bfs产生的路径，用于在回溯的时候修改走过路径的流量
int n, m;
void add_edge(int index, int from, int to, int cap);
int bfs(int s, int t);//s是起点，t是终点
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2) {
        memset(e, 0, sizeof(e));
        memset(g, 0, sizeof(g));
        memset(route, 0, sizeof(route));
        for (int i = 0; i < n; i++) {
            int from, to, cap;
            scanf("%d%d%d", &from, &to, &cap);
            add_edge(2 * i, from, to, cap);
        }
        int max_flow = 0;
        while (bfs(1, m)) //每次bfs成功就把最大流加上残余流量的最小值
            max_flow += resident_flow[m];
        printf("%d\n", max_flow);
    }
}

void add_edge(int index, int from, int to, int cap) {//同时加入反向边
    e[index].from = e[index + 1].to = from;
    e[index].to = e[index + 1].from = to;
    e[index].cap = cap;
    g[from].push_back(index);
    g[to].push_back(index + 1);
}

int bfs(int s, int t) {
    memset(resident_flow, 0, sizeof(resident_flow));
    queue<int> q;
    q.push(s);
    resident_flow[s] = 0x7fffffff;//源点到源点的残余流量设为无穷大，这样在加入以源点为起点的点时就能正确比较大小了
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < (int)g[x].size(); i++) {
            Edge& edge = e[g[x][i]];
            if (!resident_flow[edge.to] && edge.cap > edge.flow) {//已经走过的点不会重复走，而且保证流量小于容量
                route[edge.to] = g[x][i];//添加路径
                resident_flow[edge.to] = min(resident_flow[x], edge.cap - edge.flow);
                //在计算新的残余流量时，比较从源点到起点和起点到当前的残余流量的最小值
                q.push(edge.to);
            }
        }
        if (resident_flow[t])
            //只要有一条到汇点的合法路径就退出，这样虽然做不能保证这一次的残余流量是所有路径中最大的
            //但是无所谓，因为要遍历所有的路径，最终总是能取到所有的残余流量
            break;
    }
    if (!resident_flow[t]) //如果残余流量为0，说明不存在一条合法路径
        return 0;
    for (int i = t; i != s; i = e[route[i]].from) {//把路径上的流量更新
        e[route[i]].flow += resident_flow[t];//正向边加
        e[route[i] ^ 1].flow += resident_flow[t];//反向边减，注意要异或，因为有可能会对反向边操作，异或后是正向边
    }
    return 1;
}
