Description

��N�Ľ׳˵����λ����
���磺
5!=120,�������λΪ1
10!=3628800���������λΪ3

Input

ÿ�����ݰ���һ��,ÿ����һ������N(0<=N<=10000000)

Output

����ÿ���������ݣ����N!�����λ����

Sample Input

5
10

Sample Output

1
3


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define M_PI		3.14159265358979323846
#define M_E		2.7182818284590452354
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF)
    {
        if (n<=10)
        {
            int a[11]={1,1,2,6,2,1,7,5,4,3,3};//ǰ��λ����ȷ�����ֶ�����
            printf("%d\n",a[n]);
        }
        else
        {
            int ans=0;
            double lg=0.5 * log(2 * M_PI *(double)n) / log(10.0) + (double)n * log((double)n / M_E) / log(10.0);
            //��˹���ֹ�ʽ���n!�Ĵ������֣����ؾ�ȷ����С������ʽ����������
            //ע�⣺ֱ�Ӱ��չ�ʽ�㣬����log10()���������inf�������û��׹�ʽ���Ϊe�Ķ���
            //
            int tmp=(int)lg;
            lg-=tmp;//��λ��Ϊ����ֵ
            ans=(int)(pow(M_E,lg*log(10.0)));
            printf("%d\n",ans);
        }
    }
    return 0;
}
