/* https://www.algospot.com/judge/problem/read/JLIS */
#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <limits.h>

using namespace std;

const int MAX_SEQ = 111;

long long int A[MAX_SEQ];
long long int B[MAX_SEQ];
int cache[MAX_SEQ][MAX_SEQ];
int n, m;

int sol(int currentA, int currentB)
{
    int& ret = cache[currentA][currentB];
    if(ret != 0)
        return ret;

    long long int currentBigNum = A[currentA] > B[currentB] ? A[currentA] : B[currentB];

    // A에 있는 수 선택하는 경우
    for (int indexA = currentA + 1; indexA <= n; indexA++)
    {
        if(currentBigNum < A[indexA]) // 현재 가장 큰 수보다 큰 수를 선택
            ret = max(ret, sol(indexA, currentB) + 1);
    }

    // B에 있는 수 선택하는 경우
    for (int indexB = currentB + 1; indexB <= m; indexB++)
    {
        if(currentBigNum < B[indexB]) // 현재 가장 큰 수보다 큰 수를 선택
            ret = max(ret, sol(currentA, indexB) + 1);
    }

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    while (C--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", &A[i]);
        }

        for (int i = 1; i <= m; i++)
        {
            scanf("%lld", &B[i]);
        }

        A[0] = B[0] = LONG_LONG_MIN; // sol(0,0)부터 시작하기 위해 long long int type중 가장 작은 값을 넣어준다.
        memset(cache, 0, sizeof(cache)); // cache를 0으로 초기화 하면 sol함수에서 귀찮은 예외처리를 제거할 수 있다.
        printf("%d\n", 
        sol(0, 0));
    }

    return 0;
}