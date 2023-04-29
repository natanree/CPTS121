/*	Author: Yu Chung Lee
*	Class: CptS 121 Section 5
*	Date: 12/10/21
*	Description: https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA8.htm
*		sample interview questions
*		8 different problems with a requirements/instructions
*/
#include "functions.h"

/*	Function: my_str_n_cat
*	Date: 12/6/21
*	Input: pointer to destination char array, pointer to source char array, integer n
*	Precondition: character pointers are arrays(strings)
*	Postcondition: adds src string to the end of dest string
*/
char* my_str_n_cat(char* dest_ptr, char* src_ptr, int n) {
	int i = 0, j = 0;
	// find end of destination array
	while (*(dest_ptr + i) != '\0') {
		i++;
	}
	for (;*(src_ptr + j) != '\0' && j < n; ++i, ++j) {
		*(dest_ptr + i) = *(src_ptr + j);
	}
	return dest_ptr;
}

/*	Function: binary_search
*	Date: 12/6/21
*	Input: array of integers, size of array, target value
*	Precondition: array of integers must be sorted
*	Postcondition: returns index at which target val is in array, if not found then returns -1
*/
int binary_search(int arr[], int arr_size, int target_val) {
	int left_index = 1, right_index = arr_size - 1, mid = 0, found = 0, targetindex = -1;
	while (!(found) && left_index <= right_index) {
		mid = (left_index + right_index) / 2;
		if (target_val == arr[mid]) {
			found = 1;
			targetindex = mid;
		}
		else if (target_val < arr[mid]) {
			right_index = mid - 1;
		}
		else {
			left_index = mid + 1;
		}
	}
	return targetindex;
}

/*	Function: bubble_sort
*	Date: 12/6/21
*	Input: pointer to array of pointers to strings, number of strings
*	Precondition: array must be initialized (at least until inputted size)
*	Postcondition: sorts array of strings from shortest to longest, and lowest to highest ascii
*/
void bubble_sort(char* str_arr[], int str_num) {
	int u = str_num - 1, c = 1;
	char* temp_ptr = NULL;
	for (; u > 0; --u) {
		for (c = 1; c <= u; c++) {
			if (strcmp(str_arr[c], str_arr[c - 1]) < 0) {
				temp_ptr = str_arr[c];
				str_arr[c] = str_arr[c - 1];
				str_arr[c - 1] = temp_ptr;
			}
		}
	}
	
}

/*	Function: is_palindrome
*	Date: 12/07/21
*	Input: pointer to a string, length of string
*	Precondition: string is initialized (at least until index of size-1)
*	Postcondition: returns 1(true) if string is palindrome, else 0(false)
*/
int is_palindrome(char* str_ptr, int str_len) {
	int result = 1;
	
	if (str_len == 1) {
		// only 1 character
	}
	else if (*str_ptr == ' ' && *(str_ptr + str_len - 1) == ' ') {
		// white space on both ends
		result = is_palindrome(str_ptr + 1, str_len - 2);
	}
	else if (*str_ptr == ' ') {
		// white space on left end
		result = is_palindrome(str_ptr + 1, str_len - 1);
	}
	else if (*(str_ptr + str_len - 1) == ' ') {
		// white space on right end
		result = is_palindrome(str_ptr, str_len - 1);
	}
	else if (*str_ptr != *(str_ptr + str_len - 1)) {
		// not equal
		result = 0;
	}
	else {
		// if none of the above check next
		result = is_palindrome(str_ptr + 1, str_len - 2);
	}
	return result;
}

/*	Function: sum_primes
*	Date: 12/07/21
*	Input: unsigned integer
*	Precondition: unsigned integer must be greater or equal to 2
*	Postcondition: returns sum of primes from 2 to n
*/
int sum_primes(unsigned int n) {
	int sum = 0, i = 2, is_prime = 1;
	if (n == 2) {
		sum = 2;
	}
	else {
		for (; i < n; ++i) {
			if (n % i == 0) { // checks is n prime
				is_prime = 0;
				break;
			}
		}
		switch (is_prime) {
		case 0: // not prime
			sum = sum_primes(n - 1);
			break;
		case 1: // is prime
			sum = n + sum_primes(n - 1);
			break;
		}
	}
	return sum;
}

