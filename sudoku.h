#ifndef H_SUDOKU
#define H_SUDOKU
// TODO: Commenter tout mon code
typedef unsigned char BYTE;
typedef enum {
    EASY = 40,
    MEDIUM = 45,
    HARD = 50
} Difficulty;

// FULL GRID GENERATION FUNCTIONS
void fill_grid(BYTE (*)[9]);

BYTE all_tested(BYTE **, BYTE);

void restaure(BYTE **, BYTE);

BYTE good_guest(BYTE (*)[9], BYTE, BYTE);

// DIFFICULTY GRID FUNCTIONS
void create_grid(BYTE (*)[9], Difficulty);
// TODO implement solve functions
BYTE solve(BYTE (*)[9], BYTE);

void zeros_indexes(BYTE (*)[9], BYTE (*), BYTE);

// TEST FUNCTIONS
BYTE check_rows_columns(BYTE (*)[9], BYTE, BYTE);

BYTE check_zone(BYTE (*)[9], BYTE, BYTE);

// UTILITARY FUNCTIONS
void print_grid(BYTE (*)[9]);


#endif // H_SUDOKU
