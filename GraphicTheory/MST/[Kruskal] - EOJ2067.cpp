#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m, farmsz;//farmsz记录道路的数量
typedef struct {
    int id1, id2;
    double price;
}FARM;
typedef struct {
    int x, y;
}IN;
IN in[1005];
FARM farm[1000005];
int par[1005], Rank[1005];
bool cmp(FARM f1, FARM f2);//按照道路长度从小到大排序
int Find(int x);
void Union(int x, int y);
double kruskal();
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &in[i].x, &in[i].y);
        Rank[i] = 0;
        par[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int id1, id2;
        scanf("%d%d", &id1, &id2);
        id1--;
        id2--;
        Union(id1, id2);//把已联通的2个点合并
    }
    farmsz = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Find(i) != Find(j)) {//当2个点不属于同一集合时才更新为它们的点距离
                FARM f;
                f.id1 = i;
                f.id2 = j;
                f.price = sqrt(pow(in[i].x - in[j].x, 2) + pow(in[i].y - in[j].y, 2));
                farm[farmsz++] = f;
            }
        }
    }
    sort(farm, farm + farmsz, cmp);
    printf("%.2f\n", kruskal());
    return 0;
}

bool cmp(FARM f1, FARM f2) {
    if (f1.price < f2.price)
        return true;
    return false;
}

int Find(int x) {//路径压缩
    int root = x;
    while (root != par[root])
        root = par[root];
    while (x != root) {
        int t = par[x];
        par[x] = root;
        x = t;
    }
    return root;
}

void Union(int x, int y) {//按秩合并
    x = Find(x);
    y = Find(y);
    if (Rank[x] < Rank[y])
        par[x] = y;
    else {
        par[y] = x;
        if (Rank[x] == Rank[y])
            Rank[x]++;
    }
}

double kruskal() {
    double ret = 0;
    int edge = 0;//记录路的数量，最多n - 1条
    for (int i = 0; i < farmsz && edge < n; i++) {//从小到大遍历所有的路
        if (Find(farm[i].id1) != Find(farm[i].id2)) {//当一条路的2个端点不属于同一集合时再加入
            ret += farm[i].price;
            edge++;
            Union(farm[i].id1, farm[i].id2);//合并2个端点
        }
    }
    return ret;
}
