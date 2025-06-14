#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "util.h"
#include "wilson.h"

// dx, dy は {0, 0, -1, 1} / {-1, 1, 0, 0} で外部定義されている前提
extern int dx[4], dy[4];
extern int WIDTH, HEIGHT;
extern char **maze;


void wilson(void) {
    // 乱数初期化
    srand(time(NULL));

    // 動的確保
    int **visited = (int **)malloc(sizeof(int *) * HEIGHT);
    int **mark    = (int **)malloc(sizeof(int *) * HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        visited[y] = (int *)calloc(WIDTH, sizeof(int));
        mark[y]    = (int *)calloc(WIDTH, sizeof(int));
    }

    // スタート地点 (1,1)
    visited[1][1] = 1;

    int total_cells = ((WIDTH - 1) / 2) * ((HEIGHT - 1) / 2);
    int visited_cells = 1;

    while (visited_cells < total_cells) {
        int sx, sy;
        do {
            sx = (rand() % ((WIDTH - 1) / 2)) * 2 + 1;
            sy = (rand() % ((HEIGHT - 1) / 2)) * 2 + 1;
        } while (visited[sy][sx]);

        int len = 0;
        Point path[WIDTH * HEIGHT]; // 最大長さで確保（VLAでない）

        path[len++] = (Point){sx, sy};

        for (;;) {
            int dirs[4] = {0, 1, 2, 3};
            shuffle(dirs, 4);
            int moved = 0;

            for (int i = 0; i < 4; i++) {
                int nx = path[len - 1].x + dx[dirs[i]] * 2;
                int ny = path[len - 1].y + dy[dirs[i]] * 2;

                if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1) {
                    path[len++] = (Point){nx, ny};

                    // ループ検出して削除
                    for (int j = 0; j < len - 1; j++) {
                        if (path[j].x == nx && path[j].y == ny) {
                            len = j + 1;
                            break;
                        }
                    }

                    moved = 1;
                    break;
                }
            }

            if (!moved) break; // 動けない → 強制終了

            if (visited[path[len - 1].y][path[len - 1].x])
                break; // 終了条件：接続済みマスに到達
        }

        // 経路を迷路に反映
        for (int i = 0; i < len - 1; i++) {
            int x1 = path[i].x;
            int y1 = path[i].y;
            int x2 = path[i + 1].x;
            int y2 = path[i + 1].y;
            int wx = (x1 + x2) / 2;
            int wy = (y1 + y2) / 2;

            maze[y1][x1] = ' ';
            maze[wy][wx] = ' ';
            maze[y2][x2] = ' ';

            if (!visited[y2][x2]) {
                visited[y2][x2] = 1;
                visited_cells++;
            }
        }
    }

    // 動的確保の解放
    for (int y = 0; y < HEIGHT; y++) {
        free(visited[y]);
        free(mark[y]);
    }
    free(visited);
    free(mark);
}