题意：
给定n个数（n <= 15）从中选若干个不同的数
l <= sum <= r
而且最大的数与最小的数之差不大于x

二进制枚举
对于每一种情况判断是否符合题意
反正也就2 ^ 15
时间绝对够
水的嘛就不谈了

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

int n , l , r , x;
int difficulty[20];

int main()
{
    //freopen("input.txt" , "r" , stdin);
    scanf("%d%d%d%d" , &n , &l , &r , &x);
    for (int i = 0 ; i < n ; i++)
        scanf("%d" , &difficulty[i]);
    int ans = 0;
    int MAX = (int)pow(2 , n);
    for (int i = 0 ; i <MAX ; i++)
    {
        int tmp = i;
        int curall = 0;
        int curmin = 1000005;
        int curmax = 0;
        for (int j = 0 ; j < n ; j++)
        {
            if (tmp % 2)
            {
                curmin = min(curmin , difficulty[j]);
                curmax = max(curmax , difficulty[j]);
                curall += difficulty[j];
            }
            tmp /= 2;
        }
        if (curall >= l && curall <= r && curmax - curmin >= x)
            ans++;
    }
    printf("%d\n" , ans);
    return 0;
}
