/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: game_main.cpp
 * Date Created: 2/22/22
 * File Contents: This file contains the main section for 2048 game
 **********************************/

#include "game.h"

int main(){

    // initalize variables 
    int score = 0;
    char user_choice = ' ';
    bool done = false;
    srand((unsigned int)time(0));

    // initalize board
    VECTOR<VECTOR<int> > game_board =
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    initialize_board(game_board);
    generate_new_initial(game_board);
    print_board(game_board, score);
    
    // loop program
    while (user_choice != 'n') {

        user_choice = get_move_choice();

        switch(user_choice) {
            case 'r':
                move_right(game_board, score);
                break;
            case 'l':
                move_left(game_board, score);
                break;
            case 'u':
                move_up(game_board, score);
                break;
            case 'd':
                move_down(game_board, score);
                break;
        }

        generate_new_initial(game_board);
        print_board(game_board, score);
        done = check_board(game_board);

        if (done == true) break;
    }

    return 0;
}