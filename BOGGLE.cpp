
/* BOGGLE 보글 게임 https://www.algospot.com/judge/problem/read/BOGGLE */

#include <cstdio>
#include <cstring>

const int MAX_ROW = 5;
const int MAX_COL = 5;

const int MAX_WORD_CNT = 10;
const int MAX_WORD_LEN = 11;

char map[MAX_ROW][MAX_COL + 1];
char word[MAX_WORD_CNT][MAX_WORD_LEN];

int cache[MAX_WORD_LEN][MAX_ROW][MAX_COL];

int dirX[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int dirY[8] = {0, 0, -1, 1, 1, -1, 1, -1};

char *currentWord;

bool isEqualAlphabet(char currentPositionCharacter, char wordCharacter)
{
    return currentPositionCharacter == wordCharacter ? true : false;
}

bool isOutMapBoundary(int x, int y)
{
    return (x < 0 || x >= MAX_COL || y < 0 || y >= MAX_ROW) ? true : false;
}

bool searchWord(int currentY, int currentX, int currentWordPosition)
{
    // memoization
    if (cache[currentWordPosition][currentY][currentX] != -1)
        return cache[currentWordPosition][currentY][currentX] == 1 ? true : false;

    // base case
    if (currentWord[currentWordPosition] == '\0')
    {
        // printf("found %s!\n", currentWord);
        return true;
    }

    bool ret = false;

    // 8방향 검색
    for (int dir = 0; dir < 8; dir++)
    {
        int nextX = currentX + dirX[dir];
        int nextY = currentY + dirY[dir];

        // map범위 체크
        if (isOutMapBoundary(nextX, nextY))
            continue;

        if (isEqualAlphabet(map[nextY][nextX], currentWord[currentWordPosition]))
        {
            ret = searchWord(nextY, nextX, currentWordPosition + 1);
            cache[currentWordPosition + 1][nextY][nextX] = ret ? 1 : 0;

            if (ret)
                return ret;
        }
    }

    return ret;
}

int main(void)
{
    int C, N;
    scanf("%d", &C);

    for (int tc = 0; tc < C; tc++)
    {
        for (int i = 0; i < 5; i++)
            scanf("%s", map[i]);

        scanf("%d", &N);

        for (int i = 0; i < N; i++)
            scanf("%s", word[i]);

        for (int n = 0; n < N; n++)
        {
            // init
            memset(cache, -1, sizeof(cache));
            currentWord = word[n];
            bool isFound = false;

            // set start point
            for (int i = 0; i < MAX_ROW; i++)
            {
                for (int j = 0; j < MAX_COL; j++)
                {
                    // 첫 알파벳이 맞을 때 탐색 시작
                    if (isEqualAlphabet(map[i][j], word[n][0]) && searchWord(i, j, 1))
                    {
                        isFound = true;
                        break;
                    }
                }
                if (isFound)
                    break;
            }
            printf("%s %s\n", currentWord, isFound ? "YES" : "NO");
        }
    }

    return 0;
}