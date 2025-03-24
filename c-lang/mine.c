#include <stdio.h>

void displayBoard(char board_num[9][9]);

int main(void) {
    // クリア条件
    const int CLEARCOUNT = 76;
    // 入力値を保持する
    int input_num[2];
    // 範囲表示判定
    int square_flg = 0;
    // 表示した数字の数
    int open_count = 0;
    // ヒントとなる数字、9は爆弾
    char hint_num[9][9] = {{'0','0','2','9','2','0','0','0','0'},
                            {'0','0','2','9','2','0','0','0','0'},
                            {'0','0','1','1','1','0','0','0','0'},
                            {'0','0','0','0','0','0','0','1','1'},
                            {'1','1','0','0','0','0','0','1','9'},
                            {'9','1','0','0','0','0','0','1','1'},
                            {'1','1','0','1','1','1','0','0','0'},
                            {'0','0','0','1','9','1','0','0','0'},
                            {'0','0','0','1','1','1','0','0','0'}};
    char board_num[9][9];

    printf("ゲームを開始します\n");
    
    // 行番号を表示する
    for(int i = 0; i < 9; i++) {
        printf("\t%d", i + 1);
    }

    printf("\n");
    
    for(int i = 0; i < 9; i++) {
        //列番号を表示する
        printf("%d", i + 1);

        //?マークをboard_numに格納する
        for(int j = 0; j < 9; j++) {
            board_num[i][j] = '?';
            printf("\t%c", board_num[i][j]);
        }

        printf("\n\n\n");
    }

    while(1) {
        printf("行番号を入力してください\n");
        scanf("%d", &input_num[0]);
        printf("列番号を入力してください\n");
        scanf("%d", &input_num[1]);

        while (1) {
            // 入力された値が不正なら再度入力を促す
            if(board_num[input_num[0] - 1][input_num[1] - 1] != '?' || input_num[0] < 1 || input_num[0] > 9 || input_num[1] < 1 || input_num[1] > 9) {
                printf("再度行番号を入力してください\n");
                scanf("%d", &input_num[0]);
                printf("再度列番号を入力してください\n");
                scanf("%d", &input_num[1]);
            } else {
                break;
            }
        }

        for(int i = 0; i < 9; i++) {
            printf("\t%d", i + 1);
        }

        printf("\n");

        // 9ならゲームオーバー
        if(hint_num[input_num[0] - 1][input_num[1] - 1] == '9') {
            for(int i = 0; i < 9; i++) {
                printf("%d", i + 1);
                
                // 全てを表示する
                for(int j = 0; j < 9; j++) {
                    if(hint_num[i][j] != '9') {
                        printf("\t%c", hint_num[i][j]);
                    } else {
                        printf("\t爆");
                    }
                    
                }
                printf("\n\n\n");
            }

            printf("GAME OVER\n");
            break;
        
        // 行番号4以下かつ列番号6以上かつsquare_flgが0ならその範囲を表示
        } else if(square_flg == 0 && input_num[0] <= 4 && input_num[1] >= 6) {
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 9; j++) {
                    if(j >= 5) {
                        board_num[i][j] = hint_num[i][j];
                    }
                }
            }

            // square_flgを1にすることで2度同じ処理を行わないようにする
            square_flg = 1;
            open_count = open_count + 16;

            displayBoard(board_num);
            
        // それ以外の場合表示
        } else {
            // 初期から何も入っていないboard_numにhint_numの値を入れる
            board_num[input_num[0] - 1][input_num[1] - 1] = hint_num[input_num[0] - 1][input_num[1] - 1];
            // 何マス表示されたかカウントする
            open_count++;
            // board_numを表示
            displayBoard(board_num);
            // 爆弾以外のマスが全て表示されたときopen_countとCLEARCOUNTの値は同じになりゲームクリア
            if(open_count == CLEARCOUNT) {
                printf("GAME CLEAR!\n");
                break;
            }
        }
    }

    return 0;
}

void displayBoard(char board_num[9][9]) {
    for(int i = 0; i < 9; i++) {
        printf("%d", i + 1);
        for(int j = 0; j < 9; j++) {
            
            printf("\t%c", board_num[i][j]);
        }
        printf("\n\n\n");
    }
}
