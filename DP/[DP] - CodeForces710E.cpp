/**
 * 当i是奇数的时候只有可能从i-1或者(i/2+1)*2-1
 * 如果是i/2*2+1，就相当于i-1，这就没有意义了
 */
#include "bits/stdc++.h"
#define FOR(i,a,b) for(int i=a;i<b;i++)
using namespace std;
const int MAXN = 1e7+5;
typedef long long LL;
LL num[MAXN];
LL n, x, y;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%lld%lld%lld", &n, &x, &y) == 3) {
        memset(num, 0, sizeof num);
        FOR (i, 1, n + 1) {
            if (i & 1) num[i] = min(num[i - 1] + x, num[i / 2 + 1] + y + x);
            else num[i] = min(num[i - 1] + x, num[i / 2] + y);
        }
        printf("%lld\n", num[n]);
    }
    return 0;
}