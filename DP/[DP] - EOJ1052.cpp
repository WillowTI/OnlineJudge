#include <stdio.h>
#include <string.h>
int weight[100005];
int val[100005];
int dp[100005];//dp[i]是背包容量为i时的最大价值
int n, maxweight;
int main()
{
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &maxweight);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &weight[i], &val[i]);
        for (int i = 1; i <= n; i++)//遍历每个物品
            for (int j = maxweight; j >= 0; j--)//从后往前遍历背包大小。如果从前往后的话会导致一个物品被重复放入
                if (j >= weight[i])
                    dp[j] = dp[j] > dp[j - weight[i]] + val[i] ? dp[j] : dp[j - weight[i]] + val[i];
                    //更新为(当前最大价值)和(未放入当前物品的最大价值与物品价值之和)的最大值
        printf("%d\n", dp[maxweight]);
    }
    return 0;
}
