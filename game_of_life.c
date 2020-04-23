#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "string.h"
#include "math.h"
#include "game_of_life.h"


int main(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // int m = w.ws_row;
    int m = 50;
    int n = w.ws_col;
    cell_t grid[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cell_t cell = {.health = DEAD};
            grid[i][j] = cell;
        }
    }

    setup_grid(m, n, grid);

    for (int k = 0; k < 100000; k ++) {
        jump_to_bottom(m);
        update_grid(m, n, grid);
        display_grid(m, n, grid);
        usleep(300 * 1000);
    }

}

void update_grid(int m, int n, cell_t grid[m][n]) {
    for (int i = 1; i < m-1; i++) {
        for (int j = 1; j < n-1; j++) {
            int n_neighbours = scan_neighbours(i, j, m, n, grid);

            if (grid[i][j].health == ALIVE) {
                // If has two or three neighbours, cell will stay alive
                if (n_neighbours == 2 || n_neighbours == 3) {
                    grid[i][j].health = STAYS_ALIVE;
                }
                // Cell will die
                else {
                    grid[i][j].health = WILL_DIE;
                }
            }
            else if (grid[i][j].health == DEAD) {

                // If has exactly three neighbours, cell will come alive
                if (n_neighbours == 3) {
                    grid[i][j].health = REVIVING;
                }
            }
        }
    }
    for (int i = 1; i < m-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (grid[i][j].health == STAYS_ALIVE || grid[i][j].health == REVIVING) {
                grid[i][j].health = ALIVE;
            }
            else {
                grid[i][j].health = DEAD;
            }
        }
    }
}

int scan_neighbours(int x, int y, int m, int n, cell_t grid[m][n]) {
    int neighbours = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if(!(i ==0 && j == 0)) {
                if (grid[x+i][y+j].health == ALIVE 
                || grid[x+i][y+j].health == STAYS_ALIVE 
                || grid[x+i][y+j].health == WILL_DIE) 
                {
                    neighbours++;
                }
            }
        }
    }
    return neighbours;
}

void display_grid(int m, int n, cell_t grid[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            display_cell(i, j, m, n, grid);
        }
        printf("\n");
    }
}

void display_cell(int x, int y, int m, int n, cell_t grid[m][n]) {
    if (grid[x][y].health == ALIVE) {
        printf("#");
    }
    else if (grid[x][y].health == DEAD) {
        printf(".");
    }
}

void jump_to_bottom(int n) {
    for (int i = 0; i < n; i++) {
        printf("\n");
    }
}

void setup_grid(int m, int n, cell_t grid[m][n]) {
    ten_cell_inf(m, n, grid);
}

void small_explorer(int m, int n, cell_t grid[m][n]) {
    grid[m/2][n/2].health = ALIVE;
    grid[m/2+1][n/2-1].health = ALIVE;
    grid[m/2+1][n/2].health = ALIVE;
    grid[m/2+1][n/2+1].health = ALIVE;
    grid[m/2+2][n/2-1].health = ALIVE;
    grid[m/2+2][n/2+1].health = ALIVE;
    grid[m/2+3][n/2].health = ALIVE;
}


void ten_cell_inf(int m, int n, cell_t grid[m][n]) {
    grid[m/2][n/2].health = ALIVE;
    grid[m/2-1][n/2+2].health = ALIVE;
    grid[m/2][n/2+2].health = ALIVE;
    grid[m/2-2][n/2+4].health = ALIVE;
    grid[m/2-3][n/2+4].health = ALIVE;
    grid[m/2-4][n/2+4].health = ALIVE;
    grid[m/2-3][n/2+6].health = ALIVE;
    grid[m/2-4][n/2+6].health = ALIVE;
    grid[m/2-5][n/2+6].health = ALIVE;
    grid[m/2-4][n/2+7].health = ALIVE;
}