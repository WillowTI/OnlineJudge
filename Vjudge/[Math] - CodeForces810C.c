题意：
给定n个数
对于这整个大集合求出其每一个非空集合的(max - min)
求和结果模1000000007

分析：
对于数列x1 , x2 , x3 , ...... , xn
可以得每个元素可记为(xj - xi) * 2 ^ (j - i - 1)的形式 (0 <= i < j  < n)
但是这就是一个二重循环
n ^ 2 / 2级别的复杂度
一定会超时
受金恺翔的启发（题目是求和的式子要拆开来，题目是分开的式子就合起来）
把这个求和式子拆开来
写成xi * (2 ^ i - 1)求和
-xi * (2 ^ (n - i -1) - 1)求和
减法的同模需要(ans + MOD) % MOD
避免出现负号
这样就把n ^ 2 / 2 转化为 2 * n的复杂度



#include <stdio.h>
#include <stdlib.h>

const long long MOD = 1000000007;
int n;
long long num[300005];
long long exp[300005];

int cmp(const void * a , const void * b);

int main()
{
    //freopen("input.txt" , "r" , stdin);
    //freopen("output.txt" , "w" , stdout);
    exp[0] = 1;
    for (int i = 1 ; i <= 300002 ; i++)
        exp[i] = (exp[i - 1] * 2) % MOD;
    scanf("%d" , &n);
    for (int i = 0 ; i < n ; i++)
        scanf("%I64d" , &num[i]);
    qsort(num , n , sizeof(long long) , cmp);
    long long ans = 0;
    for (int i = 0 ; i < n ; i++)
    {
        ans += (((exp[i] - 1) * num[i]) % MOD);
        ans %= MOD;
    }
    for (int i = 0 ; i < n ; i++)
    {
        ans += MOD;
        ans -=(((exp[n - i - 1] - 1) * num[i]) % MOD);
        ans %= MOD;
    }
    printf("%I64d\n" , ans);
    return 0;
}

int cmp(const void* a, const void* b)
{
    long long a1 = *(long long *)a;
    long long b1 = *(long long *)b;
    if (a1 < b1)
        return -1;
    else
        return 1;
}
