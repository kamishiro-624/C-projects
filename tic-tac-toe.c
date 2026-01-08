#include <stdio.h>
#include <ctype.h>
#include <string.h>

// 0 = X, 1 = O, 2 = NULL
char boardVars[9][2] = {"", "", "", "", "", "", "", "", "", };

// 0 = O; 1 = X
int currentTurn;
int lastMove;
int firstMoveMade;
int movesMade;


void printBoard(void) {
    printf(" %s | %s | %s \n", boardVars[0], boardVars[1], boardVars[2]);
    printf("________\n");
    printf(" %s | %s | %s \n", boardVars[3], boardVars[4], boardVars[5]);
    printf("________\n");
    printf(" %s | %s | %s \n", boardVars[6], boardVars[7], boardVars[8]);
}

int winDetection(void) {
    // Columns
    if (strcmp(boardVars[0], "") != 0 && strcmp(boardVars[0], boardVars[3]) == 0 && strcmp(boardVars[3], boardVars[6]) == 0) {
        return 1; // Win
    } else if (strcmp(boardVars[1], "") != 0 && strcmp(boardVars[1], boardVars[4]) == 0 && strcmp(boardVars[4], boardVars[7]) == 0) {
        return 1;
    } else if (strcmp(boardVars[2], "") != 0 && strcmp(boardVars[2], boardVars[5]) == 0 && strcmp(boardVars[5], boardVars[8]) == 0) {
        return 1;
    }
    // Rows
    if (strcmp(boardVars[0], "") != 0 && strcmp(boardVars[0], boardVars[1]) == 0 && strcmp(boardVars[1], boardVars[2]) == 0) {
        return 1; // Win
    } else if (strcmp(boardVars[3], "") != 0 && strcmp(boardVars[3], boardVars[4]) == 0 && strcmp(boardVars[4], boardVars[5]) == 0) {
        return 1;
    } else if (strcmp(boardVars[6], "") != 0 && strcmp(boardVars[6], boardVars[7]) == 0 && strcmp(boardVars[7], boardVars[8]) == 0) {
        return 1;
    }
    // Diagonals
    if (strcmp(boardVars[0], "") != 0 && strcmp(boardVars[0], boardVars[4]) == 0 && strcmp(boardVars[4], boardVars[8]) == 0) {
        return 1; // Win
    } else if (strcmp(boardVars[2], "") != 0 && strcmp(boardVars[2], boardVars[4]) == 0 && strcmp(boardVars[4], boardVars[6]) == 0) {
        return 1;
    }
    // Draw Detection
    if (movesMade >= 9) {
        return 2;
    }
    return 0; // Not win :(
}



int main(void)
{
    
    firstMoveMade = 0;
    currentTurn = 1;
    StartTurn:
    
    printBoard();
     
    if (firstMoveMade == 1) {
        if (winDetection() == 1) {
            if (currentTurn == 1) {
                printf("[O] has won the game.");
                return 0;
            } else {
                printf("[X] has won the game.");
                return 0;
            }
        } else if (winDetection() == 2) {
            printf("The game has ended in a draw.");
            return 0;
        }
    }
    
    if (currentTurn == 1) {
        printf("\n[X] Choose Location: ");
    } else {
        printf("\n[O] Choose Location: ");
    }
    scanf("%d", &lastMove);
    lastMove--;
    if (lastMove > 8 || lastMove < 0) {
        printf("Invalid Input.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            // Discard character
        }
        goto StartTurn;
    }
    
    if (strcmp(boardVars[lastMove],"") != 0) {
        printf("This slot has already been taken.\n");
        goto StartTurn;
    }
    
    if (currentTurn == 1) {
        movesMade++;
        firstMoveMade = 1;
        strcpy(boardVars[lastMove], "X");
        currentTurn = 0;
        goto StartTurn;
    }
    
    if (currentTurn == 0) {
        movesMade++;
        firstMoveMade = 1;
        strcpy(boardVars[lastMove], "O");
        currentTurn = 1;
        goto StartTurn;
    }
}
