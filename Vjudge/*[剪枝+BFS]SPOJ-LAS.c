#include<bits/stdc++.h>
//http://blog.csdn.net/llzhh/article/details/70677178
using namespace std;
char G[205][205];
int d[4][2] = {-1,0, 0,1, 1,0, 0,-1};
int sx, sy, ex, ey, n, m;
int front_x[205][205], front_y[205][205], cnt[205][205], director[205][205];

struct node
{
    int step;
    int x, y;
    bool operator < (const node &a)const
    {
        if(a.step == step)
        {
            if(a.x == x)
                return y > a.y;
            return x > a.x;
        }
        return step > a.step;
    }
};

priority_queue <node> q;

bool Check(int x, int y, int step)
{
    if(x >= 0 && x < n && y >= 0 && y < m && G[x][y] != '#' && (cnt[x][y] == -1 || cnt[x][y] == step))
        return 1;
    return 0;
}

void add(int x, int y, int dir, int step)
{
    int tx, ty;
    node tmp;
    tx = x;
    ty = y;
    x += d[dir][0];
    y += d[dir][1];
    while(Check(x, y, step))
    {
        if(cnt[x][y] != step)
        {
            cnt[x][y] = step;
            front_x[x][y] = tx;
            front_y[x][y] = ty;
            director[x][y] = dir;
            tmp.x = x;
            tmp.y = y;
            tmp.step = step;
            q.push(tmp);
        }

        tx = x;
        ty = y;
        x += d[dir][0];
        y += d[dir][1];
    }
}

char Find_dir(int x, int y, int d1, int d2)
{
    if((d1 == 1 && d2 == 0) || (d1 == 0 && d2 == 1))
        return '/';
    else if((d1 == 2 && d2 == 3) || (d1 == 3 && d2 == 2))
        return '/';
    else if((d1 == 0 && d2 == 3) || (d1 == 3 && d2 == 0))
        return '\\';
    else if((d1 == 1 && d2 == 2) || (d1 == 2 && d2 == 1))
        return '\\';
    else
        return G[x][y];
}

void bfs(int dir)
{
    while(!q.empty())
        q.pop();

    node now, next;
    cnt[sx][sy] = 100000;
    add(sx, sy, dir, 0);

    while(!q.empty())
    {
        now = q.top();
        q.pop();
        if(now.x == ex && now.y == ey)
        {
            int tx = ex, ty = ey;
            ex = front_x[tx][ty];
            ey = front_y[tx][ty];
            while(ex != sx || ey != sy)
            {
                if(director[ex][ey] != director[tx][ty])
                    G[ex][ey] = Find_dir(ex, ey, director[ex][ey], director[tx][ty]);
                tx = ex;
                ty = ey;
                ex = front_x[tx][ty];
                ey = front_y[tx][ty];
            }
            return;
        }
        next.step = now.step + 1;
        for(int i = 0; i < 4; i++)
        {
            next.x = now.x + d[i][0];
            next.y = now.y + d[i][1];
            if(Check(next.x, next.y, next.step))
            {
                add(now.x, now.y, i, next.step);
            }
        }
    }
}

int main()
{
    int T;
    long long room = sizeof(cnt);
    scanf("%d", &T);
    while(T--)
    {
        memset(cnt, -1, room);
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
        {
            scanf("%s", &G[i]);
            for(int j = 0; j < m; j++)
            {
                if(G[i][j] == '>' || G[i][j] == '<' || G[i][j] == '^' || G[i][j] == 'v')
                {
                    sx = i;
                    sy = j;
                }
                if(G[i][j] == 'C')
                {
                    ex = i;
                    ey = j;
                }
            }
        }
        int dir;
        if(G[sx][sy] == '>')
            dir = 1;
        else if(G[sx][sy] == '<')
            dir = 3;
        else if(G[sx][sy] == '^')
            dir = 0;
        else if(G[sx][sy] == 'v')
            dir = 2;
        bfs(dir);



        for(int i = 0; i < n; i++)
            printf("%s\n", G[i]);
    }
    return 0;
}
