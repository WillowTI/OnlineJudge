//输入n条有向边，每条边可以翻转，即起点终点互换
//输出翻转后能得到多少图是不包含环的
//不参与环的边不管翻还是不翻都可以，所以贡献是2^x
//参与环的边有2^x种生成情况，其中x是环的大小
//但不能不翻，不能全翻，所以贡献是2^x-2
#include "bits/stdc++.h"
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define DFOR(i,a,b) for(int i=a-1;i>=b;i--)
using namespace std;
typedef long long LL;
const int MAXN = 2e5+5;
const LL MOD = 1e9+7;
LL n, ans, sum;
//xi是每个环的大小
//sum是所有环的大小之和
//按照公式计算得ans = 2^(n-sum)*(2^x1-2)*(2^x2-2)*(2^x3-2)*...
int a[MAXN], cnt[MAXN], par[MAXN];
LL qpow(LL a, LL b);//开LL保平安
void dfs(int depth, int u, int fa);
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%lld", &n) == 1) {
        memset(cnt, 0, sizeof cnt);
        memset(par, 0, sizeof par);
        ans = 1;
        sum = 0;
        FOR(i, 1, n + 1)
            scanf("%d", a + i);
        FOR(i, 1, n + 1) {
            if (!par[i]) {
                dfs(0, i, i);
            }
        }
        ans = (ans * qpow(2, n - sum)) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}

LL qpow(LL a, LL b) {
    LL ans = 1;
    while (b) {
        if (b & 1){
            ans = (ans * a) % MOD;
        }
        b >>= 1;
        a = (a * a) % MOD;
    }
    return ans;
}

void dfs(int depth, int u, int fa) {
    par[u] = fa;
    cnt[u] = depth;//保存结点深度作为集合大小
    if (!par[a[u]])//如果下一个结点尚未扩展就dfs下去
        dfs(depth + 1, a[u], fa);
    else if (par[a[u]] == fa) {//如果已经扩展过，而且属于同一个祖先结点说明找到环，更新ans和sum
        sum += cnt[u] - cnt[a[u]] + 1;//两个结点深度之差为环的大小
        ans = (ans * (qpow(2, cnt[u] - cnt[a[u]] + 1) + MOD - 2)) % MOD;
    }
}