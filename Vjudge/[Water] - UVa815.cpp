������⻨�˺ܳ�ʱ��
������ˮ�������һЩ���ӵĸ߶�
��ʵ����Ѻ�ˮ����ɽ�ˮ��������⣬���Ժ���ȫ���ĳ���ˮ��
ÿ�����ӵ��������10 * 10��
������ˮ�������������Ϳ��Գ�100
����Ҫ�����ˮ�ĸ߶Ⱥͱ���û�Ľ������ռ��

�ӵ͵�������
��ˮ���ڽ����ڽϵ͵Ľ�������
����ˮ��������۵ĸ߶ȴﵽ��������ߵĽ�����ʱ
��ˮͬʱ����2���������ϻ���
Ȼ��������3����4��

ע�⽨����ĸ߶ȿ����Ǹ���
���Ҳ����һֱ���۵���ߵĽ�����ʱ����ʣ�����ˮ
��ʱ�ͻ����еĽ�����һ�����
����⻹Ҫ�����ĩ����
��������������֮��������в�һ��


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
