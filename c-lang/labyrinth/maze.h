#ifndef MAZE_H
#define MAZE_H

extern int WIDTH, HEIGHT;
extern char **maze;
extern int goalX, goalY;

void allocateMaze();
void freeMaze();
void generateMaze();
void printMaze();
int countAdjacentWalls(int x, int y);
void addLoops(int loopCount);

#endif