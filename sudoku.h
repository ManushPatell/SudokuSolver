#include <stdio.h>
#include <stdlib.h>
#ifndef SUDOKU_H
#define SUDOKU_H

//suduko.h file


extern int POSSIBLE; // binary for 11111111 (meaning combinations are possible)
extern int SIZE_ROW;
extern int SIZE_COLUMN;
extern int possible[9];


// typedef struct Box // represents 3x3 subgrid
// {
//     int numbers[9];

// } Box;

typedef struct Square //represents each cell in grid
{
    int number; // if 1 then its not a possible combination
    //[0] [0] [0] [0] [0] [0] [0] [0] [0]
    //[9] [8] [7] [6] [5] [4] [3] [2] [1]
    int possible[9]; //possible nums that can go into cell 
    int solvable; 
    int final; 
    // Box * box; //pointer to 3x3 subgrid
    int row; //row num of cell 
    int column; // column num of cell

} Square;
/* sudoku
|     
|--> [0] --> [0] --> Square
             [1] --> Square
             [2] --> Square
             [3] --> Square
             [4] --> Square
             [5] --> Square
             [6] --> Square
             [7] --> Square
             [8] --> Square
|--> [1] --> [0] --> Square
             [1] --> Square
             [2] --> Square
             [3] --> Square
             [4] --> Square
             [5] --> Square
             [6] --> Square
             [7] --> Square
             [8] --> Square */ //understanding triple pointer usage 


int ** createPuzzle();


void printPuzzle(int ** puzzle);
Square *** setUpPuzzle(int ** puzzle);
int findcell(Square *** sudoku, int row, int column, int **puzzle);
int validsolution(Square *** sudoku, int row, int column, int solution, int **puzzle);
void cleanup(int ** puzzle, Square *** sudoku);


#endif