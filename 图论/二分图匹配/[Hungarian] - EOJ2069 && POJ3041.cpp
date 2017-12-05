/**
 * 最小点覆盖=最大匹配数
 * 以行和列构造二分图，若某行某列有一个陨石，就视为有匹配关系
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, k;
bool vis[505], connect[505][505];//vis数组记录每次path中这个点是否被访问过，connect数组记录两个点之间是否有联系
int match[505];//match数组记录哪个点和它连接，没有连接为0
bool path(int x);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        connect[x][y] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {//遍历每一个点，检查是否能增加匹配
        memset(vis, 0, sizeof(vis));
        if (path(i))//每次path成功都会增加一条匹配的数目
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}

bool path(int x) {
    for (int i = 1; i <= n; i++) {
        if (connect[x][i] && !vis[i]) {//如果有联系而且尚未被访问
            vis[i] = 1;
            if (!match[i] || path(match[i])) {//如果这个点尚未连接或者能把它腾出空间
                match[i] = x;//那就更新联系
                return 1;
            }
        }
    }
    return 0;
}
