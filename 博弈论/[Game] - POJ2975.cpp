/**
 * 对任意的当前状态S，只需将某堆石头a[i]变为S^a[i]即可使得整个局面的SG值为0，即变为必败态。
 * 而且应当有S^a[i]<a[i]
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
int piles[1005];
int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    while (scanf("%d", &n) && n) {
        int ans = 0, sum = 0;
        for (int i = 0; i < n; i++)
            scanf("%d", &piles[i]);
        for (int i = 0; i < n; i++)
            sum ^= piles[i];
        if (!sum)
            puts("0");
        else {
            for (int i = 0; i < n; i++)
                if ((sum ^ piles[i]) < piles[i])
                    ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}
