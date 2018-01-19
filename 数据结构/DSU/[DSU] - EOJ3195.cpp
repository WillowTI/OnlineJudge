#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
int par[maxn], n, m;
bool vis[maxn];
int found(int x);
void un(int x, int y);
int main() {
    //freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d%d", &n, &m)) {
        if (!n && !m) break;
        for (int i = 1; i <= n; i++)
            par[i] = i;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            un(x, y);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x = found(par[i]);
            if (!vis[x]) {
                vis[x] = 1;
                ans++;
            }
        }
        printf("Case %d: %d\n", cas++, ans);
    }
    return 0;
}

int found(int x) {
    return x == par[x] ? x : par[x] = found(par[x]);
}

void un(int x, int y) {
    x = found(x);
    y = found(y);
    if (x != y)
        par[x] = y;
}
