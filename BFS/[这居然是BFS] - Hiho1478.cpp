/**
 * 把水加入队列，然后对4个方向bfs，同时更新距离
 * 对于已经更新了距离的点不再更新，因为肯定之前的值更小
 * 暴力T了，可能10s是假的
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 805;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char in[MAXN][MAXN];
int n, m, dis[MAXN][MAXN];
bool is_valid(int x, int y);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        scanf("%s", in[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            dis[i][j] = -1;
            if (in[i][j] == '0') {
                dis[i][j] = 0;
                q.push(make_pair(i, j));
            }
        }
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            if (is_valid(xx, yy) && dis[xx][yy] == -1) {
                dis[xx][yy] = dis[x][y] + 1;
                q.push(make_pair(xx, yy));
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d%c", dis[i][j], j == m - 1 ? '\n' : ' ');
    return 0;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
