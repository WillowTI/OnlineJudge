质因数分解
对于一个数n
从2开始往上遍历
如果遇到能被n整除的数那就添加到答案数组里
再从2开始遍历
这个数确保一定是质数
因为是递增的遍历的
小的数是大的数的因数
而数越小越容易被整除
既然连小的数字都不能被整除
那么遍历得到的能被整除的数一定没有因数

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main()
{
    //freopen("input.txt" , "r" , stdin);
    int cas;
    scanf("%d" , &cas);
    for (int t = 0 ; t < cas ; t++)
    {
        int n;
        scanf("%d" , &n);
        printf("%d=" , n);
        int ans[10000]={0};
        int pos = 0;
        int i = 2;
        while (i * i <= n)
        {
            if (n % i ==0)
            {
                ans[pos++] = i;
                n /= i;
                i = 1;
            }
            i++;
        }
        ans[pos++] = n;
        for (int j = 0 ; j < pos ; j++)
            printf("%d%c" , ans[j] , j == pos - 1 ? '\n' : '*');
    }
    return 0;
}
