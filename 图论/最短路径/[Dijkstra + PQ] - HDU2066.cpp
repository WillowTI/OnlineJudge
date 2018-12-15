/**
 * 看到 Robin 在出题，在这道题的基础上修改，就顺手做了
 * 有 1E3 个点，用 Floyd 肯定超时，用 O(V^2) 的 Dijkstra 也会超时
 * 所以采取用优先级队列的 Dijkstra 
 * 模板采用挑战上的
 * 求出 s 个源点到其他点的最短距离后，遍历 d 个目的地，遍历耗时 O(s * d)
 * 总复杂度 O(VlogV + s * d)
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (int)(b); (i)++)
#define DFOR(i, a, b) for (int (i) = (a); (i) > (int)(b); (i)--)
#define EPS 1e-6
const int MAXN = 1e3+5;
using namespace std;
typedef long long LL;
struct edge {int to, cost;};
typedef pair<int, int> P;
vector <edge> G[MAXN];
int mind[MAXN][MAXN];
int sourse[MAXN], dest[MAXN];

void go(int s) {
    priority_queue<P, vector<P>, greater<P> > que;
    memset(mind[s], 0x3f, sizeof(mind[s]));
    mind[s][s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if (mind[s][v] < p.first) continue;
        FOR (i, 0, G[v].size()) {
            edge e = G[v][i];
            if (mind[s][e.to] > mind[s][v] + e.cost) {
                mind[s][e.to] = mind[s][v] + e.cost;
                que.push(P(mind[s][e.to], e.to));
            }
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    int t, s, d;
    while (scanf("%d%d%d", &t, &s, &d) == 3) {
        FOR (i, 0, MAXN) G[i].clear();
        FOR (i, 0, t) {
            int a, b, c;
            cin >> a >> b >> c;
            edge e1, e2;
            e1.to = b;
            e1.cost = e2.cost = c;
            e2.to = a;
            G[a].push_back(e1);
            G[b].push_back(e2);
        }

        FOR (i, 0, s) cin >> sourse[i];
        FOR (i, 0, d) cin >> dest[i];
        FOR (i, 0, s) go(sourse[i]);

        int ans = 0x3f3f3f3f;
        FOR (i, 0, s)
            FOR (j, 0, d)
                ans = min(ans, mind[sourse[i]][dest[j]]);

        cout << ans << endl;
    }
    return 0;
}