Given a fraction a/b, write it as a sum of different Egyptian fraction. For example, 2/3 = 1/2 + 1/6.
There is one restriction though: there are k restricted integers that should not be used as a denominator.
For example, if we can’t use 2..6, the best solution is:
2/3 = 1/7 + 1/9 + 1/10 + 1/12 + 1/14 + 1/15 + 1/18 + 1/28
The number of terms should be minimized, and then the large denominator should be minimized.
If there are several solutions, the second largest denominator should be minimized etc.
Input
The first line contains the number of test cases T (T ≤ 100). Each test case begins with three integers
a, b, k (2 ≤ a < b ≤ 876, 0 ≤ k ≤ 5, gcd(a, b) = 1). The next line contains k different positive integers
not greater than 1000.
Output
For each test case, print the optimal solution, formatted as below.
Extremely Important Notes
It’s not difficult to see some inputs are harder than others. For example, these inputs are very hard
input for every program I have:
596/829=1/2+1/5+1/54+1/4145+1/7461+1/22383
265/743=1/3+1/44+1/2972+1/4458+1/24519
181/797=1/7+1/12+1/2391+1/3188+1/5579
616/863=1/2+1/5+1/80+1/863+1/13808+1/17260
22/811=1/60+1/100+1/2433+1/20275
732/733=1/2+1/3+1/7+1/45+1/7330+1/20524+1/26388
However, I don’t want to give up this problem due to those hard inputs, so I’d like to restrict the
input to “easier” inputs only. I know that it’s not a perfect problem, but it’s true that you can still
have fun and learn something, isn’t it?
Some tips:
1. Watch out for floating-point errors if you use double to store intermediate result. We didn’t use
double.
2. Watch out for arithmetic overflows if you use integers to store intermediate result. We carefully
checked our programs for that.
Sample Input
5
2 3 0
19 45 0
2 3 1 2
5 121 0
5 121 1 33
Sample Output
Case 1: 2/3=1/2+1/6
Case 2: 19/45=1/5+1/6+1/18
Case 3: 2/3=1/3+1/4+1/12
Case 4: 5/121=1/33+1/121+1/363
Case 5: 5/121=1/45+1/55+1/1089

翻译：
给定分子、分母、k个禁止使用的分母。
把这个分数拆分成若干个1/x相加的形式。
当有多组解时，确保拆分后分数的个数要最小。
如果个数相同，最大分母要最小。
如果最大分母相同，第二大分母要最小，以此类推。

分析：
首先要拆分后分数的个数最小，那就从1个，2个往上试，总能找到解。
再寻找最优解。把个数记为maxdep，通过DFS找出所有由maxdep个分数组成的解，在这些解中根据要求在寻找最优解。

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ll long long

ll a,b,maxdep,forbidnum,ans[1005],temp[1005],forbid[10];
int flag;//用于记录有没有在当前深度下做出第一个解

ll max(ll a,ll b);
ll gcd(ll a,ll b);
int find(ll a);//判断这个数字是不是禁止使用的
int better();//判断当前解是不是更优的
void DFS(int curdep,ll a,ll b);

int main()
{
    int cas;
    scanf("%d",&cas);
    for (int t=0;t<cas;t++)
    {
        scanf("%lld%lld%lld",&a,&b,&forbidnum);
        for (int i=0;i<forbidnum;i++)
        {
            scanf("%lld",&forbid[i]);
        }

        for (maxdep=0;;maxdep++)
        {
            flag=0;
            DFS(0,a,b);
            if (flag) break;
        }

        printf("Case %d: %lld/%lld=",t+1,a,b);
        for (int i=0;i<=maxdep;i++)
        {
            printf("1/%lld%c",ans[i],i==maxdep?'\n':'+');
        }
    }
    return 0;
}

ll max(long long a, long long b)
{
    return a>b?a:b;
}

ll gcd(long long a, long long b)
{
    return b==0?a:gcd(b,a%b);
}

int find(long long a)
{
    for (ll i=0;i<forbidnum;i++)
    {
        if (a==forbid[i])
            return 1;
    }
    return 0;
}

int better()
{
    for (int i=maxdep;i>=0;i--)//从后往前遍历当前做出来的解
    {
        if (ans[i]!=temp[i])//直到找到不同的数字
        {
            if (temp[i]<ans[i]) return 1;//如果当前解的数字更小，说明此解更好
            else return 0;
        }
    }
    return 0;
}

void DFS(int curdep, long long a, long long b)
{
    if (curdep==maxdep)//当达到最大深度时
    {
        if (a!=1||find(b)) return ;//如果分子不是1，说明还要更大的深度来拆分，不行（之所以用1来判断是因为更新分数的时候就约分过了）。
                                                //如果分子是1，但是分母不合法，也不行
        temp[curdep]=b;//合法时把b添加到temp数组中
        if (flag==0||better()) memcpy(ans,temp,sizeof(ll)*(curdep+1));//如果是在深度下做出第一个解或者这个解更好，那就把原来的解替换掉
        flag=1;//说明此时做出解来了
        return ;
    }
    ll tmp,a1,b1;
    ll start;
    if (curdep==0) start=b/a;
    else start=max(b/a,temp[curdep-1]);//起始分母拆分点是b/a和上一个拆分分母的最大值。b/a是把要拆的a/b化为(1/(b/a))。
    for (ll i=start+1;;i++)//一定要加一，因为要保证所有的分母是单调递增的
    {
        if ((maxdep-curdep+1)*b<=a*i) break;//剪枝，或者叫估价函数。maxdep-curdep+1是还能用几个拆分分数，如果这些分数都是最大的1/i还不行的话就说明不行。
                                                                        //写成数学就是a/b>=(maxdep-curdep+1)*1/i，通分后分子就是(maxdep-curdep+1)*b<=a*i
                                                                        //既然这样的，或者说之前的拆分方法是行不通的，那就退出，找其他的方法
        if (find(i)) continue;//如果这个数字是禁止的那就继续往上找
        a1=a*i-b;//当过了前面两个条件后说明当前数字是合法的，那就更新分子分母。a/b-1/i，通分后是(a*i-b)/(b*i)。
        b1=b*i;
        tmp=gcd(a1,b1);//约分
        temp[curdep]=i;//把i添加到当前答案数组中
        DFS(curdep+1,a1/tmp,b1/tmp);//递归寻找下一个数字
    }
}
