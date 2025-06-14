#ifndef MAZE_H
#define MAZE_H

extern int WIDTH, HEIGHT;
extern char **maze;
extern int goalX, goalY;
extern int dx[4], dy[4];

void allocateMaze();
void freeMaze();
void printMaze();
void generateMaze();

#endif