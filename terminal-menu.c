#include <stdio.h>
#include <unistd.h>
#include <termios.h>

char getch_unix() {
	struct termios oldt, newt;
	char ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

void clearConsole() {
	printf("\033[2J\033[H");
	fflush(stdout);
}

int updateMenu(int direction, int selected, int length, char *menu[]) {
    clearConsole();
    
	// 1 = right, 2 = left
	if (direction == 1) {

		if (selected == length - 1) {
			selected = 0;
		} else {
			selected += 1;
		}

		for (int i = 0; i < length; i++) {
			if (i == selected) {
				printf("\033[7m%s\033[0m\t", menu[i]);
			} else {
				printf("%s\t", menu[i]);
			}
		}

		return selected;
	} else if (direction == 2) {

		if (selected == 0) {
			selected = length - 1;
		} else {
			selected -= 1;
		}

		for (int i = 0; i < length; i++) {
			if (i == selected) {
				printf("\033[7m%s\033[0m\t", menu[i]);
			} else {
				printf("%s\t", menu[i]);
			}
		}

		return selected;
	}
}

int main() {
	char* menuOptions[] = {"ONE", "TWO", "THREE"};
	int selectedOption = 0;

	const int length = sizeof(menuOptions) / sizeof(menuOptions[0]);

	for (int i = 0; i < length; i++) {
		if (i == selectedOption) {
			printf("\033[7m%s\033[0m\t", menuOptions[i]);
		} else {
			printf("%s\t", menuOptions[i]);
		}
	}

    char lastKey;

    do {

	char key = getch_unix();

	if (key == 27) { // 27 prefaces the arrow key returned escape code
		if (getch_unix() == 91) { // [
			switch (getch_unix()) {
			case 67:
				selectedOption = updateMenu(1, selectedOption, length, menuOptions);
				break;
			case 68:
				selectedOption = updateMenu(2, selectedOption, length, menuOptions);
				break;
			}
		}
	}

	// printf("%d", selectedOption);
	
	lastKey = key;
	
    } while (lastKey != '\n' && lastKey != '\r');
    
    printf("Final Choice Index: %d", selectedOption);
	return 0;
}
