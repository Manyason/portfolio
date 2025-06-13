#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "player.h"
#include "util.h"

int main() 
{
    srand(time(NULL));

    // 入力：迷路サイズ
    printf("迷路の幅（奇数）を入力してください（例: 15）：");
    scanf("%d", &WIDTH);
    printf("迷路の高さ（奇数）を入力してください（例: 15）：");
    scanf("%d", &HEIGHT);

    // 偶数なら+1して奇数に
    if (WIDTH % 2 == 0) WIDTH++;
    if (HEIGHT % 2 == 0) HEIGHT++;

    allocateMaze();
    generateMaze();

    while (1) 
    {
        printMaze();

        if (playerX == goalX && playerY == goalY) 
        {
            printf("ゴール！クリア！\n");
            printf("総移動回数: %d\n", moveCount);
            break;
        }

        char input = getch();
        movePlayer(input);
    }

    freeMaze();
    return (0);
}