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

char *cards[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
int total = 13;
int cardsPlayer = 2, cardsDealer = 2;

char *randomCard(){
    return cards[rand() % total];
}

int cardValue(char *value){
    if(strcmp(value, "J") == 0 || strcmp(value, "Q") == 0 || strcmp(value, "K") == 0) return 10;
    if(strcmp(value, "A") == 0) return 11;
    return atoi(value);
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
        switch(line) {
        case 0: printf(" _____ "); break;
        case 1: printf("|/////|"); break;
        case 2: printf("|/////|"); break;
        case 3: printf("|/////|"); break;
        case 4: printf("|_____|"); break;
        }
        printf("\n");
    }
    printf("\n               %d + %s\n\n", dealerTotal, dealerHand[1]);
    
    printf("       Blackjack pays 3 to 2\n");
    printf("   Dealer must draw to 16 and stand on 17\n\n");
    
    //PLAYER FIRST HAND
    
    printf("          PLAYER HAND\n\n");
    
    
    int playerTotal = 0;
    char *playerHand[maxHand];
    
    //PLAYER FIRST CARDS AND HAND VALUE 
    for(int i = 0; i < 2; i++){
        playerHand[i] = randomCard();
        playerTotal += cardValue(playerHand[i]);
    }
    
    for (int line = 0; line < 5; line++){
        printf("        ");
        for(int i = 0; i < cardsPlayer; i++){
            printCard(playerHand[i], line);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n               %d\n\n", playerTotal);
    
    

    return 0;
}