/* 
 * triangle_game.c:
 *     This program solves for the solution of the Triangle Game and prints
 *     the steps necessary for such a solution. 
 *     
 *     The Triangle Game is played on a triangular board with fifteen 
 *     equally - spaced holes in it. Initially, fourteen of the holes have 
 *     pegs in them, while hole 4 starts out empty. A peg can move by 
 *     jumping over an adjacent peg which is then removed, just like
 *     in checkers. However, unlike in checkers, it is okay to jump
 *     horizontally as well as diagonally (vertical jumps are not allowed).
 *     Also unlike checkers, you can't just move pegs around; the only way
 *     to move a peg is to jump over an adjacent peg into an empty space.
 *
 *     The object of the game is to make the game last as long as possible 
 *     (thirteen moves). The final peg will always be in position 12.
 *
 *     The program represents a board as an array of integers of length 15.
 *     At a given location, if there is a peg there, it is represented as a
 *     1 while a hole is represented as a 0. 
 *     
 *     The main function inputs the initial board setup into solve which then
 *     prints the solution step - by - step using a recursive algorithm. 
 */

# include <stdio.h>
# include "triangle_routines.h"

# define BOARD_SIZE 15
# define NMOVES 36

/* The variable moves describes all the possible moves on a triangle board */
int moves[NMOVES][3] =
{
  {0, 1, 3},
  {3, 1, 0},
  {1, 3, 6},
  {6, 3, 1},
  {3, 6, 10},
  {10, 6, 3},
  {2, 4, 7},
  {7, 4, 2},
  {4, 7, 11},
  {11, 7, 4},
  {5, 8, 12},
  {12, 8, 5},
  {0, 2, 5},
  {5, 2, 0},
  {2, 5, 9},
  {9, 5, 2},
  {5, 9, 14},
  {14, 9, 5},
  {1, 4, 8},
  {8, 4, 1},
  {4, 8, 13},
  {13, 8, 4},
  {3, 7, 12},
  {12, 7, 3},
  {3, 4, 5},
  {5, 4, 3},
  {6, 7, 8},
  {8, 7, 6},
  {7, 8, 9},
  {9, 8, 7},
  {10, 11, 12},
  {12, 11, 10},
  {11, 12, 13},
  {13, 12, 11},
  {12, 13, 14},
  {14, 13, 12}
};

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
 */
int solve(int board[]);


int main(int argc, char * argv[]) {
    int board[BOARD_SIZE];
    triangle_input(board);
    if (!solve(board)) {
        printf("No such set of moves solves the board\n");
    }
    return 0;
}


/* 
 * npegs:
 *    The function returns the number of pegs on the board by 
 *    finding the number of ones in the board list.
 *
 *    Arguments
 *        - board[]: represents a board, an array of 15 integers of 
 *          ones and zeros.
 *
 *    Returns:
 *        - An integer representing the number of pegs on the board
 */
int npegs(int board[]) {
    int count;
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == 1) {
            count++;
        }
    }
    return count;
}


/* 
 * valid_move:
 *    The function returns 1 if the move is valid on this board, 
 *    otherwise return 0. This condition holds if there is a peg at the
 *    starting location and no peg at the final location, and a peg to hop
 *    over at the middle location.
 *
 *    Arguments
 *        - board[]: represents a board, an array of 15 integers of 
 *          ones and zeros.
 *        - move[]: represents a move (taken from the global variable
 *          moves[]), as an array of length 3. The first value is the
 *          starting point while the third is the ending point. The middle
 *          value is the space being hopped over.
 *
 *    Returns:
 *        - A boolean - like integer representing true or false if the move 
 *          is valid.
 */
int valid_move(int board[], int move[]) {
    return ((board[move[0]]) && (board[move[1]]) && (!board[move[2]]));
}

/* 
 * make_move:
 *    This function makes a move on the board. It actually alters the board
 *    to update it after the move has been made.
 *
 *    Arguments
 *        - board[]: represents a board, an array of 15 integers of 
 *          ones and zeros.
 *        - move[]: represents a move (taken from the global variable
 *          moves[]), as an array of length 3. The first value is the
 *          starting point while the third is the ending point. The middle
 *          value is the space being hopped over.
 *
 *    Returns:
 *        - This function does not return anything.
 */
void make_move(int board[], int move[]) {
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}


/* 
 * unmake_move:
 *    This function undoes a move on the board. It actually alters the board
 *    to reset it to before the move had been made.
 *
 *    Arguments
 *        - board[]: represents a board, an array of 15 integers of 
 *          ones and zeros.
 *        - move[]: represents a move (taken from the global variable
 *          moves[]), as an array of length 3. The first value is the
 *          starting point while the third is the ending point. The middle
 *          value is the space being hopped over.
 *
 *    Returns:
 *        - This function does not return anything.
 */
void unmake_move(int board[], int move[]) {
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}


/* 
 * solve:
 *    This function solves the game starting from this board. It returns 1 
 *    if the game can be solved; otherwise it returns 0. It does not 
 *    permanently alter the board passed in. Once a solution is found, 
 *    it prints the boards making up the solution in reverse order. Using
 *    a recursive algorithm, it iterates through all possible moves until
 *    satisfying the base case: the solved_board with only a single peg.
 *
 *    Arguments
 *        - board[]: represents a board, an array of 15 integers of 
 *          ones and zeros.
 *
 *    Returns:
 *        - A boolean - like integer representing true or false if the move
 *          is valid.
 */
int solve(int board[]) {
    /*
     * The variable solvable is meant to be a boolean to represent if a given
     * board is solvable. It will represent the solvability of the "next"
     * possible board after a legal move is made and used to check if 
     * the function should continue its chain of possible moves or give up
     * and try a new combination. It takes the value of 0 if the board is
     * not solvable and 1 if the board is solvable.
     *
     * The variable solved represents if the board is already solved. The 
     * board is solved if it has a single peg, meaning the sum of the board's
     * values is exactly 1 (recall a board is represented as zero if there
     * is no peg in that hole and 1 if there is a peg in that hole). The
     * variable solved is the sum of the values in the board array. It is
     * 1 if the current board is solved, otherwise it is not 1. 
     */
    int i, k, solvable, solved;

    solved = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        solved += board[i];
    }

    /* The base case of the recursion */
    if (solved == 1) {
        triangle_print(board);
        return 1;
    }
    /* The second statement iterates through all the possible moves */
    for (k = 0; k < NMOVES; k++) {
        if (valid_move(board, moves[k])) {
            make_move(board, moves[k]);
            solvable = solve(board);
            unmake_move(board, moves[k]);
            if (solvable == 1) {
                triangle_print(board);
                return 1;
            }
        }
    }
    return 0;
}