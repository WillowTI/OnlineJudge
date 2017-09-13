题意：
给定n个数和k
求小于k的尽可能大的数字
使得这n + 1个数的GCD大于1
如果找不到这样的数字输出0

分析：
先求出n个数的GCD
如果GCD等于1
那么答案一定是0
否则把GCD分解质因数
答案是质因数的x倍


#include <cstdio>
#include <algorithm>

using namespace std;

int num[100005];
int factor[32000];
int pos = 0;
int n, k;

int gcd(int a, int b);

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    sort(num, num + n);
    int GCD = num[0];
    for (int i = 1; i < n; i++)
    {
        GCD = gcd(num[i], GCD);
        if (GCD == 1)
            break;
    }
    if (GCD == 1)
        printf("0\n");
    else
    {
        int st = 2;
        int first = 1;
        while (GCD != 1)//分解质因数的时候这里TLE一次，因为剩下的最后一个因数可能会很大，每次加一就会超时
        {
            if (st * st > GCD)
            {
                factor[pos++] = GCD;
                break;
            }
            else if (GCD % st == 0)
            {
                if (first)
                {
                    factor[pos++] = st;
                    first = 0;
                }
                GCD /= st;
            }
            else
            {
                st++;
                first = 1;
            }
        }
        int ans = -1;
        for (int i = 0 ; i < pos ; i++)
        {
            int tmp = k / factor[i] * factor[i];//找到最大的答案
            ans = ans > tmp ? ans : tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a %b);
}
