#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ASCII_RANGE 95 // ASCII value for tilde '~'
#define ASCII_BASE 32 // ASCII value for the space character ' '

int option;
char key[7];
int validKey;
char decodeText[101];
char result[101];

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
            // Clear Input Buffer
    }
}

int main()
{
    do {
        printf("[] 1. Decode\n[] 2. Encode\n\n");
        printf("Choose Option: ");
        
        if (scanf("%d", &option) != 1) {
            printf("[] Invalid option selected.\n");
            clearBuffer();
        } else if (option != 1 && option != 2) {
            printf("\n[] Invalid option selected.\n\n");
            clearBuffer();
        } else {
            clearBuffer();
        }
    } while (option != 1 && option != 2);
    
    printf("[] Successfully chose option %d.", option);
    
    do {
        validKey = 1;
        printf("\n[] Please input a 6 digit key: ");
        scanf("%6s", key);
        clearBuffer();
        for (int i = 0; i < 6; i++) {
            if (!isdigit(key[i])) {
                validKey = 0;
                printf("\n[] Invalid digit found. ");
                break;
            }
        }
        if (strlen(key) != 6) {
            validKey = 0;
            printf(" Incorrect length. ");
        }
        
    } while (validKey == 0);
    
    if (option == 1) {
        printf("\nMaximum length of 100 characters.");
        printf("\nEnter string to decode: ");
        
        fgets(decodeText, 101, stdin);
        size_t len = strlen(decodeText);
        if (len > 0 && decodeText[len-1] == '\n') {
            decodeText[len-1] = '\0';
            len--;
        }
        
        printf("\nYour resulting string is: ");
        for (int i = 0; i < strlen(decodeText); i++) {
            int char_ascii = (int)decodeText[i];
            int offset = key[i % 6] - '0';
            
            int normalized_index = char_ascii - ASCII_BASE;
            
            // 2. Apply Shift: Calculate the new index
            // We add ASCII_RANGE before the modulo to ensure the result of the 
            // subtraction (decoding) is never negative before applying modulo.
            int new_index = (normalized_index + (offset * -1) + ASCII_RANGE) % ASCII_RANGE;
            
            // 3. Denormalize: Convert the new index back to its ASCII value
            int newChar = new_index + ASCII_BASE;
            printf("%c", newChar);
        }
    } else if (option == 2) {
        printf("\nMaximum length of 100 characters.");
        printf("\nEnter string to encode: ");
        
        fgets(decodeText, 101, stdin);
        size_t len = strlen(decodeText);
        if (len > 0 && decodeText[len-1] == '\n') {
            decodeText[len-1] = '\0';
            len--;
        }
        
        printf("\nYour resulting string is: ");
        for (int i = 0; i < len; i++) { // Use 'len' instead of re-calculating strlen(decodeText)
            int char_ascii = (int)decodeText[i];
            int offset = key[i % 6] - '0';
    
            int normalized_index = char_ascii - ASCII_BASE;
            
            // 2. Apply Shift (Encoding: positive direction)
            // Adding ASCII_RANGE is not strictly necessary for encoding since it's an addition, 
            // but we can leave it out for simplicity here.
            int new_index = (normalized_index + offset) % ASCII_RANGE; 
            
            // 3. Denormalize
            int newChar = new_index + ASCII_BASE;
            
            printf("%c", newChar);
        }
    }
    return 0;
}
