/*	Author: Yu Chung Lee
*	Class: Cpts 121 lab section 5
*	Date Created: 09/18/21
*	Last Updated: 09/19/21
*		Added variance, standard deviation, min + max gpa sections
*	Description: Reads data from input.dat to calculate and print mean values, standard deviaiton, min + max gpa
*/

#include "functions.h"

int main(void) {
	int student1_ID = 0, student2_ID = 0, student3_ID = 0, student4_ID = 0, student5_ID = 0,
		student1_cs = 0, student2_cs = 0, student3_cs = 0, student4_cs = 0, student5_cs = 0;
	double student1_gpa = 0.0, student2_gpa = 0.0, student3_gpa = 0.0, student4_gpa = 0.0, student5_gpa = 0.0,
		student1_age = 0.0, student2_age = 0.0, student3_age = 0.0, student4_age = 0.0, student5_age = 0.0,
		sum_gpa = 0.0, sum_cs = 0.0, sum_age = 0.0,
		mean_gpa = 0.0, mean_cs = 0.0, mean_age = 0.0,
		deviation1 = 0.0, deviation2 = 0.0, deviation3 = 0.0, deviation4 = 0.0, deviation5 = 0.0,
		gpa_variance = 0.0, standard_deviation = 0.0,
		max_gpa = 0.0, min_gpa = 0.0;

	FILE* infile = NULL, *outfile = NULL;
	
	// open .dat files
	infile = fopen("input.dat", "r");
	outfile = fopen("output.dat", "w");

	// reads info for student 1
	student1_ID = read_integer(infile);
	student1_gpa = read_double(infile);
	student1_cs = read_integer(infile);
	student1_age = read_double(infile);

	// reads info for student 2
	student2_ID = read_integer(infile);
	student2_gpa = read_double(infile);
	student2_cs = read_integer(infile);
	student2_age = read_double(infile);

	// reads info for student 3
	student3_ID = read_integer(infile);
	student3_gpa = read_double(infile);
	student3_cs = read_integer(infile);
	student3_age = read_double(infile);

	// reads info for student 4
	student4_ID = read_integer(infile);
	student4_gpa = read_double(infile);
	student4_cs = read_integer(infile);
	student4_age = read_double(infile);

	// reads info for student 5
	student5_ID = read_integer(infile);
	student5_gpa = read_double(infile);
	student5_cs = read_integer(infile);
	student5_age = read_double(infile);

	// calculate sum of gpa
	sum_gpa = calculate_sum(student1_gpa, student2_gpa, student3_gpa, student4_gpa, student5_gpa);

	// calculate sum of class standings
	sum_cs = calculate_sum(student1_cs, student2_cs, student3_cs, student4_cs, student5_cs);

	// calculate sum of ages
	sum_age = calculate_sum(student1_age, student2_age, student3_age, student4_age, student5_age);

	// calculate + print mean gpa
	mean_gpa = calculate_mean(sum_gpa, 5);
	print_double(outfile, mean_gpa);

	// calculate + print mean class standing
	mean_cs = calculate_mean(sum_cs, 5);
	print_double(outfile, mean_cs);

	// calculate + print mean ages
	mean_age = calculate_mean(sum_age, 5);
	print_double(outfile, mean_age);

	// spacer
	fprintf(outfile, "\n");

	// calculate devation for student 1 - 5
	deviation1 = calculate_deviation(student1_gpa, mean_gpa);
	deviation2 = calculate_deviation(student2_gpa, mean_gpa);
	deviation3 = calculate_deviation(student3_gpa, mean_gpa);
	deviation4 = calculate_deviation(student4_gpa, mean_gpa);
	deviation5 = calculate_deviation(student5_gpa, mean_gpa);

	// calculate variance
	gpa_variance = calculate_variance(deviation1, deviation2, deviation3, deviation4, deviation5, 5);

	// calculate + print standard deviation
	standard_deviation = calculate_standard_deviation(gpa_variance);
	print_double(outfile, standard_deviation);

	// find + print min gpa value
	min_gpa = find_min(student1_gpa, student2_gpa, student3_gpa, student4_gpa, student5_gpa);
	print_double(outfile, min_gpa);

	// find + print max gpa value
	max_gpa = find_max(student1_gpa, student2_gpa, student3_gpa, student4_gpa, student5_gpa);
	print_double(outfile, max_gpa);

	// close .dat files
	fclose(infile);
	fclose(outfile);

	return 0;
}