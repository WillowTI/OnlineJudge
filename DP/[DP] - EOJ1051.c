#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LL long long
LL p[100];
LL m[55][55];
int n;
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        memset(m, 0, sizeof(m));
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lld%lld", &p[i], &p[i + 1]);
        LL ans = 0;
        for (int l = 2; l <= n; l++) {//l为当前链的长度
            for (int i = 1; i <= n - l + 1; i++) {//由于n-(n-l+1)+1=l，所以i的最大值就确定了
                int j = i + l - 1;//j是以i为起点，长度为l的区间的终点，j-i+1=l，j=i+l-1
                m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];//先把切割点设在i处
                for (int k = i + 1; k < j; k++) {//再从i + 1到j遍历切割点，取最小值，注意不能取j，因为会访问到j + 1的下标
                    LL tmp = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    m[i][j] = m[i][j] < tmp ? m[i][j] : tmp;
                }
            }
        }
        printf("%lld\n", m[1][n]);
    }
    return 0;
}
