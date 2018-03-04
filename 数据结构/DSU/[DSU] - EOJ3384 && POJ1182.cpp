/**
 * 带权并查集
 * 既然我知道是A还是B还是C，那就枚举
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long LL;
using namespace std;
int n, k, ans, op, x, y, par[150005];
bool same(int x, int y);
int dsu_find(int x);
void dsu_union(int x, int y);
int main() {
    //freopen("F:\\TestCode\\TestCLion\\in.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 1; i < 150005; i++)
        par[i] = i;
    while (k--) {
        scanf("%d%d%d", &op, &x, &y);
        if (x <= 0 || x > n || y <= 0 || y > n) {
            ans++;
            continue;
        }
        if (op == 1) {
            if (same(x, y + n) || same(x, y + 2 * n)) ans++;
            else {
                dsu_union(x, y);
                dsu_union(x + n, y + n);
                dsu_union(x + 2 * n, y + 2 * n);
            }
        } else {
            if (same(x, y) || same(x, y + 2 * n)) ans++;
            else {
                dsu_union(x, y + n);
                dsu_union(x + n, y + 2 * n);
                dsu_union(x + 2 * n, y);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}

int dsu_find(int x) {
    return x == par[x] ? x : par[x] = dsu_find(par[x]);
}

bool same(int x, int y) {
    return dsu_find(x) == dsu_find(y);
}

void dsu_union(int x, int y) {
    x = dsu_find(x);
    y = dsu_find(y);
    if (x == y) return;
    par[x] = y;
}