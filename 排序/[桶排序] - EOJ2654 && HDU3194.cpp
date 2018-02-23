/**
 * sort的代价是nlogn，对这道题偏大了
 * 考虑到MOD小于40000，那桶排序扫一遍的代价也不是很大
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 1000005;
int a, b, m, n, x[MAXN], bucket[40005];
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d%d%d%d%d", &n, &a, &x[0], &b, &m) == 5) {
        memset(bucket, 0, sizeof(bucket));
        if (n == 1) {
            printf("%d\n", x[0]);
            continue;
        }
        for (int i = 1; i < n; i++)
            x[i] = (x[i - 1] * a + b) % m;
        for (int i = 0; i < n; i++)
            bucket[x[i]]++;
        int cnt = 0, target = n / 2 + 1;
        bool flag = 0;
        for (int i = 0; i < 40005; i++) {
            while (bucket[i]--) {
                cnt++;
                if (cnt == target) {
                    printf("%d\n", i);
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
    }
    return 0;
}

