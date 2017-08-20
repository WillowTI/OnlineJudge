理解题意花了很长时间
给定洪水的体积和一些格子的高度
其实这里把洪水想象成降水量更好理解，所以后面全部改成雨水了
每个格子的面积都是10 * 10的
所以雨水的体积读进来后就可以除100
现在要求最后降水的高度和被淹没的建筑物的占比

从低到高排序
雨水先在降临在较低的建筑物上
当雨水在上面积累的高度达到后面比它高的建筑物时
雨水同时在这2座建筑物上积累
然后是连续3座、4座

注意建筑物的高度可能是负的
最后也可能一直积累到最高的建筑物时还有剩余的雨水
这时就会所有的建筑物一起积雨
这道题还要输出行末空行
和以往两个数据之间输出空行不一样


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a[905];
int n, m;

int main()
{
    //freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d%d", &m, &n) && n)
    {
        for (int i = 0 ; i < n * m ; i++)
            scanf("%d", &a[i]);
        double sum, high, per;
        scanf("%lf", &sum);
        sum /= 100;
        sort(a, a + m * n);
        for (int i = 1 ; i < n * m ; i++)
        {
            int tot = (a[i] - a[i - 1]) * i;
            if (sum >= tot)
                sum -= tot;
            else
            {
                high = a[i - 1] + sum / i;
                sum = 0;
                per = i * 1.0 / n / m;
                break;
            }
        }
        if (sum)
        {
            high = a[n * m - 1] + sum / n / m;
            per = 1;
        }
        printf("Region %d\n", cas++);
        printf("Water level is %.2f meters.\n", high);
        printf("%.2f percent of the region is under water.\n\n", per * 100);
    }
    return 0;
}
