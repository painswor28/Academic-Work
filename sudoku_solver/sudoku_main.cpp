/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: PC05.cpp
 * Date Created: 2/28/22
 * File Contents: This file contains the function definitions for Programming Challenge 05
 **********************************/

#include "sudoku.h"

int main( const int argc, const char* argv [] )
{
    // verify inputs
    if(argc != 3) {
        COUT << "USAGE: ./PC05 input_file output_file" << ENDL;
        return 1;
    }

    // initialize objects
    IFSTREAM sudoku_infile(argv[1]);
    VECTOR< VECTOR<int> > sudoku(ROWS, VECTOR<int> (COLS));
    OFSTREAM sudoku_outfile( argv[2] );

    void print_greeting(void);

    // solve puzzle
    populate_puzzle( sudoku_infile, sudoku );
    recursive_solver(sudoku, 0, 0);
    print_puzzle(sudoku);
    print_puzzle_to_file(sudoku_outfile, sudoku);

    // close file objects
    sudoku_infile.close();
    sudoku_outfile.close();  

    return 0;
}