#ifndef MAZE_H
#define MAZE_H

extern int WIDTH, HEIGHT;
extern char **maze;
extern int goalX, goalY;

void allocateMaze();
void freeMaze();
void printMaze();
void generateMaze();

#endif