���⣺
����n������k
��С��k�ľ����ܴ������
ʹ����n + 1������GCD����1
����Ҳ����������������0

������
�����n������GCD
���GCD����1
��ô��һ����0
�����GCD�ֽ�������
������������x��


#include <cstdio>
#include <algorithm>

using namespace std;

int num[100005];
int factor[32000];
int pos = 0;
int n, k;

int gcd(int a, int b);

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    sort(num, num + n);
    int GCD = num[0];
    for (int i = 1; i < n; i++)
    {
        GCD = gcd(num[i], GCD);
        if (GCD == 1)
            break;
    }
    if (GCD == 1)
        printf("0\n");
    else
    {
        int st = 2;
        int first = 1;
        while (GCD != 1)//�ֽ���������ʱ������TLEһ�Σ���Ϊʣ�µ����һ���������ܻ�ܴ�ÿ�μ�һ�ͻᳬʱ
        {
            if (st * st > GCD)
            {
                factor[pos++] = GCD;
                break;
            }
            else if (GCD % st == 0)
            {
                if (first)
                {
                    factor[pos++] = st;
                    first = 0;
                }
                GCD /= st;
            }
            else
            {
                st++;
                first = 1;
            }
        }
        int ans = -1;
        for (int i = 0 ; i < pos ; i++)
        {
            int tmp = k / factor[i] * factor[i];//�ҵ����Ĵ�
            ans = ans > tmp ? ans : tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a %b);
}
