/* 쿼드 트리 뒤집기 https://www.algospot.com/judge/problem/read/QUADTREE */

#include <stdio.h>
#include <string.h>

char str[1001];
int len;

void inverseNode(int nodeStart[], int nodeEnd[])
{
    char tmpStr[1001];
    // stncpy를 memcpy로 바꿨더니 수행시간이 8ms -> 0ms로 줄었다.
    memcpy(tmpStr, str, len);
    int pos = nodeStart[0];
    int switchOrder[4] = {2, 3, 0, 1};

    // inverse node
    // 0, 1, 2, 3 => 2, 3, 0, 1
    for (int i = 0; i < 4; i++)
    {
        for (int j = nodeStart[switchOrder[i]]; j <= nodeEnd[switchOrder[i]]; j++)
        {
            str[pos++] = tmpStr[j];
        }
    }
}

int divide(int startPosition)
{
    int nodeCnt = 0;
    int nodeStart[4];
    int nodeEnd[4];

    int nextNodeStartPosition = startPosition + 1;
    int nodeLastPosition = 0;

    while (nextNodeStartPosition < len)
    {
        int nextNodeEndPosition = nextNodeStartPosition;

        // x노드면 분할정복 시작
        if (str[nextNodeStartPosition] == 'x')
        {
            // x노드인 경우 다음 node의 End값을 분할정복의 마지막 노드 값으로 설정
            nextNodeEndPosition = divide(nextNodeStartPosition);
        }

        nodeStart[nodeCnt] = nextNodeStartPosition;
        nodeEnd[nodeCnt] = nextNodeEndPosition;
        nodeCnt++;
        
        if (nodeCnt == 4)
        {
            // 분할정복 결과 4개의 노드로 나누어지면 노드를 상하반전 시킴
            inverseNode(nodeStart, nodeEnd);
            nodeLastPosition = nextNodeEndPosition;
            break;
        }

        if (nextNodeStartPosition < nextNodeEndPosition)
            nextNodeStartPosition = nextNodeEndPosition;
        nextNodeStartPosition++;
    }
    return nodeLastPosition;
}

int main(void)
{
    int C;
    scanf("%d", &C);
    for (int tc = 0; tc < C; tc++)
    {
        scanf("%s", str);
        len = strlen(str);
        divide(0);
        printf("%s\n", str);
    }

    return 0;
}