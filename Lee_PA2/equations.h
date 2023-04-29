/*	Author: Yu Chung Lee
*	Date: 09/13/21
*
*	Description: Calls for math and standard i/o library, initializes functions
*/


#ifndef EQUATIONS_H
#define EQUATIONS_H

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.14159265

#include <math.h>
#include <stdio.h>

#endif

int calculate_series_resistance(int r1, int r2, int r3);

double calculate_total_sales_tax(double sales_tax_rate, double item_cost);

double calculate_volume_pyramid(double l, double w, double h);

double calculate_parallel_resistance(int r1, int r2, int r3);
 
char encode_character(char plaintext_character, int shift);

double calculate_distance(double x1, double x2, double y1, double y2);

double calculate_general_equation(double y, double z, double x, int a);