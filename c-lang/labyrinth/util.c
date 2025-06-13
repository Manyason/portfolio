#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// ユーザーの1文字入力をエコーなし・Enter不要で取得する関数（UNIX端末用）
char getch() 
{
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (ch);
}

// 配列の要素をランダムに並び替える（Fisher-Yatesシャッフル）
void shuffle(int *array, int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        int j = i + rand() % (n - i);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}