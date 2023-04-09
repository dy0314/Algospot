/* https://www.algospot.com/judge/problem/read/NUMB3RS# */
#include <stdio.h>
#include <memory.h>

const int MAX_TOWN = 51;
const int MAX_DAY = 101;

int townMap[MAX_TOWN][MAX_TOWN];
double cache[MAX_DAY][MAX_TOWN];
int numOfConnectedTown[MAX_TOWN];

int n, d, p;

bool isTownConnected(int townA, int townB)
{
    return townMap[townA][townB] == 1 ? true : false;
}

double sol(int day, int townNum)
{
    // 기저사례 
    if (day == 0)
    {
        return townNum ==p ? 1.0 : 0.0;        
    }

    double &ret = cache[day][townNum];

    // 실수는 정확히 비교(==) 하기가 어렵기 때문에 대소로 비교한다.
    if (ret > -0.5)
        return ret;
    ret = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (isTownConnected(townNum, i))
        {
            ret += sol(day - 1, i) * (1.0 / (double)numOfConnectedTown[i]);
        }
    }

    return ret;
}

void reset()
{
    memset(numOfConnectedTown, 0, sizeof(numOfConnectedTown));
    for (int i = 0; i < MAX_DAY; i++)
    {
        for (int j = 0; j < MAX_TOWN; j++)
        {
            cache[i][j] = -1;
        }
    }
}

int main(void)
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        reset();

        scanf("%d %d %d", &n, &d, &p);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &townMap[i][j]);
                numOfConnectedTown[i] += townMap[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            sol(d, i);
        }

        int q;
        scanf("%d", &q);
        while (q--)
        {
            int town;
            scanf("%d", &town);
            printf("%.8lf ", cache[d][town]);
        }
        printf("\n");
    }

    return 0;
}