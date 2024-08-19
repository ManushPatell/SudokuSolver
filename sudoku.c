#include "sudoku.h"
#include <stdio.h>

#include <stdlib.h>

//implementation file (sudoku.c file)
int POSSIBLE = 0x1FF;
int SIZE_ROW = 9;
int SIZE_COLUMN = 9;
int possible[9]= {0,0,0,0,0,0,0,0,0};


int main(){
    int ** puzzle;
    Square *** sudoku;

    puzzle = createPuzzle(); // create puzzle

    printPuzzle(puzzle); // print puzzle
    
    sudoku = setUpPuzzle(puzzle); //set up puzzle
    
    printf("\n This is your solved sudoku :))\n\n");

    printPuzzle(puzzle); // Print the solved puzzle
    printf("\n");
    // int solution = findcell(sudoku, i, j); 
    
   cleanup(puzzle, sudoku);


    

    return 0;



}