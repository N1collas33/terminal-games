#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32                               
    #include <windows.h>
    #define sleep(s) Sleep((s) * 1000)
#else
    #include <unistd.h>
#endif

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};


int play, r, c;
const char PLAYER = 'X';
const char AI = 'O';

void game(){
    printf("\n");
    for(int i = 0; i < 3; i++){
        printf("     ");
        for(int j = 0; j < 3; j++){
            printf(" %c ", board[i][j]);
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
        if (i < 2){
            printf("     ------------\n");
        }
    }
}

int checkVitory(char symbol){
    for(int i = 0; i < 3; i++){
        //Check lines
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol ) return 1;
        //Check columns
        if (board[0][i] == symbol && board[1][i] == symbol && board [2][i] == symbol) return 1;

    }
    //Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return 1;

    return 0;

}

int bestPlay(){
    //Try to win the game
    for( int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (board[i][j] == PLAYER || board[i][j] == AI) continue;
            char temp = board[i][j];
            board[i][j] = AI;
            if (checkVitory(AI) == 1) return 1;
            board[i][j] = temp;
        }
    }
    //Block the player winning move
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == PLAYER || board[i][j] == AI) continue;
            char temp = board[i][j];
            board[i][j] = PLAYER;
            if (checkVitory(PLAYER) == 1){
                board[i][j] = AI;
                return 0;
            }
            board[i][j] = temp;
        }
    }
    //If the center is open, play there
    if (board[1][1] == '5'){
        board[1][1] = AI;
        return 0;
    }
    //If the AI can't win, block a player winning move, and the center is closed, play a random move
    do{
        play = rand() % 9 + 1;
        r = (play - 1) / 3;
        c = (play - 1) % 3;
    }while(board[r][c] == PLAYER || board[r][c] == AI);

    board[r][c] = AI;
    return 0;
}

int main(){
    srand(time(NULL));
    int match = 0;
    while (match < 9){

        printf("\n     Player turn\n");
        game();
        printf("\n    Input your play: ");
        scanf("%d", &play);
        r = (play - 1) / 3;
        c = (play - 1) % 3;
        while (board[r][c] == PLAYER || board[r][c] == AI || play >= 10 || play <= 0){
            printf("\n    Invalid position!\n");
            printf("    Input your play: ");
            scanf("%d", &play);
            r = (play - 1) / 3;
            c = (play - 1) % 3;
        }
        board[r][c] = PLAYER;
        if (checkVitory(PLAYER) == 1){
            printf("\n   ----You win !----");
            return 0;
        }
        
        match++;
        if (match == 9) break;
        
        printf("===================================\n");
        printf("\n      AI Turn\n");
        game();
        printf("\n     AI thinking...\n");
        printf("\n===================================\n");
        sleep(2);
        if (bestPlay() == 1){
            if (checkVitory(AI) == 1){
                game();
                printf("\n   ----AI Wins !----");
                return 0; 
            }
        }
        match++;
    }
    game();
    printf("\n========================\n");
    printf("    Tie!\n");
    printf("=========================\n");
    return 0;
}