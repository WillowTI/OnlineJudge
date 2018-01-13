#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int dp[20][8200], n, s, a[20];
//dp[i][j]表示第i个人取，还有j块石头
//当j为0的时候，没有石头，这时候是胜，为1
int slove(int idx, int remain);//dfs搜索
int main() {
    //freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) && n) {
        scanf("%d", &s);
        for(int i = 0; i < 2 * n; i++)
            scanf("%d", &a[i]);
        memset(dp, -1, sizeof(dp));
        printf("%d\n", slove(0, s));
    }
    return 0;
}

int slove(int idx, int remain) {
    if(dp[idx][remain] != -1)//如果有过标记了就返回
        return dp[idx][remain];
    if(remain == 0)//如果没有剩余的石头，标记为1
        return dp[idx][remain] = 1;
    dp[idx][remain] = 0;//先默认标记为0
    for(int i = 1; i <= a[idx] && i <= remain; i++)
        if(!slove((idx+1) % (2 * n), remain - i))//只要存在一种取走i个石头后能赢的情况就标记为1
            dp[idx][remain] = 1;
    return dp[idx][remain];
}
