/* https://www.algospot.com/judge/problem/read/LIS */

#include <stdio.h>
#include <memory.h>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 555;

int N;
int subsequence[MAX_SIZE];
int cache[MAX_SIZE];

int LIS(int startPosition)
{
    int &ret = cache[startPosition]; // 현재 startPosition에서 LIS 값을 cache에 저장

    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = startPosition + 1; i < N; i++)
    {
        if (subsequence[startPosition] < subsequence[i]) // LIS조건을 만족하기 위해 subsequence[startPosition]보다 큰 값만 추가
        {
            ret = max(ret, LIS(i) + 1);
        }
    }

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &subsequence[i]);
        }
        memset(cache, -1, sizeof(cache));

        int ret = 0;
        for (int i = 0; i < N; i++)
            ret = max(ret, LIS(i) + 1);
        printf("%d\n", ret);
    }
    return 0;
}