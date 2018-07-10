/**
 * 花式爆内存，要提前一步判断到达终点才行，最终结果差别很大
 */
#include "cstdio"
#include "algorithm"
#include "cstring"
#include "queue"

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const int MAXN = 1005;
char a[MAXN][MAXN];
bool vis[MAXN][MAXN];
int b, c, d;
int ans;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct Node {
    int x = 0, y = 0, step = 0;
};

bool isValid(int x, int y) {
    return x >= 0 && x < b && y >= 0 && y < c;
}

Node st;

void bfs(char c) {
    queue<Node> q;
    q.push(st);
    vis[st.x][st.y] = true;
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        int x = cur.x;
        int y = cur.y;
        if (a[x][y] == c) {
            ans += cur.step;
            st.x = x;
            st.y = y;
            st.step = 0;
            return;
        }
        FOR (i, 0, 4) {
            int nx = x + D[i][0];
            int ny = y + D[i][1];
            if (isValid(nx, ny) && !vis[nx][ny] && a[nx][ny] != 'X') {
                if (a[nx][ny] == c) {
                    st.x = nx;
                    st.y = ny;
                    st.step = 0;
                    ans += cur.step + 1;
                    return;
                } else {
                    Node next;
                    next.x = nx;
                    next.y = ny;
                    next.step = cur.step + 1;
                    q.push(next);
                    vis[nx][ny] = true;
                }
            }
        }

    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &b, &c, &d);
    FOR (i, 0, b) {
        scanf("%s", a[i]);
    }
    FOR (i, 0, b) {
        FOR (j, 0, c) {
            if (a[i][j] == 'S') {
                st.x = i;
                st.y = j;
            }
        }
    }
    FOR (i, 1, d + 1) {
        memset(vis, false, sizeof vis);
        bfs('0' + i);
    }
    printf("%d\n", ans);
    return 0;
}
