//responsible for creating and showing the puzzle and that sort
#include "sudoku.h"
//puzzle.c file


Square *** setUpPuzzle(int ** puzzle ) //set up puzzle given row and column as parameters
{
    Square *** sudoku;
    int i, j, x;
    

    sudoku = (Square***)malloc(sizeof(Square**) *9); //dynamic mem allocation for 9 rows
    if (sudoku == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
}
    // loop through grids  

    for (i = 0; i < SIZE_ROW; i++ ){ //iterate through # of rows

        sudoku[i] = (Square**)malloc(sizeof(Square*) *9);//dynamic memory allocation for rows 
     
        if (sudoku[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }   

        // loop through columns

        for (j = 0; j <SIZE_COLUMN; j++){ //now stores the rest of the cells in the same row/column

            sudoku[i][j] = (Square*)malloc(sizeof(Square)); //stores memory allocation per cell 
           
            sudoku[i][j] -> number = puzzle[i][j]; //assign value to number (cell) in Square struct

            sudoku[i][j] -> row = i; //assign value to row in Square struct

            sudoku[i][j] -> column = j; //assign value to column in Square struct

           
        if (sudoku[i][j] == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
        }

         for (int x=0; x <9; x++ ) //want to iterate through the possible numbers
            {
                 sudoku[i][j] -> possible[x] = 0; //set all values of index to 0 
            }
        }
    } //end of double for loop

        // iterate through grid
        for (i = 0; i < SIZE_ROW; i++ )
        { 
            for (j = 0; j <SIZE_COLUMN; j++)
        {
            
            if (sudoku[i][j] -> number != 0) //if the number is not zero, its not solvable
            {
                    sudoku[i][j] -> solvable = 0;//set solvable to zero so no solution to that cell
                    
            }            // 0 is possible, 1 is not 
            
            else
                {
                sudoku[i][j] -> solvable = 1; //possible solution exists and we know by number 1
                findcell(sudoku, i, j, puzzle); //takes in sudoku, and i for row and j for column 
                
                
                }
            }
      
        }
        
        return sudoku;

}
int findcell(Square *** sudoku, int row, int column, int ** puzzle)
{   
    // Base case: If the column is out of bounds, move to the next row
    if (column >= SIZE_COLUMN) {
        column = 0;
        row++;
    }

    // Base case: If the row is out of bounds, return a solution
    if (row >= SIZE_ROW) {
        return 1; // Solution found
    }

    // If the current cell is already filled, move to the next cell
    if (sudoku[row][column]->number !=0) {
        return findcell(sudoku, row, column + 1, puzzle);
    }
     int number = sudoku[row][column]->number; //need to implement algorithm here

     
 
    for (int i=0; i < SIZE_ROW; i++) //check the rows
    {
        int filled_number = sudoku[row][i] -> number; 
        if (filled_number != 0) //if the cell in the row has a value not 0
        { //we'll remove from possibilities
            sudoku[row][column] -> possible[filled_number-1] = 1;
            //printf("%d", (sudoku[row][column] -> possible[filled_number-1])); //stating now that, that number is not a possible solution
        } // 0 0 0 0 0 0 1 0 1 
        
    }   
    
    for (int i=0; i < SIZE_COLUMN; i++) //check the columns
    {
        int filled_number = sudoku[i][column] -> number; 
        if (filled_number != 0) //if the cell in the row has a value not 0
        { //we'll remove from possibilities
            sudoku[row][column] -> possible[filled_number-1] = 1; //stating now that, that number is not a possible solution
        
        }
        
    }

    // check the subgrid
    //subgrid[9]; // 9 pointers in an array that point to a subgrid each

    int subgrid_row = row / 3; //find the subgrid based on row position

    int subgrid_column = column/3; //find the subgrid based on column position

    /* 
    Rows 0, 1, 2 → Subgrid Row Index 0
    Rows 3, 4, 5 → Subgrid Row Index 1
    Rows 6, 7, 8 → Subgrid Row Index 2

    Similarly for columns:

    Columns 0, 1, 2 → Subgrid Column Index 0
    Columns 3, 4, 5 → Subgrid Column Index 1
    Columns 6, 7, 8 → Subgrid Column Index 2 */

    for (int r = 0; r < 3; r++)  //assess 3x3 subgrid to see what numbers will not work
    {
        // { int filled_number = sudoku[r][c] -> number;  //0 0, 0, 1, 0 2, 0 3, 
        for (int c = 0; c < 3; c++)
        {
        int filled_number = sudoku[subgrid_row * 3 +r][subgrid_column *3 + c] -> number;
            if (filled_number !=0)
            {
                sudoku[row][column] -> possible[filled_number-1] = 1;
                // printf("%d", (sudoku[row][column] ->possible[filled_number-1]));
                

            }
        }


    }
    /*return a number that is a possible solution to the cell
     iterate through the array of possibilities and see what position hasnt been replaced by 1*/
   

        for (int counter = 0; counter < 9; counter++)
        {
            if (sudoku[row][column] -> possible[counter] ==0)
            {
                
                int solution = counter + 1; // counter is the index, add 1 to get the solution
               
                puzzle[row][column]= solution ; // update the number to the solution
                int isValid;
                isValid = validsolution(sudoku,row, column, solution, puzzle);
              
                if (isValid == 0)  // valid solution  (for now hahah) 
                {
                    
                    
                    int result;
                    result = findcell(sudoku, row, column + 1, puzzle);
                    
                    if (result !=0) // valid solution, so no need to backtrack
                    {
                        
                          return 1;
                        
                    }
                    
                    
                }
                puzzle[row][column] = 0;
                
            }
            
        }
        return 0; //trigger backtracking

}
int validsolution(Square *** sudoku, int row, int column, int solution, int**puzzle)
{
    int count = 0;
    //check if solution has more than one frequency in sudoku NOT PUZZLE 
    
    
    for (int col = 0; col < SIZE_COLUMN; col ++) //iterate through the column 
    {
        if (col != column && puzzle[row][col]== solution)
        {
            count++;
            return 1;
        }
         
    }
    
    for (int row_checker = 0; row_checker < SIZE_ROW; row_checker++ ) //check row
    {
        if (row_checker != row && puzzle[row_checker][column]== solution)
        {
            count++;
            return 1;  // if count more than one then return 
        }
        
    }
    int subgridrow = row/3;
    int subgridcol = column/3;

    for (int r = 0; r < 3; r++) //check subgrid
    {
        for (int c = 0; c < 3; c++)
        {
            if ((subgridrow * 3 + r != row || subgridcol * 3 + c != column) && puzzle[subgridrow *3 + r][subgridcol *3 + c]== solution)
            {
                count++;
                return 1;
            }
        }
    }
    return 0; 







}




int ** createPuzzle(){
    

    int ** puzzle;
    int i,j;
//     int array[9][9] = 
//     {
//         0, 2, 0,    0, 3, 0,    0, 4, 0,
//         6, 0, 0,    0, 0, 0,    0, 0, 3,
//         0, 0, 4,    0, 0, 0,    5, 0, 0,

//         0, 0, 0,    8, 0, 6,    0, 0, 0,
//         8, 0, 0,    0, 1, 0,    0, 0, 6,
//         0, 0, 0,    7, 0, 5,    0, 0, 0,

//         0, 0, 7,    0, 0, 0,    6, 0, 0,
//         4, 0, 0,    0, 0, 0,    0, 0, 8,
//         0, 3, 0,    0, 4, 0,    0, 2, 0,
// }; //our sudoku format, 9x9 box 

    printf("Enter your Sudoku puzzle (0 for empty cells):\n");
    printf("BEWARE, if segmentation fault occurs, your puzzle was not possible\n");
    puzzle = malloc(sizeof(int*) * 9);
    if (puzzle == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < 9; i++) {
        puzzle[i] = malloc(sizeof(int) * 9);
        if (puzzle[i] == NULL) {
            printf("Memory allocation failed\n");      
            return NULL;
        }
    }

    for (i = 0; i < SIZE_ROW; i++ ){
        for (j = 0; j <SIZE_COLUMN; j++){
            printf("Row %d, Column %d: ", i+1, j+1);
            if (scanf("%d", &puzzle[i][j]) != 1) {
                printf("Invalid input! Please enter a number.\n");
                printf("Restarting program...\n");
                exit(0);
            }

// Check if the input value is within the range of 0-9
        if (puzzle[i][j] < 0 || puzzle[i][j] > 9) {
            printf("Invalid input! Please enter a value between 0 and 9.\n");
            printf("Restarting program...\n");
            exit(0);
            }
    }

        
    }
    return puzzle;
}

// new function which will print puzzle

void printPuzzle(int ** puzzle){
        static int second = 0; // Static variable initialized only once //checks if its the second time the function has been called or the first
        second++;
        int i,j;
        if (puzzle == NULL)
        {
            printf("\n Memory Allocation Error \n");
            return;
        }
        printf("-----------------------------\n"); //formatting
        for (i = 0; i < SIZE_ROW ; i++)
        {   // print each row
            for (j = 0; j < SIZE_COLUMN; j++)
            {
                printf(" %d ", puzzle[i][j]);
                
                if ((j + 1) % 3 == 0 && j != 8) {
                    printf("|");
                }
            }

            printf("\n");
            if ((i + 1) % 3 == 0 && (i != 8)) {
            printf("-----------------------------\n");
        }
        
        } // print each line
        printf("------------------------------\n");
    
    if (second == 2) //second time going through meaning its been solved already
    {
        cleanup(puzzle, NULL);
    }
    else
    {
        printf("\n Can you confirm this is the correct sudoku you want to input: (1 for yes, another number for no) \n");
        int userInput, result; //if user messed up inputting the sudoku, they can leave the program through this 
        result = scanf("%d", &userInput);
        if (result != 1 || userInput != 1) //if 
        {
        cleanup(puzzle, NULL);
        exit(0);
        }
    }
    
    
}



void cleanup(int **puzzle, Square ***sudoku) {
    if (puzzle != NULL) {
        for (int i = 0; i < 9; i++) {
            if (puzzle[i] != NULL) {
                free(puzzle[i]);
            }
        }
        free(puzzle);
    }

    if (sudoku != NULL) {
        for (int i = 0; i < 9; i++) {
            if (sudoku[i] != NULL) {
                for (int j = 0; j < 9; j++) {
                    if (sudoku[i][j] != NULL) {
                        free(sudoku[i][j]);
                    }
                }
                free(sudoku[i]);
                sudoku[i] = NULL; // Prevent double free

            }
        }
        free(sudoku);
        sudoku = NULL;
        


}

exit(0);
}


