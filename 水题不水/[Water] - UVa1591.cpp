题意：
特别抽象的一道题
给出数据总量n
数组p的元素大小sp
数组q元素大小sq
求使Qofs'(i)=(Pofs(i)+Pofs(i)<<A)>>B成立的A、B的值，和q数组占用的空间k。
k尽可能小
如果有多组答案
a尽可能小
如果还有多组答案
b尽可能小

分析：
暴力做，按照题目的意思去模拟就行了
我的做法想多了
最后给出别人的聪明做法

还有一点
这是在Linux上运行的
所以输出long long要用%lld
我用%I64d一直Presentation Error还不知道错在哪里

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
        for (int i = 0 ; i < 33 ; i++)//枚举a和b，最大开到32， 和n*sp的最大值2^30正好组合成long long的最大范围，开小了还WA
        {
            for (int j = 0 ; j < 33 ; j++)
            {
                if (isvalid(i, j))//判断这组a，b是否会造成重叠，实际上完全想多了，我还推倒了一遍公式
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
        for (int i = 0 ; i < 33 ; i++)//找到满足a，b尽可能小的条件
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

网上其他的解法
简略太多
for(a=0;a<32;++a)
    for(b=0;b<32;++b){
        LL cur=(((n-1)*sp+((n-1)*sp<<a))>>b)+sq;
        if(cur>=n*sq&&cur<best) best=cur,aa=a,bb=b;
    }
事实上当a，b一定时，q的两段内存之间的空余量是确定的
可以想象成是一个等差数列
所以不重叠也就等价于当前的答案大于等于理论最小距离n * sq
而且是从a递增的b递增的顺序遍历
所以也满足a，b最小的规则
