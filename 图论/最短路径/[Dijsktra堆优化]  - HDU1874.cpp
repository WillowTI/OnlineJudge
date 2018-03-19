#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "algorithm"
#include "queue"
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int INF = 0x7f7f7f7f;
int G[205][205];
int dis[205], n;
void dijkstra(int s);
int main() {
//    freopen("in.txt", "r", stdin);
    int m;
    while  (scanf("%d%d", &n, &m) == 2) {
        memset(G, 0x7f, sizeof G);
        memset(dis, 0x7f, sizeof dis);
        for (int i = 0; i < m; i++) {
            int x, y, dis;
            scanf("%d%d%d", &x, &y, &dis);
            G[x][y] = G[y][x] = min(dis, G[x][y]);
        }
        int from, to;
        scanf("%d%d", &from, &to);
        dijkstra(from);
        if (dis[to] == INF)
            puts("-1");
        else
            printf("%d\n", dis[to]);
    }
    return 0;
}

void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P> > pq;
    dis[s] = 0;
    pq.push(P(0, s));
    while (!pq.empty()) {
        P p = pq.top();
        pq.pop();
        int v = p.second;
        if (dis[v] < p.first)
            continue;
        for (int i = 0; i < n; i++) {
            if (dis[i] > dis[v] +G[v][i]) {
                dis[i] = dis[v] +G[v][i];
                pq.push(P(dis[i], i));
            }
        }
    }
}