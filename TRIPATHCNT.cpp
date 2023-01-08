/* https://www.algospot.com/judge/problem/read/TRIPATHCNT */

#include <stdio.h>
#include <memory.h>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 101;

int n;
int triangle[MAX_SIZE][MAX_SIZE];
int cache[MAX_SIZE][MAX_SIZE];
int cacheCnt[MAX_SIZE][MAX_SIZE];

int solMaxPathSum(int currentY, int currentX)
{
    if (currentY == n)
        return 0;

    int &ret = cache[currentY][currentX];
    if (ret != -1)
        return ret;

    // 아래로 내려가는 경우와 오른쪽 아래로 내려가는 경우 중 최대 값을 취한다.
    ret = triangle[currentY][currentX] + max(solMaxPathSum(currentY + 1, currentX), solMaxPathSum(currentY + 1, currentX + 1));
    // 최대값을 캐싱한다.

    return ret;
}

int solMaxPathCnt(int currentY, int currentX)
{
    if (currentY == n - 1)
        return 1;

    int &ret = cacheCnt[currentY][currentX];
    if (ret != 0)
        return ret;

    // 아래로 이동하는 경우 최대 합
    int firstPathResult = solMaxPathSum(currentY + 1, currentX);
    // 우측아래로 이동하는 경우 최대 합
    int secondPathResult = solMaxPathSum(currentY + 1, currentX + 1);

    if (firstPathResult > secondPathResult)
        ret += solMaxPathCnt(currentY + 1, currentX);
    else if (firstPathResult < secondPathResult)
        ret += solMaxPathCnt(currentY + 1, currentX + 1);
    else // 두 경우의 최대 합이 같은 경우 경우의 수를 더해준다.
        ret += solMaxPathCnt(currentY + 1, currentX) + solMaxPathCnt(currentY + 1, currentX + 1);

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
        memset(cacheCnt, 0, sizeof(cacheCnt));

        printf("%d\n", solMaxPathCnt(0, 0));
    }

    return 0;
}