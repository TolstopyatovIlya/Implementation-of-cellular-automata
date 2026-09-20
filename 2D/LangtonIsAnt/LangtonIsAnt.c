#include <ncurses.h>

#define ESC 27

typedef struct {
	int y;
	int x;
	int dy;
	int dx;
} Ant;

void newGeneration(const size_t HEIGHT, const size_t WIDTH, int generation[HEIGHT][WIDTH], Ant* ant) {
	for(size_t i = 0; i < 2; ++i) {
		if(ant->x < 0 || ant->x >= (int)WIDTH || ant->y >= (int)HEIGHT || ant->y < 0) {
			break;
		}
		if(generation[ant->y][ant->x] == 0) {
			generation[ant->y][ant->x] = 1;
			int temp = ant->dx;
			ant->dx = -ant->dy;
			ant->dy = temp;
		} else if(generation[ant->y][ant->x] == 1) {
			generation[ant->y][ant->x] = 0;
			int temp = ant->dx;
			ant->dx = ant->dy;
			ant->dy = -temp;
		}
		ant->x += ant->dx;
		ant->y += ant->dy;
	}
}

void draw(const size_t HEIGHT, const size_t WIDTH, int generation[HEIGHT][WIDTH]) {
	move(0, 0);
	for(size_t y = 0; y < HEIGHT; ++y) {
		for(size_t x = 0; x < WIDTH; ++x) {
			printw(generation[y][x] ? "#" : " ");
		}
	}
	refresh();
}

int main(void) {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);

	const size_t HEIGHT = LINES;
	const size_t WIDTH = COLS;
	int generation[HEIGHT][WIDTH];
	for(size_t y = 0; y < HEIGHT; ++y) {
		for(size_t x = 0; x < WIDTH; ++x) {
			generation[y][x] = 0;
		}
	}
	Ant ant = {(int)HEIGHT/2, (int)WIDTH/2, 0, -1};
	int ch;
	while((ch = getch()) != ESC) {
		newGeneration(HEIGHT, WIDTH, generation, &ant);
		draw(HEIGHT, WIDTH, generation);
		napms(100);
	}
	
	endwin();
	return 0;
}
