/**
 * 把男兵和女兵看成点，把之间的关系看成边
 * 由于优先考虑值大的关系，所以实际上是最大生成树
 * 挑战上的做法是全部乘-1，这样又转化为最小生成数了，这无所谓，本质上一样的
 * 结果是原始的代价减去生成树的权之和
 * 关系只能用一次，所以可能会有所有点不全部连通的情况，这也没关系了
 */
#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "cmath"
#include "vector"
#include "algorithm"
using namespace std;
const int MAXN = 1e4+5;
struct edge {
    int a1, a2, dis;
    edge(){}
    edge(int a, int b, int d):
            a1(a), a2(b), dis(d){}
    bool operator < (const edge& o) const {
        return dis < o.dis;
    }
};
vector<edge> e;
int par[2*MAXN+5];
int a1, a2, d;
int kruscal(int r);
int dsu_find(int x);
void dsu_union(int x, int y);
int main() {
//    freopen("in.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, r;
        scanf("%d%d%d", &n, &m, &r);
        e.clear();
        e.resize(r);
        for (int i = 0; i < 2*MAXN+5; i++)
            par[i] = i;
        for (int i = 0; i < r; i++) {
            scanf("%d%d%d", &a1, &a2, &d);
            e[i] = edge(a1, MAXN + a2, d);
        }
        sort(e.begin(), e.end());
        printf("%d\n", 10000 * (n + m) - kruscal(r));
    }
    return 0;
}

int kruscal(int r) {
    int ret = 0;
    for (int i = r - 1; i >= 0; i--) {
        int a1 = dsu_find(e[i].a1);
        int a2 = dsu_find(e[i].a2);
        if (a1 == a2) continue;
        ret += e[i].dis;
        dsu_union(a1, a2);
    }
    return ret;
}

int dsu_find(int x) {
    return x == par[x] ? x : par[x] = dsu_find(par[x]);
}

void dsu_union(int x, int y) {
    par[x] = y;
}