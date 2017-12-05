#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define EPS 1e-8
using namespace std;
struct Point{
    double x, y;
    Point (double x = 0, double y = 0):x(x), y(y) {};
    Point operator + (Point a) {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (Point a) {
        return Point(x - a.x, y - a.y);
    }
    bool operator < (Point a) {
        if (fabs(y - a.y) <= EPS)
            return x < a.x;
        return y < a.y;
    }
};
Point p[105], res[105];
int n;
double dis(Point a, Point b);
int cross_product(Point a, Point b);
void Graham();
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        if (n == 1) {
            printf("0.00\n");
            continue;
        }
        if (n == 2) {
            printf("%.2f\n", dis(p[0], p[1]));
            continue;
        }
        Graham();
        double ans = 0;
        for (int i = 0; i < n - 1; i++)
            ans += dis(res[i + 1], res[i]);
        printf("%.2f\n", ans);
    }
    return 0;
}

double dis(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Graham() {
    sort(p, p + n);
    //y小，x小，所以p[0]和p[n-1]一定属于凸包
    res[0] = p[0];
    res[1] = p[1];
    int top = 1;
    for (int i = 2; i < n; i++) {//从前往后，获得从p[0]到p[n-1]逆时针半圈的凸包点集
        while (top >= 1 && cross_product(p[i] - res[top - 1], res[top] - res[top - 1]) >= 0)
            top--;
        res[++top] = p[i];
    }
    int m = top;
    for (int i = n - 2; i >= 0; i--) {
            //i从n-2或者n-1开始都可以，问题不大
            //但是top >  m一定是严格大于，如果取等号的话，可能会把p[n-1]出栈，那就出事了
        while (top >  m && cross_product(p[i] - res[top - 1], res[top] - res[top - 1]) >= 0)
            top--;
        res[++top] = p[i];
    }
    n = top + 1;
}

int cross_product(Point a, Point b) {
    double res = a.x * b.y - a.y * b.x;
    if (fabs(res) < EPS)
        return 0;
    else if (res > 0)
        return 1;
    return -1;
}
