#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

int WIDTH, HEIGHT;
char **maze;
int playerX, playerY;
int goalX, goalY;
int moveCount = 0;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

char getch() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void shuffle(int *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void dfs(int x, int y) {
    int dirs[4] = { 0, 1, 2, 3 };
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]] * 2;
        int ny = y + dy[dirs[i]] * 2;

        if (nx >= 1 && nx < WIDTH - 1 && ny >= 1 && ny < HEIGHT - 1 && maze[ny][nx] == '#') {
            maze[y + dy[dirs[i]]][x + dx[dirs[i]]] = ' ';
            maze[ny][nx] = ' ';
            dfs(nx, ny);
        }
    }
}

int countAdjacentWalls(int x, int y) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && maze[ny][nx] == '#') {
            count++;
        }
    }
    return count;
}

void addLoops(int loopCount) {
    for (int i = 0; i < loopCount; i++) {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        if (maze[y][x] == '#' && 
            maze[y-1][x] == ' ' && maze[y+1][x] == ' ') {
            maze[y][x] = ' ';
        }
        if (maze[y][x] == '#' && 
            maze[y][x-1] == ' ' && maze[y][x+1] == ' ') {
            maze[y][x] = ' ';
        }
    }
}

void allocateMaze() {
    maze = (char **)malloc(sizeof(char *) * HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (char *)malloc(sizeof(char) * WIDTH);
    }
}

void freeMaze() {
    for (int i = 0; i < HEIGHT; i++) {
        free(maze[i]);
    }
    free(maze);
}

void generateMaze() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
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
    addLoops(30);
}

void printMaze() {
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY) {
                putchar('P');
            } else if (x == goalX && y == goalY) {
                putchar('G');
            } else {
                putchar(maze[y][x]);
            }
        }
        putchar('\n');
    }

    printf("\n移動回数: %d\n", moveCount);
    printf("現在位置: (%d, %d)\n", playerX, playerY);
    printf("WASDで移動。ゴール = G\n");
}

void movePlayer(char dir) {
    int newX = playerX;
    int newY = playerY;

    switch (dir) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return;
    }

    if (maze[newY][newX] == ' ') {
        playerX = newX;
        playerY = newY;
        moveCount++;
    }
}

int main() {
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

    while (1) {
        printMaze();

        if (playerX == goalX && playerY == goalY) {
            printf("ゴール！クリア！\n");
            printf("総移動回数: %d\n", moveCount);
            break;
        }

        char input = getch();
        movePlayer(input);
    }

    freeMaze();
    return 0;
}