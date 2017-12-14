#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define EPS 1e-8
using namespace std;
struct Point {
    double x, y;
    Point(){}
    Point(double x, double y) {
        this -> x = x;
        this -> y = y;
    }
    Point operator + (Point& a) {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (Point& a) {
        return Point(x - a.x, y - a.y);
    }
};
double amount;
int n_p, n_q, low_id_p, low_id_q;
//n是点数组的大小，low_id记录最低点的下标
double cp(Point a, Point b);
double calculate(double height, Point p[], int low_id, int sz);//计算多边形的面积
int main() {
    //freopen("in.txt", "r", stdin);
    Point p[1005], q[1005];
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        memset(p, 0, sizeof(p));
        memset(q, 0, sizeof(q));
        low_id_p = low_id_q = 0;
        scanf("%lf", &amount);
        scanf("%d", &n_p);
        for (int i = 0; i < n_p; i++) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            low_id_p = p[low_id_p].y < p[i].y ? low_id_p : i;
        }
        scanf("%d", &n_q);
        for (int i = 0; i < n_q; i++) {
            scanf("%lf%lf", &q[i].x, &q[i].y);
            low_id_q = q[low_id_q].y < q[i].y ? low_id_q : i;
        }
        double l = min(p[low_id_p].y, q[low_id_q].y);//最低点是2个水槽的最低点
        double r = min(p[0].y, min(p[n_p - 1].y, min(q[0].y, q[n_q - 1].y)));//最高点是2个水槽4个边界点的最低点
        while (fabs(l - r) >= EPS) {//二分高度，求多边形面积
            double m = (l + r) / 2;
            double area1 = calculate(m, p, low_id_p, n_p);
            double area2 = calculate(m, q, low_id_q, n_q);
            double sum = area1 + area2;
            if (sum - amount > 0)
                r = m;
            else
                l = m;
        }
        printf("%.3f\n", r);
    }
    return 0;
}

double cp(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double calculate(double height, Point p[], int low_id, int sz) {
    int i = 0, j = sz - 1;
    double ret = 0;
    while (i <= low_id && p[i].y > height) i++;
    while (j >= low_id && p[j].y > height) j--;
    if (i <= j) {//当height在水槽之下的时候，i > j
        //计算直线y=height与两边的交点
        Point a1 = Point(p[i].x - (p[i].x - p[i - 1].x) * (height - p[i].y) / (p[i - 1].y - p[i].y), height);
        Point a2 = Point(p[j].x + (p[j + 1].x - p[j].x) * (height - p[j].y) / (p[j + 1].y - p[j].y), height);
        for (int t = i; t + 1 <= j; t++) //以c1为向量起点计算多边形面积
            ret += cp(p[t] - a1, p[t + 1] - a1);
        ret += cp(p[j] - a1, a2 - a1);
    }
    return fabs(ret) / 2.0;
}
