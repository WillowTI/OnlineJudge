/**
 * 第一种做法是从下往上，最常见的
 */
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "algorithm"
#include "iostream"
#define FOR(i, a, b) for (int (i)=(a); (i)<(b); (i)++)
#define DFOR(i, a, b) for (int (i)=(a); (i)>(b); (i)--)
using namespace std;
typedef long long LL;

const int MAXN = 355;
int a[MAXN][MAXN];
int n;
int dp[MAXN][MAXN];

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    FOR (i, 0, n) {
        FOR (j, 0, i + 1) {
            scanf("%d", &a[i][j]);
        }
    }
    FOR (i, 0, n)
        dp[n - 1][i] = a[n - 1][i];
    DFOR (i, n - 1, -1) {
        FOR (j, 0, i + 1)
            dp[i][j] = a[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
    }
    cout << dp[0][0] << endl;
    return 0;
}

/**
 * 第二种是从上往下
 * dp[i][j]代表到第i行第j列的数字的最大权值和
 * dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j])
 * 如果下标可以访问的话
 */
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "algorithm"
#include "iostream"
#define FOR(i, a, b) for (int (i)=(a); (i)<(b); (i)++)
#define DFOR(i, a, b) for (int (i)=(a); (i)>(b); (i)--)
using namespace std;
typedef long long LL;

const int MAXN = 355;
int a[MAXN][MAXN];
int n;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    FOR (i, 0, n) {
        FOR (j, 0, i + 1) {
            scanf("%d", &a[i][j]);
        }
    }
    FOR (i, 1, n) {
        FOR (j, 0, i + 1) {
            int o = 0;
            if (j - 1 >= 0) o = a[i - 1][j - 1];
            if (j <= i) o = max(o, a[i - 1][j]);
            a[i][j] += o;
        }
    }
    int ans = a[n - 1][0];
    FOR (i, 0, n)
        ans = max(ans, a[n - 1][i]);
    cout << ans << endl;
    return 0;
}