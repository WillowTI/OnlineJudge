/**
 * 看一遍是学不会的
 * 差分思想
 * c1记录差分
 * 但是光有c1还不够，c1只能保证算每个元素是O(log n)的
 * 算前缀和时需要用到另一个数组c2
 * c2[i] = (i - 1) * c1[i]
 * a1[1]+...+a[i] = i * sum(c1, i) - sum(c2, i)
 * 更新的时候保持同步
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
typedef long long LL;
using namespace std;
const int MAXN = 5e5+5;
LL c1[MAXN], c2[MAXN];
int n, q, op, l, r;
int lowbit(int x);
LL sum(LL* a, int x);
void update(LL* a, int x, LL v);

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    LL x, y = 0;
    FOR (i, 1, n + 1) {
        scanf("%lld", &x);
        update(c1, i, x - y);
        update(c2, i, (i - 1) * (x - y));
        y = x;
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &op);
        scanf("%d%d", &l, &r);
        if (op == 1) {
            LL tag;
            scanf("%lld", &tag);
            update(c1, l, tag);
            update(c1, r + 1, -tag);
            update(c2, l, (l - 1) * tag);
            update(c2, r + 1, r * -tag);
        } else {
            LL sum1 = (l - 1) * sum(c1, l - 1) - sum(c2, l - 1);
            LL sum2 = r * sum(c1, r) - sum(c2, r);
            printf("%lld\n", sum2 - sum1);
        }
    }
    return 0;
}

int lowbit(int x) {
    return x & -x;
}

LL sum(LL* a, int x) {
    LL ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ret += a[i];
    return ret;
}

void update(LL* a, int x, LL v) {
    for (int i = x; i <= n; i += lowbit(i))
        a[i] += v;
}