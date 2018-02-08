/**
 * 经典贪心策略
 * 一开始看错题目，WA了好几发
 * 然后弄明白了，按照正确的策略写，实现错了好几发，被自己蠢哭
 * 策略很简单，每次重量最小的先上船，然后把重量尽可能大的也一起上船，没有满足的就算了
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int cas, n, k, t, a[2005];
bool vis[2005];
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &k);
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        sort(a, a + n);
        int ans = 0, cnt = 0;
        for (int i = 0; cnt < n; i++) {
            if (vis[i]) continue;
            vis[i] = 1;
            int tail = n - 1;
            while (tail >= 0 && (vis[tail] || a[i] + a[tail] > k))
                tail--;
            if (tail >= 0) {
                vis[tail] = 1;
                cnt++;
            }
            cnt++;
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}