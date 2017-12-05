/** 
 * Dinic和EK在求一条路径时都是用BFS
 * Dinic在BFS的过程中把层次，也可以认为是路径，构造出来
 * 二者的区别在于Dinic在修改路径上的残余流量时是用DFS，所以是递归的结构
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef struct Edge{
    int from, to, cap, flow;
    Edge(){}
    Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow){}
}Edge;
vector<Edge> e;
vector<int> g[20];
int n, m;
int level[20];
void add_edge(int index, int from, int to, int cap);
int bfs();
int dfs(int x, int resident_flow);//resident_flow是源点到x的残余流量，在遍历的过程会越来越小，可以理解为流被分配到其他的路径上
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    for (int t = 1; t <= cas; t++) {
        e.clear();
        for (int i = 0; i < 20; i++)
            g[i].clear();
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            int from, to, cap;
            scanf("%d%d%d", &from, &to, &cap);
            add_edge(2 * i, from, to, cap);
        }
        int max_flow = 0;
        while (bfs())
            max_flow += dfs(1, 0x7fffffff);
        printf("Case %d: %d\n", t, max_flow);
    }
    return 0;
}

void add_edge(int index, int from, int to, int cap) {
    e.push_back(Edge(from,to,cap,0));
    e.push_back(Edge(to,from,0,0));
    g[from].push_back(index);
    g[to].push_back(index + 1);
}

int bfs() {
    queue<int> q;
    memset(level, 0, sizeof(level));
    q.push(1);
    level[1] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < (int)g[x].size(); i++) {
            Edge &edge = e[g[x][i]];
            if (!level[edge.to] && edge.cap > edge.flow) {//构建层次
                level[edge.to] = level[x] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[n];
}

int dfs(int x, int resident_flow) {
    int tmp = resident_flow;
    if (x == n)
        return resident_flow;
    for (int i = 0; i < (int)g[x].size(); i++) {
        Edge &edge = e[g[x][i]];
        if (level[edge.to] == level[x] + 1 && edge.cap - edge.flow) {//确保下一个残余流量不为0
            int t = dfs(edge.to, min(tmp, edge.cap - edge.flow));
            e[g[x][i]].flow += t;
            e[g[x][i] ^ 1].flow -= t;
            tmp -= t;
        }
    }
    return resident_flow - tmp;
}
