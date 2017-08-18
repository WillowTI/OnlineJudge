#include <cstdio>
#include <cstring>

int n, pos;
int a[12];
int b[12];
int c[12];
int state[10][10000000];

int allawake();
int overlap();

int main()
{
    //freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d", &n) && n)
    {
        memset(state, 0, sizeof(state));
        pos = 0;
        for (int i = 0 ; i < n ; i++)
        {
            scanf("%d%d%d", &a[i], &b[i], &c[i]);
            state[i][pos] = c[i];
        }
        pos++;
        int flag = 1;
        int ans = 1;
        while (!allawake())
        {
            int tmp[12];
            int numawake = 0;
            int numsleep = 0;
            for (int i = 0 ; i < n ; i++)
                if (c[i] <= a[i])
                    numawake++;
                else
                    numsleep++;
            for (int i = 0 ; i < n ; i++)
            {
                if (c[i] == a[i])
                {
                    if (numsleep > numawake)
                        tmp[i] = c[i] + 1;
                    else tmp[i] = 1;
                }
                else
                    tmp[i] = c[i] + 1;
                if (tmp[i] > b[i] + a[i])
                    tmp[i] = 1;
            }
            for (int i = 0 ; i < n ; i++)
                c[i] = tmp[i];
            if (overlap())
            {
                flag = 0;
                break;
            }
            else
            {
                for (int i = 0 ; i < n ; i++)
                    state[i][pos] = c[i];
                pos++;
            }
            ans++;
        }
        printf("Case %d: ", cas++);
        if (flag)
            printf("%d\n", ans);
        else
            printf("-1\n");
    }
    return 0;
}

int allawake()
{
    for (int i = 0 ; i <n ; i++)
        if (c[i] > a[i])
            return 0;
    return 1;
}

int overlap()
{
    for (int i = 0 ; i < pos ; i++)
    {
        int flag = 1;
        for (int j = 0 ; j < n ; j++)
            if (state[j][i] != c[j])
            {
                flag = 0;
                break;
            }
        if (flag)
            return 1;
    }
    return 0;
}
