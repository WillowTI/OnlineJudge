/**
 * 给n个数字和m
 * 每个数字可以分为若干组，至少1组
 * 所有组数之和等于m
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const int MAXN = 5e5+5;
int a[MAXN];
int n, m;
bool go(int mid) {
    int sum = 0;
    FOR (i, 0, n) {
        int c = (a[i] % mid) ? a[i] / mid + 1 : a[i] / mid;
        sum += c;
        if (sum > m) return false;
    }
    return true;
}

int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) && n != -1) {
        int l = 0x7ffffff, r = -1;
        FOR (i, 0, n) {
            scanf("%d", a + i);
            l = min(l, a[i]);
            r = max(r, a[i]);
        }
        l /= (m - n + 1);
        int ans = r;
        while (l < r) {
            int mid = (l + r) / 2;
            if (go(mid)) {
                ans = min(ans, mid);
                r = mid;
            } else
                l = mid + 1;
        }
        cout << ans << endl;
        //写到这里，ans就是正确答案了
        //但是后面多此一举把ans带入，演算，计算最终答案
        //这时要考虑整除问题
        /**
         * 
	        int out = -1;
	        FOR (i, 0, n) {
	            int c = (a[i] % ans) ? a[i] / ans + 1 : a[i] / ans;
	            int t = (a[i] % c) ? a[i] / c + 1 : a[i] / c;
	            out = max(out, t);
	        }
	        cout << out << endl;
         */
    }
    return 0;
}
