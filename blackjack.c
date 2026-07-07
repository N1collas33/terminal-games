#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cross-platform sleep/clear screen
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
// Shortcut to redraw the board without repeating all the args every time
#define REFRESH printGame(dealerCount,dealerHand,dealerTotal,playerCount,playerHand,playerTotal,dealerTurn);

char *cards[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

// Face cards = 10, Ace = 11 (adjusted later in handTotal)
int cardValue(char *value){
    if(strcmp(value, "J") == 0 || strcmp(value, "Q") == 0 || strcmp(value, "K") == 0) return 10;
    if(strcmp(value, "A") == 0) return 11;
    return atoi(value);
}

// Sums the hand, downgrading Aces from 11 to 1 if it would otherwise bust
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

// Infinite-deck draw (no removal/shuffling, repeats are possible)
char *randomCard(){
    return cards[rand() % 13];
}

// Draws one row (0-4) of an ASCII card; call 5 times to draw a full card
void printCard(char *value, int line) {
    switch(line){
        case 0: printf(" _____ "); break;
        case 1: printf("|     |"); break;
        case 2:
            // "10" needs one less leading space to stay aligned
            if (strcmp(value, "10") != 0){
                printf("|  %s  |", value); break;
            }else{
                printf("| %s  |", value); break;
            }
        case 3: printf("|     |"); break;
        case 4: printf("|_____|"); break;
    }
}

// Redraws the whole board. dealerTurn toggles between hole-card hidden
// (player's turn) and dealer's full hand revealed.
void printGame(int dealerCount, char *dealerHand[], int dealerTotal, int playerCount, char *playerHand[], int playerTotal, int dealerTurn){
    CLEAR;
    
    printf("          DEALER HAND\n\n");
 
    if(dealerTurn){
        for(int line = 0; line < 5; line++){
            printf("        ");
            for(int i = 0; i < dealerCount; i++){
                printCard(dealerHand[i], line);
                printf(" ");
            }
            printf("                    ");
            switch(line) {
                case 0: printf(" _____ "); break;
                case 1: printf("|/////|"); break;
                case 2: printf("|/////|"); break;
                case 3: printf("|/////|"); break;
                case 4: printf("|_____|"); break;
            }
            printf("\n");
        }
        printf("\n               %d\n\n", dealerTotal);
        if(dealerTotal > 21) printf("           BUST!\n\n");
        // Checks dealer's original first 2 cards, ignoring later draws
        if(cardValue(dealerHand[0]) + cardValue(dealerHand[1]) == 21) printf("           BLACKJACK!\n\n");
    }
    else{
        // Only the dealer's first card is shown; the rest stays face-down
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
            printf("                    ");
            switch(line) {
                case 0: printf(" _____ "); break;
                case 1: printf("|/////|"); break;
                case 2: printf("|/////|"); break;
                case 3: printf("|/////|"); break;
                case 4: printf("|_____|"); break;
            }
            printf("\n");
        }
        printf("\n               %d\n\n", cardValue(dealerHand[0]));
    }
    
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
    playerTotal = handTotal(playerHand, playerCount); // recompute to be safe
    printf("\n               %d\n\n", playerTotal);
}

int main(){
    srand(time(NULL));
    printf("\n===========TERMINAL BLACKJACK===========\n");
    printf("           PRESS ENTER TO PLAY\n");
    getchar();
    char playAgain;
    

    do {
        CLEAR;
        int playerCount = 2, dealerCount = 2, dealerTurn = 0;

    	printf("          DEALER HAND\n\n");
    	int dealerTotal = 0;
    	char *dealerHand[maxHand];
    
    	// Deal dealer's first 2 cards
    	for (int i = 0; i < 2; i++) {
    		dealerHand[i] = randomCard();
    	}
    	dealerTotal = handTotal(dealerHand, dealerCount);
    
    	// Show only the dealer's up-card; second card stays hidden
    	for (int line = 0; line < 5; line++) {
    		printf("        ");
    		printCard(dealerHand[0], line);
    		printf(" ");
    		switch (line) {
    			case 0: printf(" _____ "); break;
    			case 1: printf("|/////|"); break;
    			case 2: printf("|/////|"); break;
    			case 3: printf("|/////|"); break;
    			case 4: printf("|_____|"); break;
    		}
    		printf("                    ");
    		switch (line) {
    			case 0: printf(" _____ "); break;
    			case 1: printf("|/////|"); break;
    			case 2: printf("|/////|"); break;
    			case 3: printf("|/////|"); break;
    			case 4: printf("|_____|"); break;
    		}
    		printf("\n");
    	}
    	printf("\n               %d \n\n", cardValue(dealerHand[0]));
    
    	printf("       Blackjack pays 3 to 2\n");
    	printf("   Dealer must draw to 16 and stand on 17\n\n");
    
    	printf("          PLAYER HAND\n\n");
    
    	int playerTotal = 0;
    	char *playerHand[maxHand];
    
    	// Deal player's first 2 cards (sum here is just a placeholder,
    	// handTotal() below recalculates it properly with Ace logic)
    	for (int i = 0; i < 2; i++) {
    		playerHand[i] = randomCard();
    		playerTotal += cardValue(playerHand[i]);
    	}
    
    	for (int line = 0; line < 5; line++) {
    		printf("        ");
    		for (int i = 0; i < playerCount; i++) {
    			printCard(playerHand[i], line);
    			printf(" ");
    		}
    		printf("\n");
    	}
    	playerTotal = handTotal(playerHand, playerCount);
    	printf("\n               %d\n\n", playerTotal);
    
    	if (playerTotal == 21)
    		printf("           BLACKJACK!");
    
    	// Player's turn: hit or stand until 21 or bust
    	char op;
    	while (playerTotal < 21) {
    		printf("        [H] HIT\t [S] STAND\n");
    		scanf(" %c", &op);
    	    getchar(); // clears leftover newline from scanf
    		if (op == 's' || op == 'S')
    			break;
    		else {
    			playerHand[playerCount] = randomCard();
    			playerCount++;
    			playerTotal = handTotal(playerHand, playerCount);
    			REFRESH;
    			if (playerTotal > 21) {
    				printf("           YOU BUSTED!\n");
    				break;
    			}
    		}
    	}
    
    	// Dealer's turn: reveal hole card
    	dealerTurn = 1;
    	sleep(2);
    	REFRESH;
    
    	// Dealer hits until 17+ (standard house rule)
    	while (dealerTotal < 17) {
    		dealerHand[dealerCount] = randomCard();
    		dealerCount++;
    		dealerTotal = handTotal(dealerHand, dealerCount);
    		sleep(2);
    		REFRESH;
    	}
    
    	sleep(2);
    	CLEAR;
    
    	// Decide the round's winner
    	printf("\n\n\n\n\n\n\n\n");
    	if (playerTotal > 21) {
    		printf("           YOU LOSE!");
    	} else if (dealerTotal > 21) {
    		printf("           YOU WIN!");
    	} else if (playerTotal == dealerTotal) {
    		printf("           PUSH!");
    	} else if (playerTotal > dealerTotal) {
    		printf("           YOU WIN!");
    	} else {
    		printf("           YOU LOSE!");
    	}
    	printf("\n\n     PRESS ENTER TO PLAY AGAIN\n");
    	printf("     PRESS ANY OTHER KEY TO QUIT\n");
    	playAgain = getchar();
    	printf("\n\n\n\n\n\n\n\n");
    } while (playAgain == '\n'); // Enter = play again, anything else = quit
    
    return 0;
}
