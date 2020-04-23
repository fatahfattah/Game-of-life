#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#define ROWS 500
#define COLS 500

typedef enum health {
    ALIVE,
    REVIVING,
    DEAD,
    WILL_DIE,
    STAYS_ALIVE
} health_t;

typedef struct cell {
    health_t health;
} cell_t;

void update_grid(int m, int n, cell_t grid[ROWS][COLS]);
void display_grid(int m, int n, cell_t grid[ROWS][COLS]);
void display_cell(int x, int y, int m, int n, cell_t grid[ROWS][COLS]);
int scan_neighbours(int x, int y, int m, int n, cell_t grid[ROWS][COLS]);
void jump_to_bottom(int n);
void setup_grid(int m, int n, cell_t grid[ROWS][COLS]);
void small_explorer(int m, int n, cell_t grid[ROWS][COLS]);
void ten_cell_inf(int m, int n, cell_t grid[ROWS][COLS]);


#endif