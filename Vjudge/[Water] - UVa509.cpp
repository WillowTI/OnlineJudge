���⣺
Ϊ�������ܱ��ָ�
���ݶ��Ǵ��ڲ�ͬ�Ĵ����ϵ�
����d, s, b
dΪ���̵�����
sΪÿ����Ķ�����λ
bΪÿ�������ж��ٸ����ݿ飨����У��飩
żУ��ΪE
����ͬһ��
�����еĶ�����λ���������0
��У��ΪO
�������1
�𻵵�������x��ʾ
һ���в����ж���1��x
��Ҫ�����Ƿ�Ϻ�У��Ĺ���
����������invalid
����Ļָ�����
���Ѷ�����ת��Ϊʮ�����ƣ�У��鲻�������ת����
������û�д���4�ı�������ĩβ��0

������
һ����ģ��
����ǽ���ͽ���ת��
������ר������2������

#include <cstdio>
#include <cstring>

char cd[6][6405];
char ans[100000];
int d, s, b;
char check;

int decode();
void getans();

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("output.txt","w",stdout);
    int cas = 1;
    while (scanf("%d%d%d\n", &d, &s, &b) == 3 && d)
    /*
       ���������ͦ����˼�ģ�����д���ļ��������
       �����ڿ���̨���ִ�Ͳ���
       ���Ҳ�ǹ���
       ��һ��д����while (scanf("%d", &d)==1 && d)
       ��ѭ���������ȥs, b
    */
    {
        memset(cd, 0, sizeof(cd));
        memset(ans, 0, sizeof(ans));
        check = getchar();
        if (check == 'E')
            check = '0';
        else
            check = '1';
        for (int i = 0 ; i < d ; i++)
            scanf("%s", cd[i]);
        int flag = decode();
        if (flag)
        {
            for (int i = 0 ; i < b ; i++)
                for (int j = i * s ; j < (i + 1) * s ; j++)
                    cd[i % d][j] = '*';//��У����Ϊ*
            getans();
            printf("Disk set %d is valid, contents are: %s\n", cas, ans);
        }
        else
            printf("Disk set %d is invalid.\n", cas);
        cas++;
    }
}

int decode()
{
    for (int j = 0 ; j < s * b ; j++)
    {
        char cur = cd[0][j];
        int num = 0;
        int corx, cory;
        if (cur == 'x')
        {
            num++;
            corx = 0;
            cory = j;
        }
        for (int i = 1 ; i < d ; i++)
        {
            if (cd[i][j] == 'x')
            {
                num++;
                corx = i;
                cory = j;
            }
            else//��������һ��ʼ��ĵط�������˺ü��鶼û�п���������Ҫ�������۵�
            {
                if (cur!='x') cur = cur == cd[i][j] ? '0' : '1';//���֮ǰ����0��1���Ǿ����������
                else cur = cd[i][j] ;//�������cur
            }
            if (num > 1)//δ֪����������1������
                return 0;
        }
        if (num)
        {
            if (check == '0')
                cd[corx][cory] = cur;
            else
                cd[corx][cory] = (!(cur - '0')) + '0';
        }
        else if (cur != check)//��������������У�������
            return 0;
    }
    return 1;
}

void getans()//��תʮ���ƣ���תʮ������
{
    int pos = 0;
    int cur = 0;
    int cnt = 0;
    for (int i = 0 ; i < b ; i++)
    {
        for (int j = 0 ; j < d ; j++)
        {
            for (int k = 0 ; k < s ; k++)
            {
                if (cd[j][i * s + k] != '*')//����У���ͼ�����
                {
                    cnt++;
                    cur = cur * 2 + cd[j][i * s + k] - '0';
                }
                if (cnt == 4)//�������4��λ�˾�ͣ����
                {
                    cnt = 0;
                    if (cur < 10)
                        ans[pos++] = cur + '0';
                    else
                        ans[pos++] = cur -10 + 'A';
                    cur = 0;
                }
            }
        }
    }
    if (cnt)//���û����4λ����������0
    {
        for (int i = cnt ; i != 4 ; i++)
            cur *= 2;
        if (cur < 10)
            ans[pos++] = cur + '0';
        else
            ans[pos++] = cur -10 + 'A';
        cur = 0;
    }
}
