#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "iostream"
#include "cmath"
#include "algorithm"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const double EPS = 1e-8;
const int MAXN = 1e5+5;
int a[MAXN];
int m, n;

bool go(int x) {
    int last = 0;
    FOR (i, 1, m) {
        int c = last + 1;
        while (c < n && a[c] - a[last] < x) c++;
        if (c == n) return false;
        last = c;
    }
    return true;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    FOR (i, 0, n)
        scanf("%d", a + i);
    sort(a, a + n);
    int l = 0;
    int r = (int)1e9;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (go(mid)) l = mid;
        else r = mid;
    }
    cout << l << endl;
    return 0;
}