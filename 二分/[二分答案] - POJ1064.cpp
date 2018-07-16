/**
 * 二分答案模板
 * 给定n根绳子，最后分成k根，求每根最大多长，保留2位小数
 * 注意最后输出要退一法，而不是四舍五入
 */
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "iostream"
#include "cmath"
#include "algorithm"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const double EPS = 1e-8;
const int MAXN = 1e4+5;
double a[MAXN];
int n, k;

bool go(double x) {
    int num = 0;
    FOR (i, 0, n) num += (int)(a[i] / x);
    return num >= k;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    double l = 0.0;
    double r = 0.0;
    FOR (i, 0, n) {
        scanf("%lf", a + i);
        r = max(r, a[i]);
    }
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (go(mid)) l = mid;
        else r = mid;
    }
    printf("%.2f\n", floor(r * 100) / 100);
    return 0;
}