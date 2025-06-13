#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "util.h"
#include "player.h"

int WIDTH, HEIGHT;
char **maze;
int goalX, goalY;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

// 再帰的に迷路を掘って生成する深さ優先探索アルゴリズム（DFS）
void dfs(int x, int y) 
{
    int dirs[4] = { 0, 1, 2, 3 };
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) 
    {
        int nx = x + dx[dirs[i]] * 2;
        int ny = y + dy[dirs[i]] * 2;

        if (nx >= 1 && nx < WIDTH - 1 && ny >= 1 && ny < HEIGHT - 1 && maze[ny][nx] == '#') 
        {
            maze[y + dy[dirs[i]]][x + dx[dirs[i]]] = ' ';
            maze[ny][nx] = ' ';
            dfs(nx, ny);
        }
    }
}

// 指定座標の周囲にある壁('#')の数をカウントする関数
int countAdjacentWalls(int x, int y) 
{
    int count = 0;
    for (int i = 0; i < 4; i++) 
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && maze[ny][nx] == '#') 
        {
            count++;
        }
    }
    return (count);
}

// 通路のループ（回り道）をランダムに追加して、単調な迷路を回避
void addLoops(int loopCount) 
{
    for (int i = 0; i < loopCount; i++) 
    {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        if (maze[y][x] == '#' && 
            maze[y-1][x] == ' ' && maze[y+1][x] == ' ') 
            {
            maze[y][x] = ' ';
        }
        if (maze[y][x] == '#' && 
            maze[y][x-1] == ' ' && maze[y][x+1] == ' ') 
            {
            maze[y][x] = ' ';
        }
    }
}

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

    playerX = startX;
    playerY = startY;

    goalX = WIDTH - 2;
    goalY = HEIGHT - 2;
    maze[goalY][goalX] = ' ';

    // 迷路にランダムでループを追加
    //addLoops(30);
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