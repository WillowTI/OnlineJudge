#include <bits/stdc++.h>
using namespace std;
int dp[105][105], cas, n, p, m, t;
//dp[x][y]代表在x分钟走到y有几种走法，这是由dp[x - 1][y - 1]和dp[x - 1][y + 1]相加得到的（如果合法的话）
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d%d", &n, &p, &m, &t);
        memset(dp, 0, sizeof(dp));
        if (p - 1 >= 1)
            dp[1][p - 1]++;
        if (p + 1 <= n)
            dp[1][p + 1]++;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                if (j - 1 >= 1) //如果合法就加上去
                    dp[i + 1][j - 1] += dp[i][j];
                if (j + 1 <= n)
                    dp[i + 1][j + 1] += dp[i][j];
            }
        }
        printf("%d\n", dp[m][t]);
    }
    return 0;
}
