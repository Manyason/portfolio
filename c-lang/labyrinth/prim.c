#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "util.h"
#include "prim.h"

#define MAX_WALLS 10000

void prim(int startX, int startY) 
{
    srand(time(NULL));

    Wall wallList[MAX_WALLS];
    int wallCount = 0;

    for (int i = 0; i < 4; i++) 
    {
        int nx = startX + dx[i] * 2;
        int ny = startY + dy[i] * 2;
        int mx = startX + dx[i];
        int my = startY + dy[i];
        if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1 && maze[ny][nx] == '#') 
        {
            wallList[wallCount++] = (Wall){ mx, my };
        }
    }

    while (wallCount > 0) 
    {
        int index = rand() % wallCount;
        Wall w = wallList[index];
        wallList[index] = wallList[--wallCount];

        int px = w.x, py = w.y;
        int dir = -1;
        for (int i = 0; i < 4; i++) 
        {
            if (maze[py - dy[i]][px - dx[i]] == ' ' && px + dx[i] > 0 && px + dx[i] < WIDTH - 1 && py + dy[i] > 0 && py + dy[i] < HEIGHT - 1) 
            {
                dir = i;
                break;
            }
        }

        if (dir == -1) continue;

        int nx = px + dx[dir];
        int ny = py + dy[dir];

        if (maze[ny][nx] == '#') 
        {
            maze[py][px] = ' ';
            maze[ny][nx] = ' ';

            for (int i = 0; i < 4; i++) 
            {
                int ex = nx + dx[i] * 2;
                int ey = ny + dy[i] * 2;
                int mx = nx + dx[i];
                int my = ny + dy[i];
                if (ex > 0 && ex < WIDTH - 1 && ey > 0 && ey < HEIGHT - 1 && maze[ey][ex] == '#') 
                {
                    wallList[wallCount++] = (Wall){ mx, my };
                }
            }
        }
    }
}