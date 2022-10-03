/* https://www.algospot.com/judge/problem/read/TRIANGLEPATH */

#include <stdio.h>
#include <memory.h>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 101;

int n;
int triangle[MAX_SIZE][MAX_SIZE];
int cache[MAX_SIZE][MAX_SIZE];

int sol(int currentY, int currentX)
{
    if(currentY == n)
        return 0;
    
    int &ret = cache[currentY][currentX];
    if(ret != -1)
        return ret;

    // 아래로 내려가는 경우와 오른쪽 아래로 내려가는 경우 중 최대 값을 취한다.
    ret = triangle[currentY][currentX] + max(sol(currentY+1, currentX), sol(currentY+1, currentX+1));
    // 최대값을 캐싱한다.
    
    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i + 1; j++)
            {
                scanf("%d", &triangle[i][j]);
            }
        }

        memset(cache, -1, sizeof(cache));
        printf("%d\n", sol(0,0));
    }

    return 0;
}