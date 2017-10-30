#include <cstdio>
#include <cstring>
int tower[105][105];//保存输入的数据
bool dp[105][105][10];//记录以(i,j)为起点，能不能使得答案为k
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        int n;
        scanf("%d", &n);
        memset(tower, 0, sizeof(tower));
        memset(dp, false, sizeof(dp));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= i; j++)
                scanf("%d", &tower[i][j]);
        for (int i = 1; i <= n; i++)
            dp[n][i][tower[n][i] % 10] = true;//以最后一行为起点，一定能到达本身个位数的值
        for (int i = n - 1; i > 0; i--)//自底向上更新
            for (int j = 1; j <= i; j++)
                for (int k = 0; k < 10; k++)
                    if (dp[i + 1][j][k] || dp[i + 1][j + 1][k])//只要子节点中有一个能到达k就更新自身的信息
                        dp[i][j][(k + tower[i][j]) % 10] = true;
        for (int i = 9; i >= 0; i--)
            if (dp[1][1][i]) {//以(1,1)为起点，从终点9开始往前遍历，能到达的第一个就是最大的
                printf("%d\n", i);
                break;
        }
    }
    return 0;
}
