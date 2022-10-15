/* https://www.algospot.com/judge/problem/read/LIS */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
    int C;
    int N;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d", &N);
        vector<int> LIS;

        for (int i = 0; i < N; i++)
        {
            int subsequence;
            scanf("%d", &subsequence);

            vector<int>::iterator lowPosition = lower_bound(LIS.begin(), LIS.end(), subsequence);
            // subsequence보다 같거나 큰 값중 가장 작은 값의 위치를 구한다

            int lengthOfLIS = lowPosition - LIS.begin();

            if (lengthOfLIS == LIS.size())
            {
                // subsequence보다 같거나 큰 값중 가장 작은 값의 위치가 없는 경우(LIS 끝에 값을 추가해야 하는 상황)
                LIS.push_back(subsequence);
                continue;
            }

            LIS[lengthOfLIS] = subsequence;
            // LIS 길이(lengthOfLIS) 중 끝 값이 가장 작은 값으로 업데이트 한다.
        }
        printf("%u\n", LIS.size());
    }
    return 0;
}
