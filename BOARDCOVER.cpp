/* BOARDCOVER 게임판 덮기 https://www.algospot.com/judge/problem/read/BOARDCOVER */

#include <stdio.h>

const int MAX_BOARD_SIZE = 22;
const int BLOCK_TYPE = 4;

char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int H, W;

// L자 모양 블록을 회전 시켰을 때 모든 모양
int block1_X[BLOCK_TYPE] = {0,1,0,0};
int block1_Y[BLOCK_TYPE] = {1,0,1,1};

int block2_X[BLOCK_TYPE] = {1,1,1,-1};
int block2_Y[BLOCK_TYPE] = {0,1,1,1};


// 흰칸인 경우 블록을 넣을 곳으로 선택
void findBlockPosition(int& currentX, int& currentY)
{
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            if (board[y][x] == '.') 
            {
                currentX = x;
                currentY = y;
                return;
            }
        }
    }

    // base case
    currentX = currentY = -1;
    return;
}

bool isBlockFit(int currentX, int currentY, int blockIdx)
{
    int candidateBlock1_X = currentX + block1_X[blockIdx];
    if (candidateBlock1_X >= W || candidateBlock1_X < 0)
        return false;

    int candidateBlock1_Y = currentY + block1_Y[blockIdx];
    if (candidateBlock1_Y >= H || candidateBlock1_Y < 0)
        return false;

    if (board[candidateBlock1_Y][candidateBlock1_X] != '.')
        return false;

    int candidateBlock2_X = currentX + block2_X[blockIdx];
    if (candidateBlock2_X >= W || candidateBlock2_X < 0)
        return false;

    int candidateBlock2_Y = currentY + block2_Y[blockIdx];
    if (candidateBlock2_Y >= H || candidateBlock2_Y < 0)
        return false;

    if (board[candidateBlock2_Y][candidateBlock2_X] != '.')
        return false;

    return true;
}

void putBlock(int currentX, int currentY, int blockIdx)
{
    int candidateBlock1_X = currentX + block1_X[blockIdx];
    int candidateBlock1_Y = currentY + block1_Y[blockIdx];

    int candidateBlock2_X = currentX + block2_X[blockIdx];
    int candidateBlock2_Y = currentY + block2_Y[blockIdx];

    board[currentY][currentX] = board[candidateBlock1_Y][candidateBlock1_X] = board[candidateBlock2_Y][candidateBlock2_X] = 'b';
}

void removeBlock(int currentX, int currentY, int blockIdx)
{
    int candidateBlock1_X = currentX + block1_X[blockIdx];
    int candidateBlock1_Y = currentY + block1_Y[blockIdx];

    int candidateBlock2_X = currentX + block2_X[blockIdx];
    int candidateBlock2_Y = currentY + block2_Y[blockIdx];

    board[currentY][currentX] = board[candidateBlock1_Y][candidateBlock1_X] = board[candidateBlock2_Y][candidateBlock2_X] = '.';
}

void printBlock()
{
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            printf("%c", board[y][x]);
        }
        printf("\n");
    }
}
int sol()
{
    int currentX, currentY;
    findBlockPosition(currentX, currentY);

    // base case
    if (currentX == -1 && currentY == -1)
        return 1;

    int ret = 0;
    for (int i = 0; i < BLOCK_TYPE; i++)
    {

        if (isBlockFit(currentX, currentY, i))
        {
            // 블록 넣기
            putBlock(currentX, currentY, i);
            ret += sol();
            // 블록 빼기
            removeBlock(currentX, currentY, i);            
        }
    }

    return ret;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    for (int tc = 0; tc < C; tc++)
    {
        scanf("%d %d", &H, &W);

        for (int y = 0; y < H; y++)
        {
            scanf("%s", board[y]);
        }

        int ret = sol();
        printf("%d\n", ret);
    }

    return 0;
}