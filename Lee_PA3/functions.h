/*	Author: Yu Chung Lee
*	Class: Cpts 121 lab section 5
*	Date Created: 09/18/21
*	Last Updated: 09/19/21
*		Added variance, standard deviation, min + max gpa sections
*	Description: Reads data from input.dat to calculate and print mean values, standard deviaiton, min + max gpa
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>

double read_double(FILE* infile);

int read_integer(FILE* infile);

double calculate_sum(double num1, double num2, double num3, double num4, double num5);

double calculate_mean(double sum, int number);

double calculate_deviation(double number, double mean);

double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number);

double calculate_standard_deviation(double variance);

double find_max(double number1, double number2, double number3, double number4, double number5);

double find_min(double number1, double number2, double number3, double number4, double number5);

void print_double(FILE* outfile, double number);



#endif