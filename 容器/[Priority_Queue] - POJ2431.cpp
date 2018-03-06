/**
 * 尽量挑油量大的加油站，每到一个加油站就判断
 * 如果pq为空就返回-1
 * 记得把终点也加到pq中，否则只是到达最后一个加油站
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
typedef long long LL;
using namespace std;
int n, l, p;
struct Point {
    int x, y;
    Point (int x, int y) {
        this -> x = x;
        this -> y = y;
    }
    Point(){}
    bool operator < (const Point a) const {
        return x < a.x;
    }
};
Point in[10005];
int solve();
int main() {
//    freopen("F:\\TestCode\\TestCLion\\in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &in[i].x, &in[i].y);
    scanf("%d%d", &l, &p);
    for (int i = 0; i < n; i++)
        in[i].x = l - in[i].x;
    sort(in, in + n);
    in[n++].x = l;
    printf("%d\n", solve());
    return 0;
}

int solve() {
    priority_queue<int> pq;
    int ans = 0, pos = 0, tank = p;//pos是当前位置，只会是加油站的位置。tank是当前油箱里的油量
    for (int i = 0; i < n; i++) {
        int d = in[i].x - pos;//d是从上一个加油站到这个加油站的距离
        while (d > tank) {
            if (pq.empty())
                return -1;
            tank += pq.top();
            pq.pop();
            ans++;
        }
        pos = in[i].x;
        tank -= d;
        pq.push(in[i].y);
    }
    return ans;
}