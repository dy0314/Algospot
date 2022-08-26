/* https://www.algospot.com/judge/problem/read/FENCE */

#include <stdio.h>
#include <algorithm>
#include <string.h>

const int MAX_FENCE = 20002;
using namespace std;

int N;
int fenceHeight[MAX_FENCE];
int highestFence;

int getLowestHeight(int a, int b)
{
    int lowestHeight = 10000;
    for (int i = a; i <= b; i++)
    {
        lowestHeight = min(lowestHeight, fenceHeight[i]);
    }

    return lowestHeight;
}

int calculateMaxArea(int a, int b)
{
    int lowestHeight = getLowestHeight(a, b);
    return (b - a + 1) * lowestHeight;
}

int sol(int bottom, int top)
{
    if (bottom == top)
        return fenceHeight[bottom];

    int mid = (top + bottom) / 2;

    int leftIdx, rightIdx;
    int ret = fenceHeight[mid];
    leftIdx = rightIdx = mid;

    // mid
    while (leftIdx > bottom || rightIdx < top)
    {
        if (leftIdx > bottom && rightIdx < top)
        {
            if (fenceHeight[leftIdx - 1] > fenceHeight[rightIdx + 1])
            {
                leftIdx--;
                ret = max(ret, calculateMaxArea(leftIdx, rightIdx));
            }
            else
            {
                rightIdx++;
                ret = max(ret, calculateMaxArea(leftIdx, rightIdx));
            }
        }
        else
        {
            if (leftIdx > bottom)
            {
                leftIdx--;
                ret = max(ret, calculateMaxArea(leftIdx, rightIdx));
            }
            if (rightIdx < top)
            {
                rightIdx++;
                ret = max(ret, calculateMaxArea(leftIdx, rightIdx));
            }
        }
    }

    // left
    ret = max(ret, sol(bottom, mid));
    // right
    ret = max(ret, sol(mid + 1, top));

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    for (int tc = 0; tc < C; tc++)
    {
        scanf("%d", &N);
        highestFence = 0;
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &fenceHeight[i]);
        }
        printf("%d\n", sol(0, N - 1));
    }

    return 0;
}