/* https://www.algospot.com/judge/problem/read/JUMPGAME */

#include <stdio.h>

const int MAX_MAP_SIZE = 101;

int n;
int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int cache[MAX_MAP_SIZE][MAX_MAP_SIZE];

void init()
{
    for (int i = 0; i < MAX_MAP_SIZE; i++)
    {
        for (int j = 0; j < MAX_MAP_SIZE; j++)
        {
            cache[i][j] = -1;
        }
    }
}

int sol(int currentY, int currentX) {
    // base case
    if(currentY == n-1 && currentX == n-1)
        return 1;

    int& ret = cache[currentY][currentX];
    if(ret != -1)
        return ret;

    // 오른쪽으로 이동
    int moveRight = currentX + map[currentY][currentX];
    if(moveRight < n) {
        ret = sol(currentY, moveRight);
        if(ret)
            return ret;
    }

    // 아래로 이동
    int moveDown = currentY + map[currentY][currentX];
    if(moveDown < n) {
        ret = sol(moveDown, currentX);
        if(ret)
            return ret;
    }

    return 0;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    for (int tc = 0; tc < C; tc++)
    {
        init();
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &map[i][j]);
            }
        }
        int ret = sol(0, 0);
        
        if(ret)
            printf("YES\n");
        else
            printf("NO\n");

    }

    return 0;
}