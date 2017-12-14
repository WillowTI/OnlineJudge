#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define EPS 1e-8
using namespace std;
struct Point{
    double x, y;
    Point() {
        x = 0;
        y = 0;
    }
    Point (double x, double y) {
        this -> x = x;
        this -> y = y;
    }
    Point operator - (Point& a) {
        return Point(x - a.x, y - a.y);
    }
};
int n;
Point p[105];
double area(Point a, Point b);//用叉积计算面积，这里是分正面积和负面积的
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        double ans = 0;
        for (int i = 1; i < n - 1; i++)//以p[0]为起点，计算p[0] -> p[i]到p[0] -> p[i + 1]的面积
            ans += area(p[i] - p[0], p[i + 1] - p[0]);
        printf("%.1f\n", ans);
    }
    return 0;
}

double area(Point a, Point b) {
    return 0.5 * (a.x * b.y - a.y * b.x);
}
