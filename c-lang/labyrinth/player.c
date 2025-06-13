#include "player.h"
#include "maze.h"

int playerX, playerY;
int moveCount = 0;

// プレイヤーをWASDキーに応じて移動させる関数（移動先が通路かどうか判定）
void movePlayer(char dir) 
{
    int newX = playerX;
    int newY = playerY;

    switch (dir) 
    {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return;
    }

    if (maze[newY][newX] == ' ') 
    {
        playerX = newX;
        playerY = newY;
        moveCount++;
    }
}