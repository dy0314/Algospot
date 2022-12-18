/* https://www.algospot.com/judge/problem/read/TILING2 */

#include <stdio.h>
#include <memory.h>

const int MOD = 1000000007;
const int MAX_TILE_SIZE = 111;
int N;
int cache[MAX_TILE_SIZE];

int sol(int n)
{
    if(n == N)
        return 1;
    if(n > N)
        return 0; 

    int &ret = cache[n];
    if(ret != -1)
        return ret;
    // 타일을 세로로 쓰는 경우 + 타일을 가로로 2개 쓰는 경우
    ret = (sol(n+1) % MOD) + (sol(n+2) % MOD);

    return ret % MOD;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    
    while(C--)
    {
        int n;
        scanf("%d", &N);
        memset(cache, -1, sizeof(cache));
        printf("%d\n", sol(0));
    }
    return 0;
}