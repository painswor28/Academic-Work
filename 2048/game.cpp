/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: game.cpp
 * Date Created: 2/22/22
 * File Contents: This file contains the function definitions for 2048 game
 **********************************/

#include "game.h"

// generates starting board and prints starting location
void initialize_board( VECTOR< VECTOR <int> > &game_board ) 
{
    int num = rand()%15;

    int init_height = num / 4;
    int init_width = num % 4;

    COUT << "Initial Location: (" << init_height << ", " << init_width << ")" << ENDL;

    game_board[init_height][init_width] = 2;
}

// prints board with formatting, space for 0 vales
void print_board( const VECTOR< VECTOR<int> >& game_board, const int score ) 
{
    COUT << "Score: " << score << ENDL;

    long unsigned int iter, jter;

    for (iter = 0; iter < game_board.size(); iter++) {
        COUT << "---------" << ENDL;

        for (jter = 0; jter < game_board[0].size(); jter++) {
            COUT << "|";
            if (game_board[iter][jter] != 0)
                COUT << game_board[iter][jter];
            else
                COUT << " ";
        }

        COUT << "|" << ENDL;
    }

    COUT << "---------" << ENDL;
}

// returns true if further moves avaialbe, else returns false
bool check_board( const VECTOR<VECTOR<int> > & game_board)
{
    long unsigned int iter, jter;

    for (iter = 0; iter < game_board.size(); iter++) {
        for (jter = 0; jter < game_board[0].size(); jter++) {

            if (game_board[iter][jter] == 0) 
                return false;
        }
    }

    return true;
}

// generates new tile at random location containig 0
void generate_new_initial( VECTOR<VECTOR<int> > & game_board )
{
    int init_height;
    int init_width;

    do {
        int num = rand()%15;
        init_height = num / 4;
        init_width = num % 4;

    } while (game_board[init_height][init_width] != 0);
   
   game_board[init_height][init_width] = 2;
}

// reads user choice from stdin
char get_move_choice()
{
    char move_choice;
    COUT << "Enter choice" << ENDL;
    COUT << "r for Right, l for Left, d for down, u for up: ";
    CIN >> move_choice;
    return move_choice;
}

// performs a left shift of the board
void move_left( VECTOR< VECTOR<int> >& game_board, int& score )
{
    long unsigned int iter, jter, kter;

    for (iter = 0; iter < game_board.size(); iter++) {
        
        for (jter = game_board[0].size()-1; jter >= 1; jter--) {
            
            if (game_board[iter][jter-1] == 0) {
                game_board[iter][jter-1] = game_board[iter][jter];
                game_board[iter][jter] = 0;

                for (kter = jter; kter <= game_board[0].size()-2; kter++) {
                    game_board[iter][kter] = game_board[iter][kter+1];
                }

                game_board[iter][game_board[0].size()-1] = 0;
            }
        }

        for (jter = 0; jter <= game_board[0].size()-2; jter++) {

            if (game_board[iter][jter+1] == game_board[iter][jter]) {
                game_board[iter][jter] *= 2;
                score += game_board[iter][jter];

                for (kter = jter + 1; kter <= game_board.size()-2; kter++) {
                    game_board[iter][kter] = game_board[iter][kter+1];
                }

                game_board[iter][game_board[0].size()-1] = 0;
            }
        }
    }
}

void move_right( VECTOR< VECTOR<int> > & game_board, int& score )
{
    long unsigned int iter, jter, kter;

    for (iter = 0; iter < game_board.size(); iter++) {

        for (jter = 0; jter < game_board[0].size()-1; jter++){

            if (game_board[iter][jter+1] == 0) {
                game_board[iter][jter+1] = game_board[iter][jter];
                game_board[iter][jter] = 0;

                for (kter = jter; kter <= 1; kter--) {
                    game_board[iter][kter] = game_board[iter][kter-1];
                }

                game_board[iter][0] = 0;
            }
        }

        for (jter = game_board[0].size()-1; jter >= 1; jter--) {

            if (game_board[iter][jter-1] == game_board[iter][jter]) {
                game_board[iter][jter] *= 2;
                score += game_board[iter][jter];

                for (kter = jter-1; kter >= 1; kter--) {
                    game_board[iter][kter] = game_board[iter][kter-1];
                } 

                game_board[iter][0] = 0;
            }
        }
    }
}


void move_up( VECTOR< VECTOR<int> >& game_board, int& score ) 
{
    long unsigned int iter, jter, kter;

    for (jter = 0; jter < game_board[0].size(); jter++) {
        
        for (iter = game_board.size()-1; iter >= 1; iter--) {
            
            if (game_board[iter-1][jter] == 0) {
                game_board[iter-1][jter] = game_board[iter][jter];
                game_board[iter][jter] = 0;

                for (kter = iter; kter <= game_board.size()-2; kter++) {
                    game_board[kter][jter] = game_board[kter+1][jter];
                }

                game_board[game_board.size()-1][jter] = 0;
            }
        }
        
        for (iter = 0; iter < game_board.size()-2; iter++) {
            
            if (game_board[iter+1][jter] == game_board[iter][jter]) {
                game_board[iter][jter] *= 2;
                score += game_board[iter][jter];

                for (kter = iter + 1; kter <= game_board.size()-2; kter++) {
                    game_board[kter][jter] = game_board[kter+1][jter];
                }

                game_board[game_board[0].size()-1][jter] = 0;
            }
        }
    }
}


void move_down( VECTOR< VECTOR<int> >& game_board, int& score )
{
    long unsigned int iter, jter, kter;

    for (jter = 0; jter < game_board[0].size(); jter++) {

        for (iter = 0; iter < game_board.size()-1; iter++) {

            if (game_board[iter+1][jter] == 0) {
                game_board[iter+1][jter] = game_board[iter][jter];
                game_board[iter][jter] = 0;

                for (kter = iter; kter >= 1; kter--) {
                    game_board[kter][jter] = game_board[kter-1][jter];
                }

                game_board[0][jter] = 0;
            }
        }
        
        for (iter = game_board.size() - 1; iter >= 1; iter--) {
            
            if (game_board[iter-1][jter] == game_board[iter][jter]) {
                game_board[iter][jter] *= 2;
                score += game_board[iter][jter];

                for (kter = iter - 1; kter >= 1; kter--) {
                    game_board[kter][jter] = game_board[kter-1][jter];
                } 

                game_board[0][jter] = 0;
            }
        }
    }
}