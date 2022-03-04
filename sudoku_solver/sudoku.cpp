/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: sudoku.cpp
 * Date Created: 2/28/22
 * File Contents: This file contains the function definitions for Programming Challenge 05
 **********************************/

#include "sudoku.h"

// prints a brief greeting to the user
void print_greeting(void)
{
    COUT << "Welcome to sukoku solver!" << ENDL;
}

// populates puzzle based on infile 
void populate_puzzle( IFSTREAM& sudoku_infile, VECTOR<VECTOR<int> > &sudoku )
{
    long unsigned int row, col;

    for(row = 0; row < ROWS; row++) {
        for(col = 0; col < COLS; col++) {
            sudoku_infile >> sudoku[row][col];
        }
    }
}

// updates puzzle index with given value
void update_puzzle( VECTOR<VECTOR<int> >& sudoku, int value, long unsigned int row, long unsigned int col )
{
    sudoku[row][col] = value;
}

// checks if guess is valid
bool check_guess( const VECTOR< VECTOR<int> >& sudoku, int value, long unsigned int row, long unsigned int col )
{
    long unsigned int irow, icol;

    // check if value in location
    if(sudoku[row][col] != 0 )
        return false;

    // check if value in row
    for(icol = 0; icol < COLS; icol++) 
        if(sudoku[row][icol] == value)
            return false;
    
    // check if value in col
    for(irow = 0; irow < ROWS; irow ++)
        if(sudoku[irow][col] == value)
            return false;
    
    // check 3X3 box
    row = row / 3 * 3;
    col = col / 3 * 3;

    for(irow = row; irow < row + 3; irow++ ) 
        for (icol = col; icol < col + 3; icol++ )
            if(sudoku[irow][icol] == value)
                return false;

    return true;
}


bool check_puzzle( const VECTOR< VECTOR<int> >& sudoku ) 
{
    long unsigned int row, col;

    for(row = 0; row < ROWS; row++) {
        for(col = 0; col < COLS; col++ ) {
            if(sudoku[row][col] == 0)
                return false;
        }
    }
    return true;
}

// recursively solves puzzle
bool recursive_solver( VECTOR< VECTOR<int> >& sudoku, long unsigned int row, long unsigned int col )
{
    // base case -- end of the puzzle
    if(check_puzzle(sudoku))
        return true;

    // find next 0
    while(sudoku[row][col] != 0){
        col = (col + 1) % 9;
        if(col == 0)
            row++;
    }

    int test_val;

    for(test_val = 1; test_val <= 9; test_val++) {
        bool valid_input = check_guess(sudoku, test_val, row, col);
        update_puzzle(sudoku, test_val, row, col);
        if(valid_input && recursive_solver(sudoku, row, col))
            return true;
        
        update_puzzle(sudoku, 0, row, col);
    }
    return false;
}

// prints puzzle to stdout
void print_puzzle( const VECTOR< VECTOR<int> >& sudoku )
{
    long unsigned int row, col;

    for(row = 0; row < ROWS; row++) {
        for(col = 0; col < COLS; col++) {
            COUT << sudoku[row][col] << " ";
        }
        COUT << ENDL;
    }
}

// prints puzzle to output file
void print_puzzle_to_file( OFSTREAM& sudoku_outfile, const VECTOR< VECTOR<int> >& sudoku )
{
    long unsigned int row, col;

    for(row = 0; row < ROWS; row++) {
        for(col = 0; col < COLS; col++) {
            sudoku_outfile << sudoku[row][col] << " ";
        }
        sudoku_outfile << ENDL;
    }
}