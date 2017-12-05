#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;
int n, m;
int parent[1005];
void unionset(int x, int y);//合并x城镇和y城镇
int main() {
    //freopen("in.txt", "r", stdin);
    while (1) {
        scanf("%d", &n);
        if (!n) break;
        scanf("%d", &m);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;//节点数组初始化为下标，即父节点就是本身
        }
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            unionset(x, y);//每读进两个城镇就合并
        }
        set<int> s;//把合并后的父节点加到set中，其size就是连通量
        for (int i = 1; i <= n; i++)
            s.insert(parent[i]);
        printf("%d\n", s.size() - 1);//最后要建立的道路数量是连通量 - 1
    }
    return 0;
}

void unionset(int x, int y) {
    int i = min(parent[x], parent[y]);
    int j = max(parent[x], parent[y]);
    for (int k = 1; k <= n; k++)
        if (parent[k] == j)
            parent[k] = i;
}
