#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "util.h"
#include "player.h"
#include "dfs.h"
#include "wilson.h"
#include "prim.h"

int WIDTH, HEIGHT;
char **maze;
int goalX, goalY;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

// 迷路用の2次元配列を動的に確保する関数
void allocateMaze() 
{
    maze = (char **)malloc(sizeof(char *) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) 
    {
        maze[i] = (char *)malloc(sizeof(char) * WIDTH);
    }
}

// 確保した迷路配列を解放する関数
void freeMaze() 
{
    for (int i = 0; i < HEIGHT; i++) 
    {
        free(maze[i]);
    }
    free(maze);
}

// 迷路とプレイヤー・ゴールの現在の状態をターミナルに表示する関数
void printMaze() 
{
    system("clear");
    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            if (x == playerX && y == playerY) 
            {
                putchar('P');
            } else if (x == goalX && y == goalY) 
            {
                putchar('G');
            } else 
            {
                putchar(maze[y][x]);
            }
        }
        putchar('\n');
    }

    printf("\n移動回数: %d\n", moveCount);
    printf("現在位置: (%d, %d)\n", playerX, playerY);
    printf("WASDで移動。ゴール = G\n");
}

// 迷路を生成する関数（初期化 → 掘る → スタート/ゴール設定 → ループ追加）
void generateMaze() 
{
    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            maze[y][x] = '#';
        }
    }

    int startX = 1, startY = 1;
    maze[startY][startX] = ' ';
    dfs(startX, startY);
    //prim(startX, startY);
    //wilson();

    playerX = startX;
    playerY = startY;

    goalX = WIDTH - 2;
    goalY = HEIGHT - 2;
    maze[goalY][goalX] = ' ';
}