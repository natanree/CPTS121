/*	Author: Yu Chung Lee
*	Class: Cpts 121 lab section 5
*	Date Created: 09/18/21
*	Last Updated: 09/19/21
*		Added variance, standard deviation, min + max gpa sections
*	Description: Reads data from input.dat to calculate and print mean values, standard deviaiton, min + max gpa
*/

#include "functions.h"

/*	Function: read_double
*	Date Created: 09/18/21
*	Input: double precision floating point value from input.dat
*	Precondition: value from file must be a double (integers before must be read already)
*	Postcondition: returns double from input.dat
*/
double read_double(FILE* infile) {
	double input_value;
	fscanf(infile, "%lf", &input_value);
	return input_value;
}

/*	Function: read_integer
*	Date Created: 09/18/21
*	Input: integer value from input.dat
*	Precondition: value from file must be a integer (double before must be read already)
*	Postcondition: returns integer from input.dat
*/
int read_integer(FILE* infile) {
	int input_value;
	fscanf(infile, "%d", &input_value);
	return input_value;
}

/*	Function: calculate_sum
*	Date Created: 09/18/21
*	Input: Double values from input.dat
*	Precondition: Data from input.dat must be read into main
*	Postcondition: returns sum of data set
*/
double calculate_sum(double num1, double num2, double num3, double num4, double num5) {
	return num1 + num2 + num3 + num4 + num5;
}

/*	Function: calculate_mean
*	Date Created: 09/18/21
*	Input: sum double values
*	Precondition: data from input.dat must be read into main + sum of values must be calculated
*	Postcondition: returns mean value of data set
*/
double calculate_mean(double sum, int number) {
	if (number == 0) {
		return -1.0;
	}
	else {
		return sum / number;
	}
}

/*	Function: calculate_deviation
*	Date Created: 09/18/21
*	Input: gpa value + mean gpa value
*	Precondition: gpa values must be read from input.dat + mean gpa must be calculated
*	Postcondition: returns deviation value
*/
double calculate_deviation(double number, double mean) {
	return number - mean;
}

/*	Function: calculate_variance
*	Date Created: 09/19/21
*	Input: deviation values, number of deviations
*	Precondition: calculate_mean must be defined, deviation values must be calculated
*	Postcondition: returns variance value
*/
double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number) {
	double sum_deviation, variance;
	sum_deviation = pow(deviation1, 2) + pow(deviation2, 2) + pow(deviation3, 2) + pow(deviation4, 2) + pow(deviation5, 2);
	
	variance = calculate_mean(sum_deviation, number);

	return variance;
} 

/*	Function: calculate_standard_deviation
*	Date Created: 09/19/21
*	Input: varaince value
*	Precondition: variance must be calculated
*	Postcondition: returns standard deviation
*/
double calculate_standard_deviation(double variance) {
	return sqrt(variance);
}

/*	Function: find_max
*	Date Created: 09/19/21
*	Input: 5 double precision values
*	Preconditon: 5 double precision values must be inputted
*	Postcondition: returns the greatest value
*/
double find_max(double number1, double number2, double number3, double number4, double number5) {
	double max = number1;
	if (number2 > max) {
		max = number2;
	}
	if (number3 > max) {
		max = number3;
	}
	if (number4 > max) {
		max = number4;
	}
	if (number5 > max) {
		max = number5;
	}

	return max;
}

/*	Function: find_min
*	Date Created: 09/19/21
*	Input: 5 double precision values
*	Preconditon: 5 double precision values must be inputted
*	Postcondition: returns the smallest value
*/
double find_min(double number1, double number2, double number3, double number4, double number5) {
	double min = number1;
	if (number2 < min) {
		min = number2;
	}
	if (number3 < min) {
		min = number3;
	}
	if (number4 < min) {
		min = number4;
	}
	if (number5 < min) {
		min = number5;
	}

	return min;
}
/*	Function: print_double
*	Date Created: 09/18/21
*	Input: .dat file name + number to be printed
*	Precondition: number to be printed must exist and be inputted, file name (outfile) must be called
*	Postcondition: prints value onto output.dat
*/
void print_double(FILE* outfile, double number) {
	fprintf(outfile, "%.2lf\n", number);
}