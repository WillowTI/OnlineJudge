#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n, m;
typedef struct {
    int x, y;
}Node;
Node in[1005];
double graph[1005][1005];//存储原始路径
double lowcost[1005] = {0};//记录已联通的点集合到其余点的最短路径
int mst[1005] = {0};//记录从哪个点出发到第i个点的路径最短，-1代表已加入联通点集
double prim();//从点的角度出发，寻找最近的点，和dijstra很像
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &in[i].x, &in[i].y);
    for (int i = 0; i < n; i++) {//预处理
        for (int j = i + 1; j < n; j++) {
            graph[i][j] = graph[j][i] = sqrt(pow(in[i].x - in[j].x, 2) + pow(in[i].y - in[j].y, 2));
        }
    }
    for (int i = 0; i < m; i++) {
        int id1, id2;
        scanf("%d%d", &id1, &id2);
        id1--;
        id2--;
        graph[id1][id2] = graph[id2][id1] = 0;
    }
    printf("%.2f\n", prim());
    return 0;
}

double prim() {//由于数据规模不大，可以用O(n^2)的方法遍历。可以考虑用priority_queue优化（事实上dijstra也可以用priority_queue优化）
    double ret = 0;
    for (int i = 0; i < n; i++) {//初始化为从0出发
        lowcost[i] = graph[0][i];
    }
    mst[0] = -1;
    for (int i = 1; i < n; i++) {//默认0已访问，所以遍历n - 1次
        double mn = (double)(1 << 30);
        int minid = 0;
        for (int j = 1; j < n; j++) {//寻找最近的点，并更新id
            if (lowcost[j] < mn && mst[j] != -1) {
                mn = lowcost[j];
                minid = j;
            }
        }
        ret += mn;
        lowcost[minid] = 0;
        mst[minid] = -1;//标记已访问
        for (int j = 1; j < n; j++) {
            if (graph[minid][j] < lowcost[j]) {//松弛操作，更新起点
                lowcost[j] = graph[minid][j];
                mst[j] = minid;//这一步其实可以省去，只要记录是否访问过就行了
            }
        }
    }
    return ret;
}
