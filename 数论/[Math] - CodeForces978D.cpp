/**
 * 给定1e5个数字
 * 每个数字只能+1，-1，不动
 * 问最少修改多少个数字能让数列是等差数列，数列仍按照输入顺序
 *
 * 枚举首位2个元素3*3=9种情况，然后计算中间数字要修改几次，去最小值
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const int MAXN = 1e5+5;
int a[MAXN];
int n;

int go(int diff, int add);

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    FOR (i, 0, n)
        scanf("%d", a + i);
    int ans = 0;
    if (n > 2) {
        ans = 0x3f3f3f3f;
        FOR (i, -1, 2) {
            FOR (j, -1, 2) {
                int b1 = a[0] + i;
                int b2 = a[n - 1] + j;
                int diff = b2 - b1;
                if (diff % (n - 1)) continue;
                diff /= (n - 1);
                int tmp = 0;
                if (i) tmp++;
                if (j) tmp++;
                int solve = go(diff, i);
                if (solve == -1) continue;
                tmp += solve;
                ans = min(ans, tmp);
            }
        }
        if (ans == 0x3f3f3f3f) ans = -1;
    }
    cout << ans;
    return 0;
}

int go(int diff, int add) {
    int ret = 0;
    FOR (i, 1, n - 1) {
        if (a[i] != a[0] + add + i * diff) {
            if (abs(a[i] - (a[0] + add + i * diff)) <= 1) ret++;
            else return -1;
        }
    }
    return ret;
}