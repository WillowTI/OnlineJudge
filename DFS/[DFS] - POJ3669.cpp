/**
 * 挑战上推荐用BFS做
 * 注意题目描述点的范围是[0, 300]，但实际上301也是可以的，题面有误
 * 如果不借助time数组直接上一个裸的回溯会超时，因为对同一个点会多次遍历
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long LL;
using namespace std;
const int MAXN = 0x7f7f7f7f;
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int m[305][305], n, ans = MAXN, x, y, t, time[305][305];
//m记录这个点什么时候会炸，MAXN代表绝对安全
//time记录到达这个点最小的代价是多少
bool vis[305][305];
bool is_valid(int x, int y);
void dfs(int x, int y, int t);
int main() {
    //freopen("F:\\TestCode\\TestCLion\\in.txt", "r", stdin);
    scanf("%d", &n);
    memset(m, 0x7f, sizeof m);
    memset(time, 0x7f, sizeof time);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &x, &y, &t);
        if (!is_valid(x, y)) continue;
        m[x][y] = min(t, m[x][y]);
        for (int j = 0; j < 4; j++) {
            int tx = x + DIR[j][0];
            int ty = y + DIR[j][1];
            if (is_valid(tx, ty))//一个点可能会多次输入，只保存最早的时间
                m[tx][ty] = min(t, m[tx][ty]);
        }
    }
    dfs(0, 0, 0);
    if (ans == MAXN)
        ans = -1;
    printf("%d\n", ans);
    return 0;
}

bool is_valid(int x, int y) {
    return x >= 0 && x <= 301 && y >= 0 && y <= 301;
}

void dfs(int x, int y, int t) {
    if (m[x][y] == MAXN) {//如果到达安全区就更新time数组和答案
        ans = min(ans, t);
        time[x][y] = min(time[x][y], t);
        return;
    }
    if (t >= m[x][y])//不合法的情况直接返回
        return;
    time[x][y] = min(time[x][y], t);
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int tx = x + DIR[i][0];
        int ty = y + DIR[i][1];
        if (is_valid(tx, ty) && !vis[tx][ty] && time[tx][ty] > t + 1) {
            vis[tx][ty] = 1;
            dfs(tx, ty, t + 1);
            vis[tx][ty] = 0;
        }
    }
}