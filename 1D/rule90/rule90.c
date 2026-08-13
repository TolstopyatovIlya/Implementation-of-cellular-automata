#include <ncurses.h>

#define ESC 27

void newGeneration(const size_t WIDTH, int array[]) {
	int newArray[WIDTH];
	for(size_t i = 0; i < WIDTH; ++i) { 
		int left = i == 0 ? 0 : array[i-1];
		int right = i == WIDTH-1 ? 0 : array[i+1];
		newArray[i] = left ^ right;
	}
	for(size_t i = 0; i < WIDTH; ++i) {
		array[i] = newArray[i];
	}
}

void draw(const size_t WIDTH, int array[]) {
	for(size_t i = 0; i < WIDTH; ++i) {
		printw(array[i] ? "#" : " ");
	}
	printw("\n");
	refresh();
}

int main(void) {
	initscr();
	keypad(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	cbreak();
	curs_set(0);

	const size_t WIDTH = COLS;
	int array[WIDTH];
	for(size_t i = 0; i < WIDTH; ++i) {
		array[i] = 0;
	}
	array[WIDTH/2] = 1;

	int ch;
	while((ch = getch()) != ESC) {
		newGeneration(WIDTH, array);
		draw(WIDTH, array);
		napms(100);
	}

	endwin();
	return 0;
}
