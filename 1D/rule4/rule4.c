#include <ncurses.h>
#include <ncurses.h>

#define ESC 27

void newGeneration(const size_t WIDTH, int currentGeneration[]) {
	int newGeneration[WIDTH];
	for(size_t i = 0; i < WIDTH; ++i) {
		int left = i == 0 ? 0 : currentGeneration[i-1];
		int right = i == WIDTH-1 ? 0 : currentGeneration[i+1];
		newGeneration[i] = (!left) & currentGeneration[i] & !right;
	}
	for(size_t i = 0; i < WIDTH; ++i) {
		currentGeneration[i] = newGeneration[i];
	}
}

void draw(const size_t WIDTH, int currentGeneration[]) {
	for(size_t i = 0; i < WIDTH; ++i) {
		printw(currentGeneration[i] ? "#" : " ");
	}
	printw("\n");
	refresh();
}

int main(void) {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);

	const size_t WIDTH = COLS;
	int currentGeneration[WIDTH];
	for(size_t i = 0; i < WIDTH; ++i) {
		currentGeneration[i] = 0;
	}
	currentGeneration[WIDTH/2] = 1;

	int ch;
	while((ch = getch()) != ESC) {
		newGeneration(WIDTH, currentGeneration);
		draw(WIDTH, currentGeneration);
		napms(100);	
	}
	
	endwin();
	return 0;
}
