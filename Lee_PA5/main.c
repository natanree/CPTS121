/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 10/17/21
*		10/17/21
*			added do while loop for main menu
* 
*	Description: Game of yahtzee, roll 5 die, choose one of 13 point calculations once, repeat 12 more times, highest score at end of game wins
*/

#include "functions.h"

int main(void) {
	int menu_option = 0;
	do {
		print_menu();
		menu_option = get_menu_option();
		switch (menu_option) {
		case PRINT_RULES:
			print_rules();
			system("pause");
			system("cls");
			break;
		case PLAY_GAME:
			break;
		case EXIT:
			printf("Thank you for playing\n");
	} while (menu_option <= 1 || menu_option > 3);

	
	return 0;
}