/*	Author: Yu Chung Lee
*	Class: CptS 121 Section 5
*	Date: 12/10/21
*	Description: https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA8.htm
*		sample interview questions
*		8 different problems with a requirements/instructions
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ROW 4
#define MAX_COL 5


#include <stdio.h>
#include <string.h>

typedef struct occurrences {
    int num_occurrences;
    double frequency;
} Occurrences;

char* my_str_n_cat(char*dest_ptr, char* src_ptr, int n);

int binary_search(int arr[], int arr_size, int target_val);

void bubble_sort(char* str_arr[], int str_num);

int is_palindrome(char* str_ptr, int str_len);

int sum_primes(unsigned int n);

void maximum_occurences(char* str_ptr, Occurrences* occ_arr_ptr, int* int_ptr, char* char_ptr);

void max_consecutive_integers(int arr[][MAX_COL], int row_num, int col_num, int** pos_ptr, int* occ_ptr);

void init_occurrences(Occurrences* occ_ptr);

#endif