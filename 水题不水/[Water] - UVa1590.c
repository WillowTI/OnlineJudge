题意：
给定n个ip地址(1 <= n <= 1000)
输出其网络地址和子网掩码

分析：
按照题目意思
改写成二进制的形式
网络地址是其从左往右相同的部分
加上从有不同数字开始
后面都是0的二进制串
再写回十进制
子网掩码与网络地址相似
不同之处在于从左往右一直到有不同数字
这一段数字全是1
后面的一样
都是0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ip[1005][20];
char bin[1005][40];

int n;

int binmaxsame();

int main()
{
    //freopen("input.txt" , "r" , stdin);
    //freopen("output.txt" , "w" , stdout);
    while (scanf("%d" , &n) == 1)
    {
        memset(ip , 0 , sizeof(ip));
        memset(bin , 0 , sizeof(bin));
        for (int i = 0 ; i < n ; i++)
        {
            scanf("%s" , ip[i]);
            ip[i][strlen(ip[i])] = '.';
            int num = 0;
            int times = 0;
            for (int j = 0 ; j < strlen(ip[i]) ; j++)
            {
                if (ip[i][j] != '.')
                    num = num * 10 + ip[i][j] - '0';
                else
                {
                    for (int k = (8 * times + 7) ; k >= 8 * times ; k--)
                    {
                        bin[i][k] =  (num % 2) + '0';
                        num /= 2;
                    }
                    times++;
                }
            }
        }
        int endnum = binmaxsame();
        char mask[33]={0};
        char smallest[33]={0};
        for (int i = 0 ; i < endnum ; i++)
        {
            mask[i] = '1';
            smallest[i] = bin[0][i];
        }
        for (int i = endnum ; i < 32 ; i++)
        {
            mask[i] = '0';
            smallest[i] = '0';
        }
        int m[4] = {0};
        int s[4] = {0};
        int tmp1 = 0;
        int tmp2 = 0;
        for (int i = 0 ; i < 32 ; i ++)
        {
            tmp1 = tmp1 * 2 + mask[i] - '0';
            tmp2 = tmp2 * 2 + smallest[i] - '0';
            if ((i + 1) % 8 == 0)
            {
                m[i / 8] = tmp1;
                s[i / 8] = tmp2;
                tmp1 = 0;
                tmp2 = 0;
            }
        }
        for (int i = 0 ; i < 4 ; i++)
            printf("%d%c" , s[i] , i == 3 ? '\n' : '.');
        for (int i = 0 ; i < 4 ; i++)
            printf("%d%c" , m[i] , i == 3 ? '\n' : '.');
    }
    return 0;
}

int binmaxsame()
{
    int ret = 0;
    for ( ; ret < 32 ; ret++)
    {
        char c = bin[0][ret];
        for (int i = 1 ; i < n ; i++)
        {
            if (c != bin[i][ret])
                return ret;
        }
    }
    return ret;
}
