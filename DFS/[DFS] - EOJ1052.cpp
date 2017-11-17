#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, maxweight, ans;
int w[30], v[30];
void dfs(int index, int weight, int value);
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        ans = 0;
        scanf("%d%d", &n, &maxweight);
        for (int i = 0; i < n; i++)
            scanf("%d%d", w + i, v + i);
        dfs(0, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}

void dfs(int index, int weight, int value) {
    if (weight > maxweight)
        return;
    ans = max(value, ans);
    for (int i = index; i < n; i++)
        dfs(i + 1, weight + w[i], value + v[i]);
}
//还有一种写法
/**
 *if (index == n + 1) {
        if (weight <= maxweight && value > ans) {
            ans = value;
        }
        return ;
    }
    dfs(index + 1, weight + w[index], value + v[index]);
    dfs(index + 1, weight, value);
 */
/**
 *我的写法应该更好
 *因为我的出口在当前重量大于背包容量的时候
 *而另一种方法的出口在遍历完所有物品
 *有可能还没有遍历完就已经超重了，那后面的遍历都是白费力气
 */
