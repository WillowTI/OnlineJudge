/** 
 * 网上的做法是用dice[n][k]记录n个骰子和为k有多少种情况
 * 递推公式是dice[n][k] = dice[n - 1][k - 1] +...+ dice[n - 1][k - 6]
 * 意思是n个骰子和为k的情况是假设n - 1个骰子和为k - 1，第n个骰子为1
 * +...+假设n - 1个骰子和为k - 6，第n个骰子和为6（注意不一定是正好加6个，在计算的时候保证下标合法）
 * 这样结果正好为k
 * 但是这道题不允许这么做，因为在n=10的时候就已经爆int了，更不要说long long
 * 那就直接保存概率
 * 最终的公式是在原来记录情况个数的公式的基础上除以6
 * 预处理出所有的情况
 * 在O(1)的时间内直接输出答案
 * 程序设计基础都有防AK题了，爽到
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
double dice[2005][12005];
int n, k;
int main() {
    //freopen("in.txt", "r", stdin);
    for (int i = 1; i <= 6; i++)
        dice[1][i] = 1.0 / 6.0;
    for (int i = 2; i <= 2000; i++) {
        for (int j = i; j <= 6 * i; j++) {
            for (int k = j - 1; k >= j - 6 && k >= i - 1 && k >= 1; k--) {
                dice[i][j] += dice[i - 1][k];
            }
            dice[i][j] /= 6.0;
        }
    }
    scanf("%d%d", &n, &k);
    if (k >= n && k <= 6 * n)
        printf("%.6f\n", dice[n][k]);
    else
        printf("%.6f\n", 0.0);
    return 0;
}
