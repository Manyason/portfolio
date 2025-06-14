#include <stdbool.h>
#include <stdlib.h>
#include "maze.h"
#include "util.h"
#include "wilson.h"

bool isInside(int x, int y) 
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// ループを消したランダムウォークを生成
int loopErasedWalk(Point *path, int startX, int startY) 
{
    Point walk[WIDTH * HEIGHT];
    int step = 0;

    int x = startX, y = startY;
    int visitedMap[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            visitedMap[i][j] = -1;

    while (maze[y][x] != ' ') 
    {
        walk[step].x = x;
        walk[step].y = y;
        visitedMap[y][x] = step;
        step++;

        int dirs[4] = { 0, 1, 2, 3 };
        shuffle(dirs, 4); // 上下左右をランダムに

        bool moved = false;
        for (int i = 0; i < 4; i++) 
        {
            int nx = x + dx[dirs[i]] * 2;
            int ny = y + dy[dirs[i]] * 2;

            if (isInside(nx, ny)) 
            {
                // ループ発見：巻き戻し
                if (visitedMap[ny][nx] != -1) 
                {
                    step = visitedMap[ny][nx] + 1;
                }

                x = nx;
                y = ny;
                moved = true;
                break;
            }
        }

        if (!moved) break; // 動けなければ終了（念のため）
    }

    for (int i = 0; i < step; i++) 
    {
        path[i] = walk[i];
    }

    return step;
}

void wilson(int startX, int startY) 
{
    while (1) 
    {
        // ランダムな奇数座標（通路候補）を選択
        int x = rand() % ((WIDTH - 1) / 2) * 2 + 1;
        int y = rand() % ((HEIGHT - 1) / 2) * 2 + 1;

        if (maze[y][x] == ' ') continue;

        Point path[WIDTH * HEIGHT];
        int length = loopErasedWalk(path, x, y);

        for (int i = 0; i < length - 1; i++) 
        {
            int x1 = path[i].x, y1 = path[i].y;
            int x2 = path[i + 1].x, y2 = path[i + 1].y;
            int mx = (x1 + x2) / 2;
            int my = (y1 + y2) / 2;

            maze[y1][x1] = ' ';
            maze[my][mx] = ' ';
            maze[y2][x2] = ' ';
        }

        // 終了条件チェック：全マス訪問済みか？
        bool allVisited = true;
        for (int y = 1; y < HEIGHT; y += 2)
            for (int x = 1; x < WIDTH; x += 2)
                if (maze[y][x] == '#')
                    allVisited = false;

        if (allVisited) break;
    }
}