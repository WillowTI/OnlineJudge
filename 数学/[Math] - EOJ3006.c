Description 

给定一个多项式 (ax+by)k，计算多项式展开后 xnym 项的系数。

Input 

第1行：一个整数T（1≤T≤100000）为问题数。

接下来共T行。每行5个整数，分别为a，b，k，n，m，整数之间由一个空格分隔。

0≤k≤1,000,000，0≤n,m≤k，且n+m=k，0≤a,b≤10^9。

Output 

对于每个问题，输出一行问题的编号（0开始编号，格式：case #0: 等）。

然后对应每个问题在一行中输出一个整数，表示所求的系数（这个系数可能很大，输出对1000000007取模后的值）。

Sample Input 

3

1 1 3 1 2

235823 382573 999 111 888

681692776 714636914 287579 7786 279793

Sample Output 

case #0:

3

case #1:

939550478

case #2:

388290460


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
 
const long long MOD=1000000007;
int fact[10000007]={0};//用于存放阶乘，避免算组合数时要一一计算
                       //只能用int，否则用long long会超内存
long long quickpow(long long a,long long b)//快速幂，原理是化指数为二进制，减少时间复杂度
{
    long long r=1,base=a;
    while(b!=0)
    {
        if(b%2)
        {
            r*=base;
            r%=MOD;
        }
        base*=base;
        base%=MOD;
        b/=2;
    }
    return r;
}
 
int main()
{
    fact[0]=1;
    for (int i=1;i<10000007;i++)//计算阶乘
    {
        long long tmp=(long long)fact[i-1]*i;
        tmp%=MOD;
        fact[i]=(int)tmp;
    }
    int cas;
    scanf("%d",&cas);
    for (int t=0;t<cas;t++)
    {
        long long a,b,k,n,m;
        scanf("%I64d%I64d%I64d%I64d%I64d",&a,&b,&k,&n,&m);
        printf("case #%d:\n",t);
        if (a==0&&b==0&&k==0&&n==0&&m==0)//这种情况很迷，从数学上说，0^0是没有定义的，但是这里数据范围包括了这种情况，所以就单独考虑了
        {
            printf("0\n");
        }
        else//按照二项式展开的公式计算系数
        {
            long long ans=1;
            long long min=n<m?n:m;
            ans*=quickpow(a,n);
            ans*=quickpow(b,m);//用快速幂计算a^n和b^m
            ans%=MOD;
            long long factup=fact[k];
            long long factdown=fact[min];
            factdown*=fact[k-min];
            factdown%=MOD;//算出分子，分母
            long long ie=quickpow(factdown,MOD-2);//除法的同余，a/b和a*(b)^-1是同余的
                                                  //根据费马小定理算出b的逆元
            ans*=factup;
            ans%=MOD;
            ans*=ie;
            ans%=MOD;
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
