���⣺
�ر�����һ����
������������n
����p��Ԫ�ش�Сsp
����qԪ�ش�Сsq
��ʹQofs'(i)=(Pofs(i)+Pofs(i)<<A)>>B������A��B��ֵ����q����ռ�õĿռ�k��
k������С
����ж����
a������С
������ж����
b������С

������
��������������Ŀ����˼ȥģ�������
�ҵ����������
���������˵Ĵ�������

����һ��
������Linux�����е�
�������long longҪ��%lld
����%I64dһֱPresentation Error����֪����������

#include <cstdio>
#include <cstring>
#include <cmath>

int n, sp, sq;
int a = 0, b = 0;
double bi;
long long ans[33][33];

int isvalid(int x, int y);

int main()
{
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d%d", &n, &sp, &sq) == 3)
    {
        memset(ans, 0, sizeof(ans));
        bi = (double)sp / sq;
        long long tmp;
        int first = 1;
        for (int i = 0 ; i < 33 ; i++)//ö��a��b����󿪵�32�� ��n*sp�����ֵ2^30������ϳ�long long�����Χ����С�˻�WA
        {
            for (int j = 0 ; j < 33 ; j++)
            {
                if (isvalid(i, j))//�ж�����a��b�Ƿ������ص���ʵ������ȫ����ˣ��һ��Ƶ���һ�鹫ʽ
                {
                    ans[i][j] = (long long)(sp * (n - 1) * (1 + pow(2, i)) / pow(2, j) + sq);
                    if (first)
                    {
                        tmp = ans[i][j];
                        first = 0;
                    }
                    else
                        tmp = tmp < ans[i][j] ? tmp : ans[i][j];
                }
            }
        }
        int find = 0;
        for (int i = 0 ; i < 33 ; i++)//�ҵ�����a��b������С������
        {
            for (int j = 0 ; j < 33 ; j++)
            {
                if (ans[i][j] == tmp)
                {
                    a = i;
                    b = j;
                    find = 1;
                    break;
                }
            }
            if (find)
                break;
        }
        printf("%Ild %d %d\n", tmp, a, b);
    }
    return 0;
}

int isvalid(int x, int y)
{
    double res = pow(2, y) / (pow(2, x) + 1);
    return res <= bi;
}

���������Ľⷨ
����̫��
for(a=0;a<32;++a)
    for(b=0;b<32;++b){
        LL cur=(((n-1)*sp+((n-1)*sp<<a))>>b)+sq;
        if(cur>=n*sq&&cur<best) best=cur,aa=a,bb=b;
    }
��ʵ�ϵ�a��bһ��ʱ��q�������ڴ�֮��Ŀ�������ȷ����
�����������һ���Ȳ�����
���Բ��ص�Ҳ�͵ȼ��ڵ�ǰ�Ĵ𰸴��ڵ���������С����n * sq
�����Ǵ�a������b������˳�����
����Ҳ����a��b��С�Ĺ���
