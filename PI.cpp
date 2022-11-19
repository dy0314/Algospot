/* https://www.algospot.com/judge/problem/read/PI */
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const int MAX_LEN = 10001;
char PI[MAX_LEN];
int cache[MAX_LEN];
size_t piLen;

bool isLevelOne(int curPos, int endPos)
{
    for (int i = curPos; i <= endPos; i++)
    {
        if ((PI[curPos]) != PI[i])
            return false;
    }
    return true;
}

bool isLevelTwo(int curPos, int endPos)
{
    for (int i = curPos + 1; i <= endPos; i++)
    {
        if (PI[curPos + 1] - PI[curPos] != PI[i] - PI[i - 1])
            return false;
    }

    if(PI[curPos + 1] - PI[curPos] == 1 || PI[curPos + 1] - PI[curPos] == -1)
        return true;
    
    return false;
}

bool isLevelFour(int curPos, int endPos)
{
    char switchNum[2] = {PI[curPos], PI[curPos + 1]};
    
    int k = 0;
    for (int i = curPos; i <= endPos; i++)
    {
        if (PI[i] != switchNum[k % 2])
            return false;
        k++;
    }
    return true;
}

bool isLevelFive(int curPos, int endPos)
{
    int diff = PI[curPos + 1] - PI[curPos];

    for (int i = curPos + 1; i <= endPos; i++)
    {
        if (PI[i] - PI[i - 1] != diff)
            return false;
    }
    return true;
}

int getMinLevel(int curPos, int endPos)
{
    if (isLevelOne(curPos, endPos))
        return 1;
    if (isLevelTwo(curPos, endPos))
        return 2;
    if (isLevelFour(curPos, endPos))
        return 4;
    if (isLevelFive(curPos, endPos))
        return 5;

    return 10;
}

int sol(int curPos)
{
    if (curPos == piLen) // base case
        return 0;

    int &ret = cache[curPos]; // curPos에서 이전에 난이도를 계산한적이 있으면 항상 그 결과는 같다.
    if (ret != INF)
        return ret;

    for (int i = 3; i <= 5; i++)
    {
        int endPos = curPos + i - 1;
        if (endPos < piLen) // 문자열을 [curPos, endPos] 까지와 [endPos+1, ...]로 문제를 구분한다.
            ret = min(ret, sol(endPos + 1) + getMinLevel(curPos, endPos));
    }

    return ret;
}

int main(void)
{
    int tc;
    scanf("%d", &tc);
    while (tc--)
    {
        scanf("%s", PI);
        piLen = strlen(PI);
        for (int i = 0; i < MAX_LEN; i++)
            cache[i] = INF;

        printf("%d\n", sol(0));
    }

    return 0;
}