/**
 * 巴什博弈
 * m 个石子，每次取 1 ~ n 个石子
 * 必败的局面是 m % (n + 1) == 0
 * 很好解释
 * 除此之外都是必赢
 */
#include "cstdio"
#include "iostream"
#include "cstdlib"
using namespace std;
int m, n;
int main() {
//    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &m, &n) == 2) {
        int a;
        if ((a = m % (n + 1)) == 0) {puts("none"); continue;}
        printf("%d", a);
        if (a == m) 
            for (int i = 1; i + a <= n; i++)
                printf(" %d", i + a);
        else 
            for (int i = n; i + a <= n; i += n)
                printf(" %d", i + a);
        printf("\n");
    }
    return 0;
}