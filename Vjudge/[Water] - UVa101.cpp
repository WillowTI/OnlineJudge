���⣺
move a onto b����a��b�Ϸ���ľ��ȫ����λ��Ȼ���a����b����
move a over b����a�Ϸ���ľ��ȫ����λ��Ȼ���a����b����ľ��ѵĶ���
pile a onto b����b�Ϸ���ľ��ȫ����λ��Ȼ���a�������ľ�����b����
pile a over b����a�������ľ���������b����ľ��ѵĶ���
������
��������vector����
�����ö�ά�����һ���߶���������ɵ�
���������ֲ����������Կ������Ȱ������ľ�����
Ȼ���a�������ľ���������b����ľ��ѵĶ���
�����ͼ��˴�����

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int pile[30][30];
int hight[30];
int n;

void findnumber(int num, int & pi, int & pj);
void clean(int pi, int pj);
void onto(int ai,int aj,int bi);

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        hight[i] = 1;
        pile[i][0] = i;
    }
    while (1)
    {
        char s1[10];
        scanf("%s", s1);
        if (s1[0] == 'q')
            break;
        int a, b;
        scanf("%d", &a);
        char s2[10];
        scanf("%s", s2);
        scanf("%d", &b);
        int ai, aj, bi, bj;
        findnumber(a, ai, aj);
        findnumber(b, bi, bj);
        if (ai != bi)
        {
            if (s1[0] == 'm')
                clean(ai, aj);
            if (s2[1] == 'n')
                clean(bi, bj);
            onto(ai, aj, bi);
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d:", i);
        for (int j = 0; j < hight[i]; j++)
            printf(" %d", pile[i][j]);
        printf("\n");
    }
    return 0;
}

void findnumber(int num, int & pi, int &pj)
{
    for (pi = 0; pi < n; pi++)
        for (pj = 0; pj < hight[pi]; pj++)
            if (num == pile[pi][pj])
                return ;
}

void clean(int pi, int pj)
{
    for (int j = pj + 1; j < hight[pi]; j++)
    {
        int num = pile[pi][j];
        pile[num][hight[num]++] = num;
    }
    hight[pi] = pj + 1;
}

void onto(int ai,int aj,int bi)
{
    for (int j = aj; j < hight[ai]; j++)
    {
        int num = pile[ai][j];
        pile[bi][hight[bi]++] = num;
    }
    hight[ai] = aj;
}
