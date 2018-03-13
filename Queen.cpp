#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
typedef long long LL;
using namespace std;
int queen, ans;
bool chess[100][100];
void BackTrace(int cur);
bool is_valid(int x, int y);
bool is_in_chess(int x, int y);
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &queen);
    BackTrace(0);
    printf("%d\n", ans);
    return 0;
}

void BackTrace(int cur) {
    if (cur == queen) {
        ans++;
        return;
    }
    for (int i = 0; i < queen; i++) {
        if (is_valid(cur, i)) {
            chess[cur][i] = 1;
            BackTrace(cur + 1);
            chess[cur][i] = 0;
        }
    }
}

bool is_valid(int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int tx = x + i;
            int ty = y + j;
            while (is_in_chess(tx, ty) && !chess[tx][ty]) {
                tx += i;
                ty += j;
            }
            if (is_in_chess(tx, ty)) return false;
        }
    }
    return true;
}

bool is_in_chess(int x, int y) {
    return x >= 0 && x < queen && y >= 0 && y < queen;
}
