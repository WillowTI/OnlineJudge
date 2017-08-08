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
