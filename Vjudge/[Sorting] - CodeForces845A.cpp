���⣺
����2 * n����
�ֳ�����
ÿ��n����
���Ƿ����һ�ַ������
ʹ��һ���������ȫ���ϸ������һ�������

������
����
�ȴ�С


#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int num[205];

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++)
        scanf("%d", &num[i]);
    sort(num, num + 2 * n);
    if (num[n] > num[n - 1])
        puts("YES");
    else
        puts("NO");
    return 0;
}
