#include <stdbool.h>
#include <stdlib.h>
#include "maze.h"
#include "util.h"
#include "wilson.h"

bool isInside(int x, int y) 
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// ランダムウォークの経路を記録し、ループを消して返す
int loopErasedWalk(Point *path, int startX, int startY) 
{
    Point walk[WIDTH * HEIGHT];
    int step = 0;

    int x = startX, y = startY;

    // 各マスの訪問マップ（経路上での最後の位置を記録）
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
        shuffle(dirs, 4); // 方向をランダムに

        for (int i = 0; i < 4; i++) 
        {
            int nx = x + dx[dirs[i]] * 2;
            int ny = y + dy[dirs[i]] * 2;

            if (isInside(nx, ny)) 
            {
                x = nx;
                y = ny;

                // ループがあれば巻き戻す
                if (visitedMap[y][x] != -1) 
                {
                    step = visitedMap[y][x] + 1;
                }

                break;
            }
        }
    }

    // ループの消えたパスを path にコピー
    for (int i = 0; i < step; i++) 
    {
        path[i] = walk[i];
    }

    return (step);
}

// Wilson法による迷路生成
void wilson(int startX, int startY) 
{
    // 未訪問セルがある限り繰り返す
    while (1) 
    {
        int x = rand() % ((WIDTH - 1) / 2) * 2 + 1;
        int y = rand() % ((HEIGHT - 1) / 2) * 2 + 1;

        if (maze[y][x] == ' ') continue;

        Point path[WIDTH * HEIGHT];
        int length = loopErasedWalk(path, x, y);

        for (int i = 0; i < length - 1; i++) 
        {
            int x1 = path[i].x;
            int y1 = path[i].y;
            int x2 = path[i + 1].x;
            int y2 = path[i + 1].y;

            int mx = (x1 + x2) / 2;
            int my = (y1 + y2) / 2;

            maze[y1][x1] = ' ';
            maze[my][mx] = ' ';
            maze[y2][x2] = ' ';
        }

        // すべてのマスが訪問済みか確認
        bool allVisited = true;
        for (int y = 1; y < HEIGHT; y += 2)
            for (int x = 1; x < WIDTH; x += 2)
                if (maze[y][x] == '#')
                    allVisited = false;

        if (allVisited) break;
    }
}