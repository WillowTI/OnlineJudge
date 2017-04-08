Description

求N的阶乘的最高位数。
例如：
5!=120,所以最高位为1
10!=3628800，所以最高位为3

Input

每个数据包含一行,每行有一个整数N(0<=N<=10000000)

Output

对于每个测试数据，输出N!的最高位数字

Sample Input

5
10

Sample Output

1
3


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define M_PI		3.14159265358979323846
#define M_E		2.7182818284590452354
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        if (n<=10)
        {
            int a[11]={1,1,2,6,2,1,7,5,4,3,3};//前几位不精确，需手动计算
            printf("%d\n",a[n]);
        }
        else
        {
            int ans=0;
            double lg=0.5 * log(2 * M_PI *(double)n) / log(10.0) + (double)n * log((double)n / M_E) / log(10.0);
            //用斯特林公式算出n!的大致数字，不必精确，用小数的形式保留下来。
            //注意：直接按照公式算，即用log10()函数会出现inf，必须用换底公式算底为e的对数
            //
            int tmp=(int)lg;
            lg-=tmp;//首位即为所求值
            ans=(int)(pow(M_E,lg*log(10.0)));
            printf("%d\n",ans);
        }
    }
    return 0;
}
