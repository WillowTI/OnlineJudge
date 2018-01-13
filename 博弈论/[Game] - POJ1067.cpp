/**
 * 威佐夫博弈
 * 两个人如果都采用正确操作，那么面对非奇异局势，先拿者必胜；反之，则后拿者取胜。
 * 通过黄金分割数判断是否是奇异局势
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
const double x = (1 + sqrt(5.0)) / 2.0;
int main() {
    //freopen("in.txt", "r", stdin);
    int a, b;
    while (scanf("%d%d", &a, &b) == 2) {
        if (a > b) {
            int t = a;
            a = b;
            b = t;
        }
        int d = (b - a);
        if (a == (int)(d * x))
            puts("0");
        else
            puts("1");
    }
    return 0;
}
