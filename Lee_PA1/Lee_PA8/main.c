/*	Author: Yu Chung Lee
*	Class: CptS 121 Section 5
*	Date: 12/10/21
*	Description: https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA8.htm
*		sample interview questions
*		8 different problems with a requirements/instructions
*/
#include "functions.h"

int main(void) {
	// q1
	char dest_str[15] = "string", src_str[5] = "cat", *str_ptr = NULL;
	printf("String1: %s\n", dest_str);
	printf("String2: %s\n", src_str);
	str_ptr = my_str_n_cat(dest_str, src_str, 4);
	puts(str_ptr);
	printf("\n");

	// q2
	int target_val = 8, arr[8] = { 0, 2, 3, 6, 8, 9, 11, 14 }, target_index = 0;
	target_index = binary_search(arr, 8, target_val);
	for (int i = 0; i < 8; ++i) {
		printf("%d ", arr[i]); // prints out array
	}
	printf("\nTarget Value: %d\nTarget Index: %d\n", target_val, target_index);

	// q3
	char* str_arr[3] = { "dog", "cat", "meow" };
	printf("\nBefore bubble sort:\n");
	for (int i = 0; i < 3; ++i) {
		fputs(str_arr[i], stdout); // prints out array
		printf(" ");
	}
	bubble_sort(str_arr, 3);
	printf("\nAfter bubble sort:\n");
	for (int i = 0; i < 3; ++i) {
		fputs(str_arr[i], stdout); // prints out array
		printf(" ");
	}

	// q4
	char palindrome[] = "ra ce car";
	int palin_bool = 0;
	printf("\n\n%s\n", palindrome);
	palin_bool = is_palindrome(palindrome, strlen(palindrome));
	if (palin_bool == 1) {
		printf("is palindrome\n");
	}
	else {
		printf("not palindrome\n");
	}
	
	// q5 (sum of primes)
	int prime_num = 20, sum_prime = 0;
	printf("\nis_prime 'n': %d\n", prime_num);
	sum_prime = sum_primes(prime_num);
	printf("Sum of primes: %d\n", sum_prime);

	// q6 (max occurence)
	Occurrences test_occ[62];
	char occ_str[] = "test string", char_ptr = '\0';
	int occ_num = 0;
	init_occurrences(test_occ);
	maximum_occurences(occ_str, test_occ, &occ_num, &char_ptr);
	printf("\n%s\n", occ_str);
	printf("Character: %c\n", char_ptr);
	printf("Occurrences: %d\n", occ_num);

	// q7 (bonus)
	int two_d_arr[MAX_ROW][MAX_COL] = { {-5,6,0,2,2}, {2,2,2,9,3}, {3,3,2,1,-8}, {7,-2,6,0,4} }, *ptr_to_loc = NULL, num_of_consec_integer = 0;
	max_consecutive_integers(two_d_arr, MAX_ROW, MAX_COL, &ptr_to_loc, &num_of_consec_integer);
	printf("\nAddress of two_d_arr[0][3]: %p\n", &two_d_arr[0][3]);
	printf("Address of start of max consecutive sequence of same int: %p\n", ptr_to_loc);
	printf("number of consecutive same integer: %d\n", num_of_consec_integer);

	return 0;
}