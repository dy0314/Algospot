/* 소풍 PICNIC https://www.algospot.com/judge/problem/read/PICNIC */

#include <stdio.h>
#include <memory.h>
#include <vector>

using namespace std;

const int MAX_CHILDREN = 10;
bool isPair[MAX_CHILDREN];
int C, n, m, ret;

void init()
{   
    ret = 0;
    memset(isPair, false, sizeof(isPair));
}

bool isAllMatched(void)
{
    for (int i = 0; i < n; i++)
    {
        if (!isPair[i])
            return false;
    }
    return true;
}

bool hasPair(int index)
{
    return isPair[index];
}

void sol(vector<vector<int> > &friendship, int currentChild)
{
    isPair[currentChild] = true;
    
    for (size_t i = 0; i < friendship[currentChild].size(); i++)
    {
        int friendIndex = friendship[currentChild][i];

        // 선택하려는 친구가 이미 친구가 있는 경우
        if(hasPair(friendIndex))
            continue;

        isPair[friendIndex] = true;
        bool hasNext = false;

        for(int nextChild = currentChild + 1; nextChild < n; nextChild++) 
        {
            // nextChild가 이미 친구가 있는 경우
            if(hasPair(nextChild))
                continue;        
            sol(friendship, nextChild);
            hasNext = true;
        }

        if(!hasNext && isAllMatched())
        {
            //printf("base case\n");
            ret++;
        }

        isPair[friendIndex] = false;
    }

    isPair[currentChild] = false;
}

int main(void)
{
    scanf("%d", &C);
    for (int tc = 0; tc < C; tc++)
    {
        init();
        vector<vector<int> > friendship(MAX_CHILDREN);

        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            scanf("%d %d", &a, &b);

            // 친구 관계를 vector로 표현.
            if (a > b) // (3, 0)과 같은 경우를 제거하기 위해
                friendship[b].push_back(a);
            else
                friendship[a].push_back(b);
        }
        sol(friendship, 0);
        printf("%d\n", ret);
    }

    return 0;
}