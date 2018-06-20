/**
 * 给定区间[a, b]
 * 求区间里距离最近和最远的2对相邻素数
 * 去区间筛能求[a, b)的素数，所以读入b后要加一
 * 埃氏筛求出[1,sqrt(b))的素数，用is_prime_small保存
 * 根据is_prime_small求出[a, b)的素数
 * 由于b很大，但是b - a < 1e6，所以可以加一个偏移，用is_prime保存[0, b - a)的素数
 * 注意所有数据用long long保存，因为b很接近Integer.MAX
 * 如何求出第一个不小于a的i的倍数ki？
 * (a + i - 1) / i * i
 */
#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "algorithm"
#include "vector"

#define FOR(i, a, b) for (int i = a; i < b; i++)
using namespace std;
typedef long long LL;
const int MAXN = 1e6+5;
bool is_prime[MAXN];
bool is_prime_small[MAXN];
LL max(LL a, LL b) {
    return a < b ? b : a ;
}
int main() {
//    freopen("in.txt", "r", stdin);
    LL a, b;
    while (scanf("%lld%lld", &a, &b) == 2) {
        b++;
        memset(is_prime, true, sizeof is_prime);
        memset(is_prime_small, true, sizeof is_prime_small);
        for (int i = 2; (LL)i * i <= b; i++) {
            if (is_prime_small[i]) {
                for (LL j = i * 2; j * j < b; j += i) {
                    is_prime_small[j] = false;
                }
                for (LL j = max(2L, (a + i - 1) / i) * i; j < b; j += i) {
                    is_prime[j - a] = false;
                }
            }
        }
        LL mindist = 2147483647L;
        LL maxdist = -1L;
        LL minx, miny, maxx, maxy;
        vector<LL> prime;
        FOR (i, 0, b - a)
            if (is_prime[i] && a + i != 1)
                prime.push_back(a + i);
        bool flag = true;
        if (prime.size() < 2) {
            flag = false;
        } else {
            FOR (i, 1, prime.size()) {
                if (prime[i] - prime[i - 1] < mindist) {
                    mindist = prime[i] - prime[i - 1];
                    minx = prime[i - 1];
                    miny = prime[i];
                }
                if (prime[i] - prime[i - 1] > maxdist) {
                    maxdist = prime[i] - prime[i - 1];
                    maxx = prime[i - 1];
                    maxy = prime[i];
                }
            }
        }
        if (!flag) {
            puts("There are no adjacent primes.");
        } else {
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", minx, miny, maxx, maxy);
        }
    }
    return 0;
}