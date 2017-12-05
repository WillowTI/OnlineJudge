非常巧妙的做法
把一个时间段涉及到的时间在数组里全部加一
最后答案就是这个数组里最大的元素

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
        int time[25]={0};
        scanf("%d" , &n);
        for (int i = 0 ; i < n ; i++)
        {
            int st , ed;
            scanf("%d%d" , &st , &ed);
            for (int j = st ; j <= ed ; j++)
            {
                time[j]++;
            }
        }
        int ans = -1;
        for (int i = 0 ; i < 25 ; i++)
        {
            ans = ans > time[i] ? ans : time[i];
        }
        printf("%d\n" , ans);
    }
    return 0;
}
