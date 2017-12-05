这道题很迷
一开始用Java写
RunTimeError
还在想大概是HashMap返回了null
（后来事实证明不是）
花了三天

然后受不了了去网上找代码
一边模仿一边自己写
写出来WA
WA还行，只要不是RTE就好受多了
把自己的代码和AC的代码一段段地比较、替换、提交
终于发现了几个错误点：
1.prot数组一定要开大，否则就是WA
一开始用Java提交RTE的原因就是这个
改了之后就是WA了
明明题目说的就是70个不多不少
为什么偏偏要开到200个
试过75个、100个都不来塞
很是无语
2.关于数组元素个数的计算
我的理解是两轮打完后有DQ的出去
这样踢过一遍后如果个数大于70就把个数控制在70以内
和第70名前两轮分数之和一样的人也一起进来
但是AC代码的做法不一样
我也不知道他在干什么
3.关于每个人的money计算
AC代码没有限制对prot下标大于等于70的访问
（其实越界访问的结果就是0.0，我试过了，这并无大碍）
而且把业余选手和DQ的人的奖金都算了
只是最后输出的时候没有显示
这样的做法一点也不严谨

最后输出的格式也有点问题
对于业余选手的总分应该是输出3位也就是"%-3d"
这在udebug上是过不了的
但是测试数据没涉及到这个问题

综上所述
这道题疑点重重
我居然还在上面debug了4天

想了想
自己写的Java的和C++的代码还是不放上来了
最后附上AC代码原址：http://blog.csdn.net/aozil_yang/article/details/50543965

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 200;
const int maxt = 50;
const int DQ = 999999;
const double eps = 1e-8;
struct player
{
    char name[maxt];
    double money;
    int place,all_2,all_4,dq[5];
    bool is_pro,is_T;
}players[maxn];
int rev_len(int k){
    int sum = 0;
    while(k!=0){
        k/=10;
        sum++;
    }
    return sum;
}
bool cmp1(const player&a,const player&b){
    if (a.all_2 != b.all_2)return a.all_2 < b.all_2;
    return strcmp(a.name,b.name)<0;
}
bool cmp2(const player&a,const player&b){
    if (a.all_4!=b.all_4)return a.all_4<b.all_4;
    return strcmp(a.name,b.name) < 0;
}
bool cmp3(const player&a,const player&b){
    int suma=0,sumb=0;
    for (int i = 0; i < 4;++i)if (a.dq[i]==DQ){suma=i;break;}
    for (int i = 0; i < 4;++i)if (b.dq[i]==DQ){sumb=i;break;}
    if (suma!=sumb)return suma>sumb;
    if(a.all_4!=b.all_4)return a.all_4<b.all_4;
    return strcmp(a.name,b.name)<0;
}
int main()
{
    //freopen("out.txt","w",stdout);
    int T,n;
    double prot[maxn],money_all;
    scanf("%d",&T);{
        while(T--){
            memset(players,0,sizeof(players));
            memset(prot,0,sizeof(prot));
            scanf("%lf",&money_all);
            for (int i = 0; i < 70; ++i)scanf("%lf",&prot[i]);
            scanf("%d",&n);
            getchar();
            for (int i = 0; i < n; ++i){
                fgets(players[i].name,20,stdin);
                if (!strchr(players[i].name, '*'))players[i].is_pro=true;
                for (int j = 0; j < 4; ++j){
                    int flag = 0;
                    if (!scanf("%d",&players[i].dq[j])){
                        players[i].dq[j] = DQ;
                        flag = 1;
                    }
                if (j<2)players[i].all_2+=players[i].dq[j];
                players[i].all_4+=players[i].dq[j];
                if (flag)break;
                }
                char ch[45];
                fgets(ch,40,stdin);
            }
            sort (players,players+n,cmp1);
            int pos=0,pos2=0;
            while(pos < min(n,70) && players[pos].all_2 < DQ)++pos;
            while(pos < n && players[pos].all_2 == players[pos-1].all_2 && players[pos].all_2 < DQ)++pos;
            sort(players,players+pos,cmp2);
            while(pos2 < n && pos2 <= pos && players[pos2].all_4 < DQ)++pos2;
            while(pos2 < n && players[pos2].all_4 == players[pos2-1].all_4 && players[pos2].all_4<DQ)++pos2;
            if (pos!=pos2)sort(players+min(pos,pos2),players+max(pos,pos2),cmp3);
            int rak=1,cur=0,pos3,cont3=0;
            while(cur < min(pos,pos2) ){
                int sum=0;
                double sum_mon=0;
                for (pos3 = cur; players[pos3].all_4==players[cur].all_4;++pos3){
                    if (players[pos3].is_pro){
                        sum++;
                        sum_mon+=prot[cont3++];
                    }
                }
                if (sum)sum_mon/=sum;
                else sum_mon/=100;
                for (int i = cur; i < pos3; ++i){
                    players[i].place=rak;
                    if (players[i].is_pro && sum)players[i].money=sum_mon*money_all/100.0+eps;
                    if(players[i].is_pro && sum > 1 && cont3-sum<70)players[i].is_T=true;
                    if (cont3-sum >=70)players[i].is_pro=false;
                }
                int numb = pos3-cur;
                rak+=numb;
                cur+=numb;
            }
            printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
            printf("-----------------------------------------------------------------------\n");
            for (int i = 0; i < pos; ++i){
                printf("%-21s",players[i].name);
                int N=10;
                if (players[i].all_4<DQ){printf("%d",players[i].place);N-=rev_len(players[i].place);}
                if (players[i].is_T){printf("T");N--;}
                for (int i = 0; i < N; ++i)printf(" ");N=4;
                for (int j =0;j < 4; ++j){
                    if(players[i].dq[j]!=DQ) printf("%-5d",players[i].dq[j]);
                    else {N-=j;break;}
                }if (N==4)N=0;
                for(int i = 0; i < N; ++i)printf("     ");
                if (N){printf("DQ\n");continue;}
                if (players[i].is_pro){printf("%-10d",players[i].all_4);printf("$%9.2lf",players[i].money);}
                else printf("%d",players[i].all_4);//有点问题，详见开头分析
                printf("\n");
            }
            if (T)printf("\n");
        }
    }
    return 0;
}
}
