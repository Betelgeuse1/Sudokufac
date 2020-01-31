#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sudoku.h"

#define TRUE 1
#define FALSE 0

#define INITIAL_LOOP_TURN 18
// TODO: Améliorer mon code et sa lisibilité
// Typedefs
typedef unsigned char BYTE;

void fill_grid(BYTE (*grid)[9]) {
    BYTE **tested = (BYTE **) calloc(81, sizeof(BYTE *));
    for (BYTE i = 0; i < 81; i++)
        tested[i] = (BYTE *) calloc(9, sizeof(BYTE));

    BYTE position = 0;
    BYTE guest = rand() % 9;

    tested[position][guest] = 1;
    grid[0][0] = guest + 1;

    while (position < 81) {
        guest = rand() % 9;

        if (tested[position][guest] == 1) {
            if (all_tested(tested, position) == TRUE) {
                restaure(tested, position);
                grid[position / 9][position % 9] = 0;
                position -= (position > 0);
            }
            continue;
        }

        tested[position][guest] = 1;

        if (good_guest(grid, position, guest) == TRUE) {
            grid[position / 9][position % 9] = guest + 1;
            position++;
        }
    }

    for (BYTE i = 0; i < 81; i++)
        free(tested[i]);
    free(tested);
}

BYTE all_tested(BYTE **tested, BYTE position) {
    for (BYTE i = 0; i < 9; i++) {
        if (tested[position][i] == 0) {
            return FALSE;

        }
    }
    return TRUE;
}

void restaure(BYTE **tested, BYTE position) {
    for (BYTE i = 0; i < 9; i++) {
        tested[position][i] = 0;

    }
}

BYTE good_guest(BYTE (*grid)[9], BYTE position, BYTE guest) {
    return check_rows_columns(grid, position, guest) && check_zone(grid, position, guest);
}

BYTE check_rows_columns(BYTE (*grid)[9], BYTE position, BYTE guest) {
    BYTE y = position / 9;
    BYTE x = position % 9;
    for (BYTE i = 0; i < 9; i++) {
        if (i != y && grid[i][x] == guest + 1) {
            return FALSE;
        }

        if (i != x && grid[y][i] == guest + 1) {
            return FALSE;
        }
    }
    return TRUE;
}

BYTE check_zone(BYTE (*grid)[9], BYTE position, BYTE guest) {
    BYTE tx = position % 9,
         ty = position / 9,
         cx = tx / 3 * 3 + 1,
         cy = ty / 3 * 3 + 1;

    for (char i = -1; i <= 1; i++) {
        for (char j = -1; j <= 1; j++) {
            if (cx + j != tx && cy + i != ty) {
                if (grid[cy + i][cx + j] == guest + 1) {
                    return FALSE;

                }
            }
        }
    }

    return TRUE;
}

void create_grid(BYTE (*grid)[9], Difficulty dif) {
    fill_grid(grid);

    BYTE nums_of_zeros = 0;
    // Empty 18 cells
    for (; nums_of_zeros < INITIAL_LOOP_TURN; nums_of_zeros++)
        grid[rand() % 9][rand() % 9] = 0;

    BYTE temp_grid[9][9] = {0};
    while (nums_of_zeros < dif) {
        BYTE tx = rand() % 9,
             ty = rand() % 9;

        if (grid[ty][tx] == 0)
            continue;
        
        memcpy(temp_grid, grid, sizeof(BYTE) * 9 * 9);
        temp_grid[ty][tx] = 0;

        if (solve(temp_grid, nums_of_zeros) == TRUE) {
            grid[ty][tx] = 0;
            nums_of_zeros++;
        }


    }
}

BYTE solve(BYTE (*grid)[9], BYTE nums_of_zeros) {
    BYTE *indexes = (BYTE *) calloc(nums_of_zeros, sizeof(BYTE)); 
    zeros_indexes(grid, indexes, nums_of_zeros);

    // We create a 2D array => BYTE[nums_of_zeros][9]
    BYTE **tested = (BYTE **) calloc(nums_of_zeros, sizeof(BYTE*));
    for (BYTE i = 0; i < nums_of_zeros; i++)
        tested[i] = (BYTE*) calloc(9, sizeof(BYTE));

    BYTE count = 0,
         position = 0;
    // TODO: Changer la résolution des grilles pour une plus humaine
    while(count < nums_of_zeros) {
        if (position == nums_of_zeros)
            position = 0;

        BYTE guest = rand() % 9;
        BYTE index = indexes[position];

        if (tested[position][guest] == 1) {
            if (all_tested(tested, position) == TRUE) {
                restaure(tested, position);
                grid[index / 9][index % 9] = 0;
                position -= (position > 0);
            }
            continue;
        }

        tested[position][guest] = 1;
        if (good_guest(grid, index, guest) == TRUE) {
            if (count == position)
                count++;

            grid[index / 9][index % 9] = guest + 1;
            position++;
        }
    }
    // Free all memory blocks before returning
    free(indexes);
    for (BYTE i = 0; i < nums_of_zeros; i++)
        free(tested[i]);
    free(tested);

    return TRUE;
}

void zeros_indexes(BYTE (*grid)[9], BYTE (*indexes), BYTE nums_of_zeros) {
    for (BYTE i = 0, j = 0; i < 81; i++) {
        if (grid[i / 9][i % 9] == 0)
            indexes[j++] = i;

        if (j >= nums_of_zeros)
            break;
    }
}

void print_grid(BYTE (*grid)[9]) {
    for (BYTE i = 0; i < 9; i++) {
        for (BYTE j = 0; j < 9; j++) {
            printf("%d", grid[i][j]);
        }
        if (i != 8)
            printf("\n");
    }
}
