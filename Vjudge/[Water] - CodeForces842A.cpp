题意：
给定5个数l, r, x, y, k
求在l, r之间和x, y之间是否存在一组数字a, b
使得a/b等于k
k是整数

分析：
两个范围都达到了10 ^ 7
二重循环一定会超时
那就让b从x开始到y遍历
a相应地，从x * k开始到y * k
看是否存在一个a落在l, r之间
这样就降低到10 ^ 7


#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

ll l, r, x, y, k;

int exam();

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%lld%lld%lld%lld%lld", &l, &r, &x, &y, &k);
    double MIN = (double)l / y;
    double MAX = (double)r / x;
    if (k < MIN || k > MAX)
        puts("NO");
    else
    {
        if (exam())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

int exam()
{
    ll st = x * k;
    for (ll i = x; i <= y; i++, st += k)
    {
        if (st >= l && st <= r)
            return 1;
    }
    return 0;
}
