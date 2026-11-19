#include <stdio.h>
#include <stdlib.h> // strtol
#include <string.h>
#include <time.h>
#include <ctype.h>

#include <unistd.h> // sleep

void flushStdIn() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int randInt(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int main() {
    srand(time(NULL));

    char buffer[5]; // length of random string
    char charSpace[28] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '-', '_'};

    long length = 0;

    do {  

        printf("Enter the length of your desired string.");
        printf("\n> ");

        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (strchr(buffer, '\n') == NULL) {
                flushStdIn();
            } else {
                buffer[strcspn(buffer, "\n")] = '\0';
            }
        }

        char *endptr;
        length = strtol(buffer, &endptr, 10);

        printf("\n");
    } while (length == 0 || length < 1);

    char result[length + 1];

    for (int i = 0; i < length; i++) {
        if (randInt(1,2) == 1) {
            result[i] = charSpace[randInt(0, strlen(charSpace) - 1)];
        } else {
            result[i] = toupper(charSpace[randInt(0, sizeof(charSpace) - 1)]);
        }
    }
    result[length] = '\0';

    printf("%s\n", result);

    return 0;
}
