/**********************************
 * Name: Peter Ainsworth
 * Email: painswor@nd.edu
 * File Name: fenwick.h
 * Date Created: 2/15/2022
 * File Contents: This file contains the function declarations for fenwick tree
 **********************************/

#ifndef FENWICK_H
#define FENWICK_H

#include <stdio.h>
#include <stdlib.h>

int* create_array( const char* argv[], long unsigned int num_inputs );

void print_menu();

void print_array( int* the_array, long unsigned int array_len );

int get_choice();

int* make_fenwick( int* array, long unsigned int length );

void update_fenwick( int* array, int* fenwick, long unsigned int array_len );
 
void sum_vals( int* fenwick, long unsigned int array_len );

#endif