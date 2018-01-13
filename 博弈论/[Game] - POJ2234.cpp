/**
 * 按照Nim博弈，所有堆的个数的异或为0说明是P状态，先手必败，否则是N状态，先手必胜
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int main() {
    //freopen("in.txt", "r", stdin);
    int n;
    while (scanf("%d", &n) == 1) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int next;
            scanf("%d", &next);
            ans ^= next;
        }
        printf("%s\n", ans ? "Yes" : "No");
    }
    return 0;
}
