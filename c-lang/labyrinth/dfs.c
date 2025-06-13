#include <stdlib.h>
#include "dfs.h"
#include "maze.h"
#include "util.h"

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