/**
 * 分治的思想类似线段树，难点在于区间合并
 * 一个大区间的最近点对距离可以先算2个子区间的最近点对，再考虑mid附近的点对
 * 确定mid附近的点对的区间大小：距离mid的x不超过2个子区间的最近距离
 * 在这个区间里其实可以二重循环枚举点对
 * 但是这里还剪枝了，按照y的大小排序
 * 只要2个点的y相差超过先前算出来的值就结束对这个点的循环
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define INF 1 << 30
#define maxn 100000 + 5
using namespace std;
typedef struct {
    double x, y;
}Point;
Point p[maxn];
int n, mge[1000000 + 5];
bool cmp(Point a, Point b);
bool cmpy(int a, int b);
double dis(Point a, Point b);
double closest_pair(int l, int r);
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        sort(p, p + n, cmp);
        printf("%.2f\n", closest_pair(0, n - 1) / 2.0);
    }
    return 0;
}

bool cmp(Point a, Point b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

double dis(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closest_pair(int l, int r) {
    double ret = INF;
    if (l == r)
        return ret;
    if (l + 1 == r)
        return dis(p[l], p[r]);
    int m = (l + r) / 2;
    double d1 = closest_pair(l, m);
    double d2 = closest_pair(m + 1, r);
    ret = min(d1, d2);
    int pos = 0;
    for (int i = l; i <= r; i++)
        if (fabs(p[i].x - p[m].x) <= ret)
            mge[pos++] = i;
    sort(mge, mge + pos, cmpy);
    for (int i = 0; i < pos; i++)
        for (int j = i + 1; j < pos && p[mge[j]].y - p[mge[i]].y < ret; j++)
            ret = min(ret, dis(p[mge[i]], p[mge[j]]));
    return ret;
}

bool cmpy(int a, int b) {
    return p[a].y < p[b].y;
}
