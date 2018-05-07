/**
 * 离散化处理
 * 输入保证数字都是不相同的，所以不用去重
 * 每次读入要更新，答案加上比当前数字大的个数
 * 但是直接统计大的不方便，就用当前读入的所有数字个数-比当前数字小的个数
 * 树状数组维护前缀和比较方便
 */
#include "cstdio"
#include "cstring"
#include "algorithm"
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
using namespace std;
typedef long long LL;
const int MAXN = 5e5+5;
struct Point {
    int val, index;
    Point(){}
    Point(int v, int i):
            val(v), index(i){}
    bool operator < (const Point p) const {
        return val < p.val;
    }
};
int n, a[MAXN], C[MAXN];
Point p[MAXN];
int lowbit(int x);
void update(int x, int v);
LL sum(int x);
int main() {
//    freopen("in.txt", "r", stdin);
    int val;
    while (scanf("%d", &n) && n) {
        memset(C, 0, sizeof C);
        FOR (i, 1, n + 1) {
            scanf("%d", &val);
            p[i] = Point(val, i);
        }
        sort(p + 1, p + n + 1);
        FOR (i, 1, n + 1)
            a[p[i].index] = i;
        LL ans = 0;
        FOR (i, 1, n + 1) {
            update(a[i], 1);
            ans += i - sum(a[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

int lowbit(int x) {
    return x & -x;
}

void update(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        C[i] += v;
}

LL sum(int x) {
    LL ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += C[i];
    return ans;
}