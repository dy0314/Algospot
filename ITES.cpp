/* https://www.algospot.com/judge/problem/read/ITES */

#include <stdio.h>
#include <queue>
#include <cmath>

using namespace std;

const long MOD = pow(2, 32);

long generateNextA(long prevA)
{
    long nextA = (prevA * 214013 + 2531011) % MOD;
    return nextA;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        queue<int> qu;
        long A = 1983;
        int K, N;
        int cnt = 0;
        int sum = 0;
        int i = 1;

        scanf("%d %d", &K, &N); 
        while (i <= N)
        {
            if (sum < K)
            {
                int signal = A % 10000 + 1;
                qu.push(signal);
                sum += signal;
                i++;
                A = generateNextA(A);
                continue;
            }

            if (sum == K)
                cnt++;

            sum -= qu.front();
            qu.pop();

        }
        printf("%d\n", cnt);
    }

    return 0;
}