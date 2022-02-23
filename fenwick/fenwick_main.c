/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu   
 * File Name: fenwick_main.c
 * Date Created: 2/15/2022
 * File Contents: This file contains the main program for fenwick tree
 **********************************/

#include "fenwick.h"

int main( int argc, const char *argv[] )
{
    // initalize arrays
    int* the_array;
    int* fenwick;
    

    // create arrays based on command line arguments
    the_array = create_array( argv, (long unsigned int)argc );
    long unsigned int length = (long unsigned int)argc;
    fenwick = make_fenwick( the_array, length );

    int user_choice = 0; 

    // loop until user quits
    while( user_choice != 'n' ){

        if ( user_choice != 0) user_choice = get_choice();
        print_menu();
        user_choice = get_choice();

        switch( user_choice ) {
            case '1' : 
                print_array( the_array, length );
                print_array( fenwick, length );
                break;
            case '2':
                sum_vals( fenwick, length );
                break;
            case '3':
                update_fenwick( the_array, fenwick, length );
                break;
        }
        
        user_choice = get_choice();
        fprintf(stdout, "Do you wish to continue (y/n): ");
        user_choice = get_choice();
        fprintf( stdout, "\n" );
    }

    // free pointers
    free( the_array );
    free( fenwick );
    return 0;
}