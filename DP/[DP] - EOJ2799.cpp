#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int cost[305][305], dp[305][305];
//cost[i][j]记录从i覆盖到j的最小花费
//dp[i][j]记录在前i个数字里覆盖j个数字的最小花费
int n, m, k;
void floyd();
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    for (int t = 0; t < cas; t++) {
        for (int i = 0; i < 305; i++)
            for (int j = i; j < 305; j++)
                cost[i][j] = 0xfffff;//初始化为无穷大
        for (int i = 0; i < 305; i++)
            for (int j = 0; j <= i + 1; j++)
                dp[i][j] = j == 0 ? 0 : 0xfffff;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            for (int st = a; st <= b; st++)
                for (int ed = st; ed <= b; ed++)
                    cost[st][ed] = min(cost[st][ed], c);
        }
        floyd();//求最小花费
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = dp[i - 1][j];//先初始化为前i-1个数里覆盖j个数的花费
                                        //注意i=j时是全部覆盖，这时候会访问到(i-1,j)，显然是不合法的，所以一定是无穷大
                for (int t = 1; t <= j; t++) {//遍历比较所有包括第i个数的情况，总共覆盖j个数，所以t最大就是j
                    if (cost[i - t + 1][i] != 0xfffff) {
                        dp[i][j] = min(dp[i][j], dp[i - t][j - t] + cost[i - t + 1][i]);//前i-t个数里覆盖j-t个的最优解加上后面连续t个数的花费之和
                    }
                }
            }
        }
        printf("case #%d:\n", t);
        printf("%d\n", dp[n][k]);
    }
    return 0;
}

void floyd() {
    for (int k = 1; k < n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k + 1][j]);
                //细节问题：因为前面已经覆盖到k个了，所以后一个cost是从k+1开始
                //而最短路径是cost[i][k] + cost[k][j]，相当于以k为中转
}