/*	Function: maximum_occurences
*	Date: 12/07/21
*	Input: pointer to string, pointer to occurences array, pointer to integer, and pointer to character
*	Precondition: size of Occurences array must be 62, first character pointer must be a string
*	Postcondition: returns highest occuring character, and number of occurences of that character
*/
void maximum_occurences(char* str_ptr, Occurrences* occ_arr_ptr, int* int_ptr, char* char_ptr) {
	int total_char = 0, i = 0, highest_occ_index = 0;
	// alphanumeric -> letters and numbers, 10 numbers + 26 upper + 26 lower = 62 alphanumeric characters
	while (*str_ptr != '\0') { // calculates number of occurences
		if (*str_ptr >= 48 && *str_ptr <= 57) { // numbers
			(occ_arr_ptr + *str_ptr - 48)->num_occurrences++;
		}
		else if (*str_ptr >= 65 && *str_ptr <= 90) { // uppercase
			(occ_arr_ptr + *str_ptr - 55)->num_occurrences++;
		}
		else if (*str_ptr >= 97 && *str_ptr <= 122) { // lowercase
			(occ_arr_ptr + *str_ptr - 61)->num_occurrences++;
		}
		str_ptr++;
		total_char++;
	}
	for (; i < 61; ++i) { // calculates frequency of each character
		(occ_arr_ptr + i)->frequency = (double)(occ_arr_ptr + i)->num_occurrences / total_char;
	}
	for (i = 0; i < 60; ++i) { // finds highest occuring character
		if ((occ_arr_ptr + i)->num_occurrences > (occ_arr_ptr + i + 1)->num_occurrences) {
			highest_occ_index = i;
		}
	}
	// sets indirect value of int_ptr to number of occurences of highest occuring character
	*int_ptr = (occ_arr_ptr + highest_occ_index)->num_occurrences;
	// sets indirect value of char_ptr to character(ascii code) of one of if not the only highest occuring character
	if (highest_occ_index >= 0 && highest_occ_index <= 9) {
		*char_ptr = highest_occ_index + 48;
	}
	else if (highest_occ_index >= 10 && highest_occ_index <= 35) {
		*char_ptr = highest_occ_index + 55;
	}
	else if (highest_occ_index >= 36 && highest_occ_index <= 61) {
		*char_ptr = highest_occ_index + 61;
	}
}

/*	Function: max_consecutive_integers
*	Date: 12/09/21
*	Input: arr of integers, number of rows, number of columns, pointer to a pointer(stores pointer of start of consec), pointer to int
*	Precondition: integer array is initialized, MAX_COL must match number of columns of inputted array
*	Postcondition: returns the pointer to the start of the consecutive same integers, and the number of consecutive appeareances of that integer
*/
void max_consecutive_integers(int arr[][MAX_COL], int row_num, int col_num, int** pos_ptr, int* occ_ptr) {
	int i = 0, j = 0, temp_num_occ = 0, max_consec_occ = 0, temp_num = arr[0][0],
		temp_row = 0, temp_col = 0, max_consec_row = 0, max_consec_col = 0;
	// loop through rows
	for (; i < row_num; ++i) {
		// loop through columns
		for (j = 0; j < col_num; ++j) {
			if (arr[i][j] == temp_num) {
				temp_num_occ += 1;
			}
			else {
				if (max_consec_occ < temp_num_occ) {
					max_consec_occ = temp_num_occ;
					max_consec_row = temp_row;
					max_consec_col = temp_col;
				}
				temp_num = arr[i][j];
				temp_num_occ = 1;
				temp_row = i;
				temp_col = j;
			}
		}
	}
	*pos_ptr = &arr[max_consec_row][max_consec_col];
	*occ_ptr = max_consec_occ;
}

void init_occurrences(Occurrences* occ_ptr) {
	int i = 0;
	for (; i < 62; ++i) {
		occ_ptr[i].frequency = 0.0;
		occ_ptr[i].num_occurrences = 0;
	}
}