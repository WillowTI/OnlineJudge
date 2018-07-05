/**
 * 从上往下n/2行的倒金字塔是等差数列
 * 从下往上n/2行的正金字塔是等差数列
 * 这些可以O(n)求出来
 * 剩下没有被金字塔覆盖的范围是从下往上的正金字塔的首位2个数字之和的前缀和
 * 以
 * 1  2  3  4
 * 12 13 14 5
 * 11 16 15 6
 * 10 9  8  7
 * 为例
 * 
 * 1  2  3  4
 *    13 14
 *    16 15
 * 10 9  8  7
 * 是等差数列
 * 12+5=11+6=10+7
 *
 * 关于前缀和以5阶为例
 * 2，4行=5行等差数列首位2个数字之和
 * 3行=5行等差数列首位2个数字之和+4行等差数列首位2个数字之和
 * 最后分奇偶讨论输出
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const LL MAXN = 2e5+5;
LL a[MAXN];
vector<LL> ps;
void calc(LL n, LL idx, LL s) {
    LL start = s;
    LL step = n;
    LL first = (2 * start + step - 1) * step / 2;
    LL second = (2 * start + 5 * (step - 1)) * step / 2;
    LL mid = 2 * start + 5 * (step - 1);
    a[idx] += first;
    if (n != 1) {
        a[idx + n - 1] += second;
        if (n != 2) {
            ps.emplace_back(ps[ps.size() - 1] + mid);
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    LL step;
    ps.emplace_back(0);
    scanf("%lld", &step);
    LL in = step;
    LL i, n;
    i = 0;
    n = 1;
    while (step > 0) {
        calc(step, i, n);
        n += 4 * (step - 1);
        step -= 2;
        i++;
    }
    if (in & 1) {
        FOR (j, 0, in / 2 + 1) {
            printf("%lld\n", a[j] + ps[j]);
        }
        FOR (j, in / 2 + 1, in) {
            printf("%lld\n", a[j] + ps[in - 1 - j]);
        }
    } else {
        FOR (j, 0, in / 2) {
            printf("%lld\n", a[j] + ps[j]);
        }
        FOR (j, in / 2, in) {
            printf("%lld\n", a[j] + ps[in - 1 - j]);
        }
    }
    return 0;
}
