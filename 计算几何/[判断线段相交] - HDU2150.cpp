#include "cstdio"
#include "cstdlib"
#include "algorithm"
#include "cstring"
using namespace std;
struct P {
    int x, y;
};

int n, num[35];
P p[35][105];
bool ans;
double cross(P a, P b, P c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
void inter(P a, P b, P c, P d) {
    if (min(a.x, b.x) <= max(c.x, d.x)
        && min(a.y, b.y) <= max(c.y, d.y)
        && min(c.x, d.x) <= max(a.x, b.x)
        && min(c.y, d.y) <= max(a.y, b.y)
        // 快速排斥
        && cross(a, b, c) * cross(a, b, d) <= 0
        && cross(c, d, a) * cross(c, d, b) <= 0)
        // 跨立实验，叉积
        ans = true;
}

void go() {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = 0; k + 1 < num[i]; k++)
                for (int l = 0; l + 1 < num[j]; l++) {
                    inter(p[i][k], p[i][k + 1], p[j][l], p[j][l + 1]);
                    if (ans) return;
                }
}
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", num + i);
            for (int j = 0; j < num[i]; j++)
                scanf("%d%d", &p[i][j].x, &p[i][j].y);

        }
        ans = false;
        if (n == 1)
            puts("No");
        else {
            go();
            if (ans) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}