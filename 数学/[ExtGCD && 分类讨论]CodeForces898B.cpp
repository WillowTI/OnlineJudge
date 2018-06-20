/**
 * 扩展欧几里得的伪模板题
 * 求出x和y只要上模板就行了
 * 但是这道题要求x和y均非负
 * 怎样求出非负的x和y可以看看这篇博客：
 * https://www.cnblogs.com/frog112111/archive/2012/08/19/2646012.html
 * 在求t的时候分t为正和负
 * 主要还是负数的情况比较繁琐
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LL long long
LL extgcd(LL a,LL b,LL &x,LL &y);
int main() {
    //freopen("in.txt", "r", stdin);
    LL a, b, sum;
    while (scanf("%I64d%I64d%I64d", &sum, &a, &b) == 3) {
        LL x = 0;
        LL y = 0;
        LL g = extgcd(a, b, x, y);
        if (sum % g || (sum < x && sum < y)) {
            puts("NO");
            continue;
        }
        LL mul = sum / g;
        LL orix = x;
        LL oriy = y;
        x *= mul;
        y *= mul;
        if (x >= 0 && y >= 0) {
            puts("YES");
            printf("%I64d %I64d\n", x, y);
            continue;
        }
        LL x1 = 0, y1 = 0;
        LL gcd = extgcd(abs(orix), abs(oriy), x1, y1);
        double t1 = (double)(-1.0 * x * gcd / b);
        double t2 = (double)(1.0 * y * gcd / a);
        if (t2 > 0) {
            if ((LL)t2 < t1)
                puts("NO");
            else {
                mul = (LL)t2;
                x += (b / gcd) * mul;
                y -= (a / gcd) * mul;
                puts("YES");
                printf("%I64d %I64d\n", x, y);
            }
            continue;
        }
        if (t2 < 0) {
            if ((LL)t2 - t1 > 1e-8 && fabs((LL)t2 - t2) < 1e-8) {
                mul = (LL)t2;
                puts("YES");
                x += (b / gcd) * mul;
                y -= (a / gcd) * mul;
                printf("%I64d %I64d\n", x, y);
            } else if (t1 - (LL)t2 + 1 < 1e-8) {
                mul = (LL)t2 - 1;
                puts("YES");
                x += (b / gcd) * mul;
                y -= (a / gcd) * mul;
                printf("%I64d %I64d\n", x, y);
            } else
                puts("NO");
            continue;
        }
    }
    return 0;
}

LL extgcd(LL a, LL b, LL &x, LL &y) {
	LL d = a;
	if (b) {
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	} else {
		x = 1;
		y = 0;
	}
	return d;
}
