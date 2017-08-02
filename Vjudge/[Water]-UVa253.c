题意：
给定两个正方体的涂色方案
判断这两个正方体是不是一样的
可以旋转

分析：
分类讨论，判断第二个正方体的哪对面和第一个正方体的上下面是相同的
根据不同的情况旋转
可能有多种面相同的情况，所以要把所有的条件都走一遍
只要其中有一次判断成功，后面的就不用做了

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char cube[20];
char s1[10];//第一个正方体
char s2[10];//第二个正方体
char ori1[10];//旋转的时候改变了第一个正方体，所以要记录原来的颜色
char ori2[10];//同上

int exam();

int main()
{
    //freopen("input.txt" , "r" , stdin);
    //freopen("output.txt" , "w" , stdout);
    while (scanf("%s" , cube) == 1)
    {
        strncpy(s1 , cube , 6);
        strcpy(s2 , cube + 6);
        strcpy(ori1 , s1);
        strcpy(ori2 , s2);
        int flag = 0;
        if (s1[0] == s2[0] && s1[5] == s2[5])
            flag = exam();
        if (!flag && s1[0] == s2[5] && s1[5] == s2[0])//当上下面是颠倒的时候有两种旋转方案
        {
            char tmp;
            tmp = s2[0];
            s2[0] = s2[5];
            s2[5] = tmp;
            tmp = s2[2];
            s2[2] = s2[3];
            s2[3] = tmp;
            flag = exam();
            if (!flag)
            {
                tmp = s2[2];
                s2[2] = s2[3];
                s2[3] = tmp;
                tmp = s2[1];
                s2[1] = s2[4];
                s2[4] = tmp;
                flag = exam();
            }
            strcpy(s1 , ori1);
            strcpy(s2 , ori2);
        }
        if (!flag && s1[0] == s2[1] && s1[5] == s2[4])
        {
            char tmp[7]={0};
            strcpy(tmp , s2);
            s2[0] = tmp[1];
            s2[4] = tmp[0];
            s2[5] = tmp[4];
            s2[1] = tmp[5];
            flag = exam();
            strcpy(s1 , ori1);
            strcpy(s2 , ori2);
        }
        if (!flag && s1[0] == s2[4] && s1[5] == s2[1])
        {
            char tmp[7]={0};
            strcpy(tmp , s2);
            s2[0] = tmp[4];
            s2[4] = tmp[5];
            s2[5] = tmp[1];
            s2[1] = tmp[0];
            flag = exam();
            strcpy(s1 , ori1);
            strcpy(s2 , ori2);
        }
        if (!flag && s1[0] == s2[2] && s1[5] == s2[3])
        {
            char tmp[7]={0};
            strcpy(tmp , s2);
            s2[0] = tmp[2];
            s2[3] = tmp[0];
            s2[5] = tmp[3];
            s2[2] = tmp[5];
            flag = exam();
            strcpy(s1 , ori1);
            strcpy(s2 , ori2);
        }
        if (!flag && s1[0] == s2[3] && s1[5] == s2[2])
        {
            char tmp[7]={0};
            strcpy(tmp , s2);
            s2[0] = tmp[3];
            s2[3] = tmp[5];
            s2[5] = tmp[2];
            s2[2] = tmp[0];
            flag = exam();
            strcpy(s1 , ori1);
            strcpy(s2 , ori2);
        }
        if (flag)
            puts("TRUE");
        else
            puts("FALSE");
    }
    return 0;
}

int exam()
{
    char t1[5]={0};
    char t2[5]={0};
    t1[0] = s1[2];
    t1[1] = s1[1];
    t1[2] = s1[3];
    t1[3] = s1[4];
    t2[0] = s2[2];
    t2[1] = s2[1];
    t2[2] = s2[3];
    t2[3] = s2[4];
    for (int i = 0 ; i < 4 ; i++)
        if (t1[0] == t2[(0 + i) % 4] && t1[1] == t2[(1 + i) % 4] && t1[2] == t2[(2 + i) % 4] && t1[3] == t2[(3 + i) % 4])
            return 1;
    return 0;
}
