#include <stdio.h>
#include <memory.h>

const int MAX_BLOCK = 101;
const int MOD = 10000000;

int cache[MAX_BLOCK][MAX_BLOCK];
int n;

int sol(int leftBlock, int prevUsedBlock)
{
    if (leftBlock == 0)
        return 1;

    int &ret = cache[prevUsedBlock][leftBlock];
    if (ret != -1)
        return ret;
    ret = 0;

    for (int usedBlock = 1; usedBlock <= leftBlock; usedBlock++)
    {
        int maxShift = prevUsedBlock + usedBlock - 1;
        ret += sol(leftBlock - usedBlock, usedBlock) * maxShift;
        ret %= MOD;
    }

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    while (C--)
    {
        memset(cache, -1, sizeof(cache));
        scanf("%d", &n);
        int ret = 0;
        for (int usedBlock = 1; usedBlock <= n; usedBlock++)
        {
            ret += sol(n - usedBlock, usedBlock);
            ret %= MOD;
        }
        printf("%d\n", ret);
    }
    return 0;
}