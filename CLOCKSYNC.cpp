/* https://www.algospot.com/judge/problem/read/CLOCKSYNC */

#include <stdio.h>
#include <vector>

const int INF = 987654321;
const int MAX_CLOCK = 16;
const int MAX_CLOCK_INX = 5;
const int MAX_SWITCH = 10;

using namespace std;

const int switchingClock[MAX_SWITCH][MAX_CLOCK_INX] = {
    {0, 1, 2, -1, -1},
    {3, 7, 9, 11, -1},
    {4, 10, 14, 15, -1},
    {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12},
    {0, 2, 14, 15, -1},
    {3, 14, 15, -1, -1},
    {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},
    {3, 4, 5, 9, 13}};

int clockState[MAX_CLOCK];

void pushSwitch(int switchNum)
{
    for (int clockIdx = 0; clockIdx < MAX_CLOCK_INX; clockIdx++)
    {
        int clockNum = switchingClock[switchNum][clockIdx];
        if (clockNum == -1)
            break;

        clockState[clockNum] = (clockState[clockNum] + 3) % 12;

        if (clockState[clockNum] == 0)
            clockState[clockNum] = 12;
    }
}

bool allClockIsTwelve()
{
    for (int i = 0; i < MAX_CLOCK; i++)
    {
        if (clockState[i] != 12)
            return false;
    }
    return true;
}

int sol(int currentSwitch)
{
    int ret = INF;
    if (currentSwitch == MAX_SWITCH)
    {
        if (allClockIsTwelve())
            return 0;
        return ret;
    }

    for (int i = 0; i < 4; i++)
    {
        ret = min(ret, sol(currentSwitch + 1) + i);
        pushSwitch(currentSwitch);
    }

    return ret;
}

int main(void)
{
  
    int C;
    scanf("%d", &C);

    for (int tc = 0; tc < C; tc++)
    {
        for (int clockNum = 0; clockNum < MAX_CLOCK; clockNum++)
        {
            scanf("%d", &clockState[clockNum]);
        }

        int result = INF;
        result = min(result, sol(0));

        if (result == INF)
            result = -1;

        printf("%d\n", result);
    }

    return 0;
}