#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"
/*
 * I didn't know but 2D arrays
 * need to be used as pointers to array.
 * So int[9][9] become int(*)[9]
 * which mean multiple things:
 *  -> The size of the first dimension
 *     of a multiple-dimension array 
 *     isn't important.
 *  -> We can upgrade the size of the first
 *     dimension of the array using malloc
 *     but can't change the size of 
 *     the next ones.
*/

Difficulty choose_difficulty(int, char**);

typedef unsigned char BYTE;

// Main loop 
int main(int argc, char *argv[]) {
    srandom(time(NULL));
    // Create the grid
    BYTE grid[9][9] = {0};
    Difficulty dif = choose_difficulty(argc, argv);

    // Create the empty grid
    create_grid(grid, dif);
    // Print final result
    print_grid(grid);

	return EXIT_SUCCESS;
}

Difficulty choose_difficulty(int argc, char **argv) {
    if (argc == 1)
        return EASY;

    if (strcmp(argv[1], "hard") == 0)
        return HARD;
    else if (strcmp(argv[1], "medium") == 0)
        return MEDIUM;

    return EASY;
}