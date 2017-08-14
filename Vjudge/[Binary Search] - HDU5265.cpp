题意：
给定一串序列
输出其中两个数的和模p的最大值
分析：
最大值一定在最大的两个数之和
和满足两个数之和小于p的同时尽可能大的情况下出现
那么排序是不可能少的

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int n;
long long p;
long long num[100005];

int main()
{
    //freopen("input.txt" , "r" , stdin);
    while (scanf("%d%I64d" , &n , &p) == 2)
    {
        for (int i = 0 ; i < n ; i++)
        {
            scanf("%I64d" , &num[i]);
            num[i] %= p;//读进来的时候就模p
        }
        sort(num , num + n);
        long long MAX = num[n - 1] + num[n - 2];//第一种情况
        if (MAX >= p)//如果两个最大的数字之和就小于p那这就是答案了
        {
            MAX -= p;
            int l = 0;//给定左右端点
            int r = n - 1;
            while (l < r)//当左端点小于右端点时
            {
                if (num[l] + num[r] < p)//答案只可能在两个数之和小于p时出现
                {
                    MAX = max(MAX , num[l] + num[r]);//更新答案
                    l++;
                }
                else
                    r--;//否则和太大了，右端点向左移
            }
        }
        printf("%I64d\n" , MAX);
    }
    return 0;
}
