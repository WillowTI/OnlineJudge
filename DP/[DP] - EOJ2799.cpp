#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int cost[305][305], dp[305][305];
//cost[i][j]��¼��i���ǵ�j����С����
//dp[i][j]��¼��ǰi�������︲��j�����ֵ���С����
int n, m, k;
void floyd();
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    for (int t = 0; t < cas; t++) {
        for (int i = 0; i < 305; i++)
            for (int j = i; j < 305; j++)
                cost[i][j] = 0xfffff;//��ʼ��Ϊ�����
        for (int i = 0; i < 305; i++)
            for (int j = 0; j <= i + 1; j++)
                dp[i][j] = j == 0 ? 0 : 0xfffff;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            for (int st = a; st <= b; st++)
                for (int ed = st; ed <= b; ed++)
                    cost[st][ed] = min(cost[st][ed], c);
        }
        floyd();//����С����
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i][j] = dp[i - 1][j];//�ȳ�ʼ��Ϊǰi-1�����︲��j�����Ļ���
                                        //ע��i=jʱ��ȫ�����ǣ���ʱ�����ʵ�(i-1,j)����Ȼ�ǲ��Ϸ��ģ�����һ���������
                for (int t = 1; t <= j; t++) {//�����Ƚ����а�����i������������ܹ�����j����������t������j
                    if (cost[i - t + 1][i] != 0xfffff) {
                        dp[i][j] = min(dp[i][j], dp[i - t][j - t] + cost[i - t + 1][i]);//ǰi-t�����︲��j-t�������Ž���Ϻ�������t�����Ļ���֮��
                    }
                }
            }
        }
        printf("case #%d:\n", t);
        printf("%d\n", dp[n][k]);
    }
    return 0;
}

void floyd() {
    for (int k = 1; k < n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k + 1][j]);
                //ϸ�����⣺��Ϊǰ���Ѿ����ǵ�k���ˣ����Ժ�һ��cost�Ǵ�k+1��ʼ
                //�����·����cost[i][k] + cost[k][j]���൱����kΪ��ת
}

