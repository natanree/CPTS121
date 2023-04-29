/*	Author: Yu Chung Lee
*	Date: 09/13/21
*
*	Description: 7 functions used to calculate each equation
*/


#include "equations.h"

/*	Function: calculate_series_resistance()
*	Date Created: 09/13/21
*	Input: Resistance values (1-3)
*	Precondition: R1, R2, R3 must exist
*	Postcondition: Outputs series resistance
*/
int calculate_series_resistance(int r1, int r2, int r3) {

	return r1 + r2 + r3;
}

/*	Function: calculate_total_sales_tax()
*	Date Created: 09/13/2021
*	Input: sales tax rate, item cost
*	Precondition: sales_tax_rate, item_cost must be defined
*	Postoncition: returns total sales tax
*/
double calculate_total_sales_tax(double sales_tax_rate, double item_cost) {

	return sales_tax_rate * item_cost;
}

/*	Function: calculate_volume_pyramid()
*	Date Created: 09/13/21
*	Input: l, w, h
*	Precondition: l, w, h must be defined
*	Postcondition: returns volume of pyramid
*/
double calculate_volume_pyramid(double l, double w, double h) {

	return (l * w * h) / 3;
}

/*	Function: calculate_parallel_resistance()
*	Date Created: 09/13/21
*	Input: R1, R2, R3
*	precondition: r1, r2, r3 must be defined
*	Postcondition: returns parallel resistance
*/
double calculate_parallel_resistance(int r1, int r2, int r3) {

	return (double)1 / (1 / r1 + 1 / r2 + 1 / r3);
}

/*	Formula: encode_character()
*	Date Created: 09/13/21
*	Input: plaintext_character, shift
*	Precondition: plaintext_character, shift must be defined
*	Postcondition: returns encoded character
*/
char encode_character(char plaintext_character, int shift) {

	return (plaintext_character - 'a') + 'A' - shift;
}

/*	Formula: calculate_distance()
*	Date Created: 09/13/21
*	Input: x1, x2, y1, y2
*	Precondition: x1, x2, y1, y2 must be defined
*	Postcondition: returns distance
*/
double calculate_distance(double x1, double x2, double y1, double y2) {

	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

/*	Formula: calculate_general_equation()
*	Date Created: 09/13/21
*	Input: y, z, x, a
*	Precondition: y, z, x, a must be defined
*	Postcondition: returns new value of y
*/
double calculate_general_equation(double y, double z, double x, int a) {

	return y / ((double)3 / 17) - z + x / (a % 2) + PI;
}