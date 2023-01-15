/* https://www.algospot.com/judge/problem/read/SNAIL */
#include <stdio.h>

const int MAX_DAYS = 1001;
const int MAX_METER = 2002;
int n, m;

// x일 동안 y미터 이동했을 때의 확률을 캐싱한다.
double cache[MAX_DAYS][MAX_METER];

double sol(int days, int totMeter)
{
    if (days == m)
    {
        if (totMeter >= n)
            return 1;
        else
            return 0;
    }

    double &ret = cache[days][totMeter];
    if (ret != -1.0)
    {
        return ret;
    }
    ret = 0;

    // 비가올 확률과 비가오지 않을 확률을 나눠서 더한다.
    ret = (sol(days + 1, totMeter + 2) * 0.75) + (sol(days + 1, totMeter + 1) * 0.25);

    return ret;
}

void resetCache()
{
    for (int i = 0; i < MAX_DAYS; i++)
    {
        for (int j = 0; j < MAX_METER; j++)
        {
            cache[i][j] = -1.0;
        }
    }
}

int main(void)
{
    int TC;
    scanf("%d", &TC);

    while (TC--)
    {
        scanf("%d %d", &n, &m);
        resetCache();

        // 절대 도달할 수 없는 경우는 속도 개선을 위해 가지치기 한다.
        if (2 * m < n)
            printf("%.10f\n", 0.0);
        else
            printf("%.10f\n", sol(0, 0));
    }

    return 0;
}