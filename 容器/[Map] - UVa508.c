题意：
输入一些字母的莫尔斯编码
一些单词
现在给定一些莫尔斯串
输出这些字符串代表什么单词
如果有且仅有一个单词是完全匹配的话就输出
如果有多个单词是完全匹配的话就输出输出第一个匹配的加上“!”
如果在字符串尾部增加或删除一些字符匹配某个单词（增加或删除的字符应尽可能少）
就任选一个匹配单词
在末尾加上“？”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char morsecode[50][10];//保存字符的莫尔斯码形式
char alphabet[50];//保存字符
char wordsoriginal[102][15];//保存给定的单词
char wordsmorse[105][150] = {{0}};//保存给定单词的莫尔斯码形式
int matchrecord[105]={0};//保存与目标莫尔斯码完全匹配的单词下标
int morsepos = 0 , wordspos = 0 , matchpos = 0;//字符个数，单词个数，完全匹配个数

int char2morse(char ch);//将字符转化为莫尔斯码

int main()
{
    //freopen("input.txt" , "r" , stdin);
    char tmp [10];
    while (scanf("%s" , tmp) == 1)
    {
        memset(morsecode , 0 , sizeof(morsecode));
        memset(alphabet , 0 , sizeof(alphabet));
        memset(wordsoriginal , 0 , sizeof(wordsoriginal));
        memset(wordsmorse , 0 , sizeof(wordsmorse));
        morsepos = wordspos = matchpos = 0;
        while (1)
        {
            if (tmp[0] == '*')
                break;
            alphabet[morsepos] = tmp[0];
            scanf("%s" , morsecode[morsepos]);
            morsepos++;
            scanf("%s" , tmp);
        }
        while (1)
        {
            scanf("%s" , wordsoriginal[wordspos]);
            if (wordsoriginal[wordspos][0] == '*')
                break;
            wordspos++;
        }
        for (int i = 0 ; i < wordspos ; i++)//把单词转化为莫尔斯码的形式
        {
            for (int j = 0 ; j < strlen(wordsoriginal[i]) ; j++)
            {
                strcat(wordsmorse[i] , morsecode[char2morse(wordsoriginal[i][j])]);
            }
        }
        while (1)
        {
            char tmp[100];
            scanf("%s" , tmp);
            if (tmp[0] == '*')
                break;
            matchpos = 0;
            for (int i = 0 ; i < wordspos ; i++)
            {
                if (strcmp(tmp , wordsmorse[i]) == 0)//判断是否和某个字符串完全匹配
                    matchrecord[matchpos++] = i;
            }
            if (!matchpos)//如果没有一个匹配的
            {
                int mindis = 1000;
                int ans = 0;
                int lentmp = strlen(tmp);
                for (int i = 0 ; i < wordspos ; i++)
                {
                    int lencmp = strlen(wordsmorse[i]);
                    if (lentmp != lencmp)
                    {
                        if (!strncmp(tmp , wordsmorse[i] , lentmp < lencmp ? lentmp : lencmp))//不管是删除末尾还是在末尾添加
                                                                                                                                            //总是要保证两个字符串的前面的字符要相同
                        {
                            int curdis = abs(lentmp - lencmp);//两个字符串，不论谁长谁短，它们的“距离”就是长度之差
                            if (curdis < mindis)//如果当前距离比之前的距离更短，那就更新答案
                            {
                                mindis = curdis;
                                ans = i;
                            }
                        }
                    }
                }
                printf("%s?\n" , wordsoriginal[ans]);
            }
            else
            {
                printf("%s" , wordsoriginal[matchrecord[0]]);
                if (matchpos > 1)
                    printf("!");
                printf("\n");
            }
        }
    }
    return 0;
}

int char2morse(char ch)
{
    for (int i  = 0 ; i < morsepos ; i++)
        if (alphabet[i] == ch)
            return i;
}
