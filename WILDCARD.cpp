/* https://www.algospot.com/judge/problem/read/WILDCARD */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int MAX_STR = 111;

char wildCard[MAX_STR];
char str[50][MAX_STR];
int cache[MAX_STR][MAX_STR];

int N;
int strNum;

bool sol(int idxWildCard, int idxStr)
{
    if(cache[idxWildCard][idxStr] != -1) {        
        return cache[idxWildCard][idxStr] == 1 ? true : false;
    }
    
    // 기저사례 1. 와일드카드와 문자열 모두 끝에 도착한 경우
    if (idxWildCard == strlen(wildCard) && idxStr == strlen(str[strNum]))
        return true;
    // 기저사례 2. 와일드카드 또는 문자열이 끝에 도착한 경우
    if (idxWildCard == strlen(wildCard) || idxStr == strlen(str[strNum]))
    {
        // 와일드카드가 *만 남은 경우 참이 될  수 있다.
        if (idxWildCard == strlen(wildCard) - 1 && wildCard[strlen(wildCard) - 1] == '*')
            return true;
        // 그외에는 모두 false
        return false;
    }

    bool ret = false;

    // 와일드카드가 *인 경우
    if (wildCard[idxWildCard] == '*')
    {
        // 두 가지 경우를 시도해 본다. (*를 사용 or 패스)
        ret = sol(idxWildCard, idxStr + 1) | sol(idxWildCard + 1, idxStr);
    }
    else if (wildCard[idxWildCard] == '?')
    {
        ret = sol(idxWildCard + 1, idxStr + 1);
    }
    else
    {
        if (wildCard[idxWildCard] == str[strNum][idxStr])
            ret = sol(idxWildCard + 1, idxStr + 1);
    }

    cache[idxWildCard][idxStr] = ret;

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    while (C--)
    {
        scanf("%s", wildCard);
        scanf("%d", &N);
        vector<string> result;

        for (int i = 0; i < N; i++)
        {
            strNum = i;
            scanf("%s", str[i]);
            memset(cache, -1, sizeof(cache));

            if (sol(0, 0))
                result.push_back(string(str[i]));
        }

        sort(result.begin(), result.end());
        
        for (int i = 0; i < result.size(); i++)
            cout << result[i] << endl;
    }

    return 0;
}