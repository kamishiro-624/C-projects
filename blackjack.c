#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// I tried ANSI escape codes for more colors with the output but it failed
// like really badly so I didn't do it :d

const char cardValues[13][3] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

void clrConsole(void) {
    printf("\x1b[2J\x1b[H");
}

int drawCard() {
    int cardValue = (rand() % 13) + 1;
    return cardValue;
}

int winCheck(int plrV, int delV) { // Use playerValue and dealerValue as args
    if (plrV == 21 || delV > 21) {
        return 0; // Player Won
    } else if (delV == 21 || plrV > 21) {
        return 1; // Dealer Won
    } else {
        return -1; // No win
    }
}

void clrStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main()
{
    int playerValue = 0;
    int dealerValue = 0;
    int dealerShownValue = 0;
    
    int lastCardDrawn = 0;
    
    srand(time(NULL));
    
    printf("= Welcome to Blackjack =\n");
    
    lastCardDrawn = drawCard();
    printf("\nYour first card is: %s", cardValues[lastCardDrawn - 1]);
    while (lastCardDrawn > 10) {
        lastCardDrawn--;
    }
    
    if (lastCardDrawn == 1) {
        if ((playerValue + 11) < 22) {
            playerValue += 11;
        } else {
            playerValue += 1;
        }
    } else {
        playerValue += lastCardDrawn;
    }
    
    lastCardDrawn = drawCard();
    printf("\nYour second card is: %s", cardValues[lastCardDrawn - 1]);
    while (lastCardDrawn > 10) {
        lastCardDrawn--;
    }
    
    if (lastCardDrawn == 1) {
        if ((playerValue + 11) < 22) {
            playerValue += 11;
        } else {
            playerValue += 1;
        }
    } else {
        playerValue += lastCardDrawn;
    }
    
    printf("\n[] The total value of your hand is %d", playerValue);
    
    // DEALER CARDS
    
    lastCardDrawn = drawCard();
    printf("\n\nThe dealer's first card is: %s", cardValues[lastCardDrawn - 1]);
    while (lastCardDrawn > 10) {
        lastCardDrawn--;
    }
    
    if (lastCardDrawn == 1) {
        if ((dealerValue + 11) < 22) {
            dealerValue += 11;
            dealerShownValue += 11;
        } else {
            dealerValue += 1;
            dealerShownValue += 1;
        }
    } else {
        dealerValue += lastCardDrawn;
        dealerShownValue += lastCardDrawn;
    }
    
    lastCardDrawn = drawCard();
    printf("\nThe dealer's second card is hidden.");
    while (lastCardDrawn > 10) {
        lastCardDrawn--;
    }
    if (lastCardDrawn == 1) {
        if ((dealerValue + 11) < 22) {
            dealerValue += 11;
        } else {
            dealerValue += 1;
        }
    } else {
        dealerValue += lastCardDrawn;
    }
    
    printf("\n[] The shown value of the dealer's hand is %d", dealerShownValue);
    
    int drawingDone = 0;
    
    // PLAYER CHOICE
    while (drawingDone == 0) {
        int playerChoice;
        int gaveValid = 0;
        int playerStand = 0;
        
        printf("\n\nChoose an option below:\n1. Hit\n2. Stand");
        
        while (gaveValid == 0) {
        printf("\n> ");
            if (scanf("%d", &playerChoice) != 1) {
                printf("Please enter a valid choice.");
                clrStdin();
                gaveValid = 0;
            } else {
                if (playerChoice < 1 || playerChoice > 2) {
                    printf("Please enter a valid choice.");
                    gaveValid = 0;
                } else {
                    gaveValid = 1;
                }
                clrStdin();
            }
        }  
        
        clrConsole();
        
        if (playerChoice == 1) {
            printf("You have chosen to hit.");
            lastCardDrawn = drawCard();
            printf("\nYour drawn card is: %s", cardValues[lastCardDrawn - 1]);
            while (lastCardDrawn > 10) {
                lastCardDrawn--;
            }
            if (lastCardDrawn == 1) {
                if ((playerValue + 11) < 22) {
                    playerValue += 11;
                } else {
                    playerValue += 1;
                }
            } else {
                playerValue += lastCardDrawn;
            }
            printf("\n[] The total value of your hand is now %d", playerValue);
        } else if (playerChoice == 2) {
            printf("You have chosen to stand.");
            printf("\n[] The total value of your hand is %d", playerValue);
            playerStand = 1;
        }
        
        // DEALER CHOICE
        
        int dealerStand = 0;
        
        if (dealerValue < 17) {
            printf("\n\nThe dealer has decided to hit.");
            
            lastCardDrawn = drawCard();
            printf("\n\nThe dealer's drawn card is: %s", cardValues[lastCardDrawn - 1]);
            while (lastCardDrawn > 10) {
                lastCardDrawn--;
            }
            if (lastCardDrawn == 1) {
                if ((dealerValue + 11) < 22) {
                    dealerValue += 11;
                    dealerShownValue += 11;
                } else {
                    dealerValue += 1;
                    dealerShownValue += 1;
                }
            } else {
                dealerValue += lastCardDrawn;
                dealerShownValue += lastCardDrawn;
            }
            printf("\n[] The shown value of the dealer's hand is now %d", dealerShownValue);
        } else {
            printf("\n\nThe dealer has decided to stand.");
            printf("\n[] The shown value of the dealer's hand is %d", dealerShownValue);
            dealerStand = 1;
        }
        
        // WIN-LOSE DETECTION
        
        if (winCheck(playerValue, dealerValue) == 0) {
                printf("\nCongratulations, you have won the game.");
                printf("\nDealer: %d\nPlayer: %d", dealerValue, playerValue);
                drawingDone = 1;
            } else if (winCheck(playerValue, dealerValue) == 1) {
                printf("\nSorry, but you have lost the game.");
                printf("\nDealer: %d\nPlayer: %d", dealerValue, playerValue);
                drawingDone = 1;
            } else if (winCheck(playerValue, dealerValue) == -1) {
                drawingDone = 0;
            }
        
        if (playerStand == 1 && dealerStand == 1) {
            if (playerValue > dealerValue) {
                printf("\n\nCongratulations, you have won the game.");
                printf("\nDealer: %d\nPlayer: %d", dealerValue, playerValue);
                drawingDone = 1;
            } else if (dealerValue > playerValue) {
                printf("\nSorry, but you have lost the game.");
                printf("\nDealer: %d\nPlayer: %d", dealerValue, playerValue);
                drawingDone = 1;
            } else if (playerValue == dealerValue) {
                printf("\nThe game has ended in a tie.");
                printf("\nDealer: %d\nPlayer: %d", dealerValue, playerValue);
                drawingDone = 1;
            }
        }
    }
    return 0;
}
