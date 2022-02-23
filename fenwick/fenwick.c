/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: fenwick.c
 * Date Created: 2/15/2022
 * File Contents: This file contains the function definitions for fenwick tree
 **********************************/

#include "fenwick.h"

// create array based on command line input
int* create_array( const char* argv[], long unsigned int num_inputs ) 
{
    // dynamically allocate array
    int* the_array = (int*)malloc( num_inputs * sizeof(int) );
    the_array[0] = 0;

    // assign values to array based on inputted chars
    long unsigned int iter;
    for( iter = 1; iter < num_inputs; iter++ ) {

        the_array[iter] = *argv[iter] - 48 ;
    }

    // return starting address of array
    return (the_array);
}

// print menu for user choices
void print_menu()
{
    fprintf(stdout, "Select your choice:\n");
    fprintf(stdout, "1: Print array and fenwick tree\n");
    fprintf(stdout, "2: Calculate range and sum\n");
    fprintf(stdout, "3. Update array and Fenwick Tree\n");
    fprintf(stdout, "Enter your selection: ");
}

// iteratively print array inputted
void print_array( int* the_array, long unsigned int array_len ) 
{
    long unsigned int iter;
    for( iter = 0; iter < array_len; iter++ ){

        printf( "%d ", the_array[iter] );
    }
    fprintf(stdout, "\n");
}

// read user choice from stdin
int get_choice()
{
    int user_choice;
    user_choice = fgetc(stdin);

    // return user choice
    return user_choice;
}

// create fenwick array based upon inputted array
int* make_fenwick( int* array, long unsigned int length )
{
    // intialize
    int* fenwick = (int*)malloc( length * sizeof(int) );
    long unsigned int iter;

    // copy initial array to fenwick tree
    for( iter = 0; iter < length; iter++ ) 
        fenwick[iter] = array[iter];
    
    // set fenwick values
    long unsigned int parent_location;
    int i = 0;

    for( iter = 0; iter < length; iter++ ) {

        parent_location = iter + (long unsigned int)( i & -i );

        if ( parent_location < length )
            fenwick[parent_location] = fenwick[iter] + fenwick[parent_location];
        
        i++;
    }

    // return starting address of fenwick array
    return (fenwick);
}


void update_fenwick( int* array, int* fenwick, long unsigned int array_len )
{
    // read in new location and value of fenwick tree
    int new_location;
    int new_value;

    fprintf( stdout, "Enter the location and value to update in the initial array: " );
    fscanf( stdin, " %d %d", &new_location, &new_value );

    // create difference integer
    int difference = new_value - array[ (long unsigned int)new_location ];
    array[ (long unsigned int)new_location ] = new_value;

    // update fenwick
    while( (long unsigned int)new_location < array_len ) {

        fenwick[new_location] += difference;
        new_location += new_location & -new_location;
    }
}

// sum consecutive vals in array
void sum_vals( int* fenwick, long unsigned int array_len ) 
{
    // read in indicies
    int left, right;
    fprintf( stdout, "Enter the range to calculate, between 1 and %lu: ", array_len-1 );
    fscanf( stdin, "%d %d", &left, &right);

    fprintf( stdout, "The sum from %d to %d is ", left, right );

    // sum a
    int sum_right = 0;
    while( right > 0){
        sum_right += fenwick[(long unsigned int)right];
        right -= right & -right;
    }    

    // sum left
    int sum_left = 0;
    --left;
    while( left > 0){
        sum_left += fenwick[(long unsigned int)left];
        left -= left & -left;
    }

    // print result
    fprintf( stdout, "%d\n", sum_right - sum_left );

    if ( (long unsigned int) left > array_len )
        fprintf( stdout, "check\n" );
}