#include <cstdio>
#include <cstring>
#include <cstdlib>
int num[105], dp[105];//dp[i]记录了一定要把第i个数字加进去的话，最大的值是多少
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &num[i]);
        int ans = dp[0] = num[0];
        for (int i = 1; i < n; i++) {
            if (dp[i - 1] < 0)//如果前面的值是负的，那么再加上自身一定比自身小
                dp[i] = num[i];
            else
                dp[i] = dp[i - 1] + num[i];//否则，一定大于等于自身，可以加上
            ans = ans > dp[i] ? ans : dp[i];//答案就是遍历每个数字的情况
        }
        printf("%d\n", ans);
    }
    return 0;
}