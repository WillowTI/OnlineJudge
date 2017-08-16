题意：
为了数据能被恢复
数据都是存在不同的磁盘上的
给定d, s, b
d为磁盘的数量
s为每个块的二进制位
b为每个磁盘有多少个数据块（包括校验块）
偶校验为E
对于同一列
磁盘中的二进制位异或下来是0
奇校验为O
异或下来1
损坏的数据用x表示
一列中不会有多余1个x
还要检验是否合乎校验的规则
不合理的输出invalid
合理的恢复数据
并把二进制转化为十六进制（校验块不参与进制转换）
如果最后没有凑满4的倍数，在末尾添0

分析：
一步步模拟
最烦的是解码和进制转换
所以我专门列了2个函数

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
       这里读数据挺有意思的，这样写用文件读入可以
       但是在控制台里手打就不行
       结果也是过的
       另一种写法是while (scanf("%d", &d)==1 && d)
       在循环体里读进去s, b
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
                    cd[i % d][j] = '*';//把校验块变为*
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
            else//这里是我一开始错的地方，检查了好几遍都没有看出来，是要分类讨论的
            {
                if (cur!='x') cur = cur == cd[i][j] ? '0' : '1';//如果之前就是0或1，那就正常做异或
                else cur = cd[i][j] ;//否则更新cur
            }
            if (num > 1)//未知数个数大于1个不行
                return 0;
        }
        if (num)
        {
            if (check == '0')
                cd[corx][cory] = cur;
            else
                cd[corx][cory] = (!(cur - '0')) + '0';
        }
        else if (cur != check)//检验下来不满足校验规则不行
            return 0;
    }
    return 1;
}

void getans()//先转十进制，再转十六进制
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
                if (cd[j][i * s + k] != '*')//不是校验块就继续做
                {
                    cnt++;
                    cur = cur * 2 + cd[j][i * s + k] - '0';
                }
                if (cnt == 4)//如果读到4个位了就停下来
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
    if (cnt)//如果没凑满4位，就往后添0
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
