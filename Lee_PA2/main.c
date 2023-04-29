/*	Author: Yu Chung Lee
*	Date: 09/13/21
*
*	Description: This code will prompt user to input values and will call functions to calculate 7 different equations
*/

#include "equations.h"

int main(void) {

	// 1. total series resistance
	int R1 = 0, R2 = 0, R3 = 0;
	double series_resistance = 0.0;

	printf("Enter values to calculate total series resistance\n");

	printf("Enter integer for resistor 1: ");
	scanf("%d", &R1);

	printf("Enter integer for resistor 2: ");
	scanf("%d", &R2);

	printf("Enter integer for resistor 3: ");
	scanf("%d", &R3);

	series_resistance = calculate_series_resistance(R1, R2, R3);

	printf("Total series resistance: %.2lf\n", series_resistance);

	system("pause");

	// 2. sales tax
	double total_sales_tax = 0.0, sales_tax_rate = 0.0, item_cost = 0.0;

	printf("\nEnter values to calculate total sales tax\n");

	printf("Enter sales tax rate: ");
	scanf("%lf", &sales_tax_rate);

	printf("Enter item cost: ");
	scanf("%lf", &item_cost);

	total_sales_tax = calculate_total_sales_tax(sales_tax_rate, item_cost);

	printf("Total sales tax: %lf\n", total_sales_tax);

	system("pause");

	// 3. volume of a right rectuangular pyramid
	double volume_pyramid = 0.0, l = 0.0, w = 0.0, h = 0.0;

	printf("\nEnter values to calculate the volume of a right rectangular pyramid\n");

	printf("Enter length of the base: ");
	scanf("%lf", &l);

	printf("Enter width of the base: ");
	scanf("%lf", &w);

	printf("Enter height of the pyramid: ");
	scanf("%lf", &h);

	volume_pyramid = calculate_volume_pyramid(l, w, h);

	printf("Volume of the right rectangular pyramid: %lf\n", volume_pyramid);

	system("pause");

	// 4. Total parallel resistance
	double parallel_resistance = 0.0;

	printf("\nEnter values to calculate the total parallel resistance\n");

	printf("Enter value for resistor 1: ");
	scanf("%d", &R1);

	printf("Enter value for resistor 2: ");
	scanf("%d", &R2);

	printf("Enter value for resistor 3: ");
	scanf("%d", &R3);

	parallel_resistance = calculate_parallel_resistance(R1, R2, R3);

	printf("Total parallel resistance = %lf\n", parallel_resistance);

	system("pause");

	// 5. Character encoding
	char encoded_character = ' ', plaintext_character = ' ';
	int shift = 0;

	printf("\nEnter values to encode a character\n");

	printf("Enter character to be encoded: ");
	scanf(" %c", &plaintext_character);

	printf("Enter degree of encoding (shift): ");
	scanf("%d", &shift);

	encoded_character = encode_character(plaintext_character, shift);

	printf("Encoded character: %c\n", encoded_character);

	system("pause");

	// 6. Distance between two points
	double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0, distance = 0.0;

	printf("\nEnter coordinate points to calculate the distance between them\n");

	printf("Enter x value for first coordinate: ");
	scanf("%lf", &x1);

	printf("Enter y value for first coordinate: ");
	scanf("%lf", &y1);

	printf("Enter x value for second coordinate: ");
	scanf("%lf", &x2);

	printf("Enter y value for second coordinate: ");
	scanf("%lf", &y2);

	distance = calculate_distance(x1, x2, y1, y2);

	printf("Distance between points: %lf\n", distance);

	system("pause");

	// 7. general equation
	int a = 0;
	double y_input = 0.0, y_output = 0.0, x = 0.0, z = 0.0;

	printf("\nEnter values for the general equation to calculate y\n");

	printf("Enter value for y: ");
	scanf("%lf", &y_input);

	printf("Enter value for z: ");
	scanf("%lf", &z);

	printf("Enter value for x: ");
	scanf("%lf", &x);

	printf("Enter value for a: ");
	scanf("%d", &a);

	y_output = calculate_general_equation(y_input, z, x, a);

	printf("Final value for y: %lf\n", y_output);

	return 0;
}