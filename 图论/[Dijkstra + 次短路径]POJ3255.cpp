#include "cstdio"
#include "cstring"
#include "algorithm"
#include "queue"
using namespace std;
typedef pair<int, int> P;
int n, r;
int dist[5005], dist2[5005];
struct edge {
    int to, cost;
    edge (int t, int c) {
        to = t;
        cost = c;
    }
};
vector<edge> G[5005];//不能用邻接矩阵，会超内存
void dijkstra();

int main() {
//    freopen("in.txt", "r", stdin);
    memset(dist, 0x7f, sizeof dist);
    memset(dist2, 0x7f, sizeof dist2);
    scanf("%d%d", &n, &r);
    for (int i = 0; i < r; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        G[x].push_back(edge(y, c));
        G[y].push_back(edge(x, c));
    }
    dijkstra();
    printf("%d\n", dist2[n]);
    return 0;
}

void dijkstra() {
    priority_queue<P, vector<P>, greater<P> > pq;
    pq.push(P(0, 1));
    dist[1] = 0;
    while (!pq.empty()) {
        P cur = pq.top();
        pq.pop();
        int v = cur.second;
        int d = cur.first;
//        if (d > dist[v]) continue;
//        如果是求最短路径可以加上这句话
//        但是次短路径不行，因为这样会导致某些值被跳过，最后结果就是无穷大
//        挑战的程序有误
        for (int i = 0; i < G[v].size(); i++) {
            edge& e = G[v][i];
            int d2 = d + e.cost;
            if (dist[e.to] > d2) {
                swap(dist[e.to], d2);//注意一定要swap，把次短路径交换出来
                pq.push(P(dist[e.to], e.to));
            }
            if (d2 < dist2[e.to] && d2 > dist[e.to]) {//更新次短路径
                dist2[e.to] = d2;
                pq.push(P(dist2[e.to], e.to));
            }
        }
    }
}