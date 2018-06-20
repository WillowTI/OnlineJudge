#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const int MAXN = 1e4+5;
const LL mod = 1e9+7;
LL n, t, k;
LL a[MAXN];
LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) {
            ret *= a;
            ret %= mod;
        }
        a *= a;
        a %= mod;
        b /= 2;
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        cin >> n >> t >> k;
        FOR (i, 0, n)
            scanf("%lld", a + i);
        LL offset = t % n;
        LL num = qpow(k, t);
        FOR (i, 0, n)
            printf("%lld%c", (a[(i - offset + n) % n] * num) % mod, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
