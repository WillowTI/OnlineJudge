#include <cstdio>
#include <cstdlib>
#include <cstring>
int main()
{
    int val[55] = {0}, pre[55], a[55], n;
    //val记录以a[i]结尾的最长的满足要求的序列长度
    //pre记录以a[i]结尾的序列的倒数第二个元素的下标，-1为只有结尾一个元素
    //freopen("in.txt", "r", stdin);
    memset(pre, -1, sizeof(pre));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    if (n == 1)//单独判断长度为1和2的序列
        puts("1");
    else if (n == 2) {
        if (a[0] != a[1])
            puts("2");
        else
            puts("1");
    } else {
        //在寻求解的时候只看前面子序列的末尾2个元素，如果只有1个元素那就只看1个
        val[0] = 1;//单个元素的长度为1
        for (int i = 1; i < n; i++) {//在计算val[i]时穷举从0->i-1的所有情况，判断连在哪个i的情况下最好
                                    //当然从i-1->0遍历也是可以的
            for (int j = i - 1; j >= 0; j--) {
                if (pre[j] == -1) {//如果没有前趋元素
                    if (a[i] != a[j]) {//那只要看末尾元素和本身是否相等就行了
                        if (val[j] >= val[i]) {//如果能使长度更长就加上去，同时更新val和pre
                            val[i] = val[j] + 1;
                            pre[i] = j;
                        }
                    }
                } else {
                    if ((a[j] - a[pre[j]]) * (a[j] - a[i]) > 0) {//如果有前趋元素，那就判断加上去后是否是合法的
                        if (val[j] >= val[i]) {//如果加上能更优，那就加上并且更新相关信息
                            val[i] = val[j] + 1;
                            pre[i] = j;
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = ans > val[i] ? ans : val[i];
        printf("%d\n", ans);
    }
    return 0;
}
