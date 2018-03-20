/**
 * 主要是规则的理解
 * 相邻的障碍物是不能破坏的，至少要位移1个距离
 * 碰到边界就直接没了，而不是停下来，但是只要经过终点就算结束
 */
#include "cstdio"
#include "cstring"
#include "algorithm"
using namespace std;
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool m[25][25], fd;
int w, h, stx, sty, edx, edy, ans;
void dfs(int x, int y, int cur_step);
bool is_valid(int x, int y);
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &w, &h) && w) {
        memset(m, 0, sizeof m);
        fd = 0;
        ans = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int num;
                scanf("%d", &num);
                if (num == 2) {
                    stx = i;
                    sty = j;
                    num = 0;
                }
                if (num == 3) {
                    edx = i;
                    edy = j;
                    num = 0;
                }
                m[i][j] = num;
            }
        }
        dfs(stx, sty, 0);
        if (fd)
            printf("%d\n", ans);
        else
            puts("-1");
    }
    return 0;
}

void dfs(int x, int y, int cur_step) {
    if (cur_step > 10)
        return;
    if (x == edx && y == edy) {
        if (fd == 0) {
            fd = 1;
            ans = cur_step;
        } else
            ans = min(ans, cur_step);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int tx = x;
        int ty = y;
        while (is_valid(tx, ty) && !m[tx][ty]) {
            tx += DIR[i][0];
            ty += DIR[i][1];
            if (tx == edx && ty == edy) {
                dfs(tx, ty, cur_step + 1);
                break;
            }
        }
        if (tx - DIR[i][0] == x && ty - DIR[i][1] == y) continue;
        if (is_valid(tx, ty) && m[tx][ty] == 1) {
            m[tx][ty] = 0;
            dfs(tx - DIR[i][0], ty - DIR[i][1], cur_step + 1);
            m[tx][ty] = 1;
        }
    }
}

bool is_valid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w;
}