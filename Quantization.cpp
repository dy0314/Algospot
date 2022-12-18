#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_SEQ_SIZE = 111;
const int MAX_QUAN_SIZE = 11;
const int INF = 987654321;

int N, S;
int num[MAX_SEQ_SIZE];
int cache[MAX_SEQ_SIZE][MAX_QUAN_SIZE];
vector<int> vt(MAX_SEQ_SIZE);

int minQuan(int startPos, int endPos)
{
    int ret = INF;

    // vt[startPos] ~ vt[endPos] 사이에 있는 모든 값으로 최소값을 구한다.
    // vt를 정렬했기 때문에 startPos~endPos 사이에서 무조건 답이 있다.
    for (int num = vt[startPos]; num <= vt[endPos]; num++)
    {
        int sum = 0;
        for (int i = startPos; i <= endPos; i++)
        {
            int sub = (vt[i] - num);
            sum += sub * sub;
        }
        ret = min(ret, sum);
    }
    return ret;
}

int sol(int curPos, int orderOfQuan)
{
    if (curPos == N)
        return 0;
    if (orderOfQuan == S)
        return INF;

    int &ret = cache[curPos][orderOfQuan];

    if (ret != -1)
        return ret;
    ret = INF;

    for (int endPos = curPos; endPos < N; endPos++)
    {
        ret = min(ret, sol(endPos + 1, orderOfQuan + 1) + minQuan(curPos, endPos));
    }

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        scanf("%d %d", &N, &S);
        for (int i = 0; i < N; i++)
        {
            int tmp;
            scanf("%d", &tmp);
            vt[i] = tmp;
        }
        memset(cache, -1, sizeof(cache));
        sort(&vt[0], &vt[N]);

        printf("%d\n", sol(0, 0));
    }

    return 0;
}