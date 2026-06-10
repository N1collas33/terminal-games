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

#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR printf("\033[2J\033[H")
#endif

#define maxHand 10
#define REFRESH printGame(dealerHand,dealerTotal,playerCount,playerHand,playerTotal);

char *cards[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int playerCount = 2, dealerCount = 2;



int cardValue(char *value){
    if(strcmp(value, "J") == 0 || strcmp(value, "Q") == 0 || strcmp(value, "K") == 0) return 10;
    if(strcmp(value, "A") == 0) return 11;
    return atoi(value);
}

int handTotal(char *hand[], int count){
    int total = 0;
    int aces = 0;
    
    for(int i = 0; i < count; i++){
        total += cardValue(hand[i]);
        if(strcmp(hand[i], "A") == 0) aces++;
    }
    
    while(total > 21 && aces > 0){
        total -= 10;
        aces--;
    }
    return total;
}


char *randomCard(){
    return cards[rand() % 13];
}




void printCard(char *value, int line) {

    switch(line){
        case 0: printf(" _____ "); break;
        case 1: printf("|     |"); break;
        case 2:
            if (value != "10"){
                printf("|  %s  |", value); break;
            }else{
                printf("| %s  |", value); break;
            }
        case 3: printf("|     |"); break;
        case 4: printf("|_____|"); break;
    }
}

void printGame(char *dealerHand[], int dealerTotal, int playerCount, char *playerHand[], int playerTotal){
    CLEAR;
    
    printf("          DEALER HAND\n\n");
 
    for (int line = 0; line < 5; line++){
        printf("        ");
        printCard(dealerHand[0], line);
        printf(" ");
        switch(line) {
        case 0: printf(" _____ "); break;
        case 1: printf("|/////|"); break;
        case 2: printf("|/////|"); break;
        case 3: printf("|/////|"); break;
        case 4: printf("|_____|"); break;
        }
        printf("\n");
    }
    printf("\n               %d + %s\n\n", dealerTotal);
    
    printf("       Blackjack pays 3 to 2\n");
    printf("   Dealer must draw to 16 and stand on 17\n\n");
    
    
    printf("          PLAYER HAND\n\n");
    for (int line = 0; line < 5; line++){
        printf("        ");
        for(int i = 0; i < playerCount; i++){
            printCard(playerHand[i], line);
            printf(" ");
        }
        printf("\n");
    }
    playerTotal = handTotal(playerHand, playerCount);
    printf("\n               %d\n\n", playerTotal);
    
}


int main(){
    srand(time(NULL));
    printf("\n===========TERMINAL BLACKJACK===========\n");
    printf("           PRESS ENTER TO PLAY\n");
    getchar();
    CLEAR;
    
    //DEALER FIRST HAND
    printf("          DEALER HAND\n\n");
    int dealerTotal = 0;
    char *dealerHand[maxHand];
    
    
    //GENERATE THE CARDS AND CALCULATES THE VALUE OF THE DEALERS HAND
    for(int i =0; i < 2; i++){
        dealerHand[i] = randomCard();
    }
    dealerTotal += cardValue(dealerHand[0]);
    
    for (int line = 0; line < 5; line++){
        printf("        ");
        printCard(dealerHand[0], line);
        printf(" ");
        switch(line){ 
            case 0: printf(" _____ "); break;
            case 1: printf("|/////|"); break;
            case 2: printf("|/////|"); break;
            case 3: printf("|/////|"); break;
            case 4: printf("|_____|"); break;
        }
        printf("                    ");
        switch(line){ 
            case 0: printf(" _____ "); break;
            case 1: printf("|/////|"); break;
            case 2: printf("|/////|"); break;
            case 3: printf("|/////|"); break;
            case 4: printf("|_____|"); break;
        }
        printf("\n");
    }
    printf("\n               %d + %s\n\n", dealerTotal);
    
    printf("       Blackjack pays 3 to 2\n");
    printf("   Dealer must draw to 16 and stand on 17\n\n");
    
    //PLAYER FIRST CARDS AND HAND VALUE 
    
    printf("          PLAYER HAND\n\n");
    
    
    int playerTotal = 0;
    char *playerHand[maxHand];
    
    for(int i = 0; i < 2; i++){
        playerHand[i] = randomCard();
        playerTotal += cardValue(playerHand[i]);
    }
    
    for (int line = 0; line < 5; line++){
        printf("        ");
        for(int i = 0; i < playerCount; i++){
            printCard(playerHand[i], line);
            printf(" ");
        }
        printf("\n");
    }
    playerTotal = handTotal(playerHand, playerCount);
    printf("\n               %d\n\n", playerTotal);

    if( playerTotal == 21) printf("           BLACKJACK!");
    
    
    char op;
    while(playerTotal < 21){
        printf("        [H] HIT\t [S] STAND\n");
        scanf(" %c", &op);
        if ( op == 's' || op == 'S') break;
        else{
            playerHand[playerCount] = randomCard();
            playerTotal += cardValue(playerHand[playerCount]);
            playerCount++;
            playerTotal = handTotal(playerHand, playerCount);
            REFRESH;
            if(playerTotal > 21){
                printf("           YOU BUSTED!\n");
                break;
            }
        }
    }

    return 0;
}