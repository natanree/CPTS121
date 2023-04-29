/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5	
*	Date Created: 10/17/21
*		10/17/21
*			added print_menu
*			added get_menu_option
*			added menu_option
*			added print_rules
* 
*	Description: Game of yahtzee, roll 5 die, choose one of 13 point calculations once, repeat 12 more times, highest score at end of game wins
*/
#include "functions.h"

/*	Function: print_menu
*	Date: 10/17/21
*	Input: n/a
*	Precondition: must not be mid game
*	Postcondition: prints menu options
*/
void print_menu(void) {
	printf("1. Rules\n2. Start Game\n3. Exit\n");
}

/*	Function: get_menu_option
*	Date: 10/17/21
*	Input: n/a
*	Preconditon: menu must be printed
*	Postcondition: returns scanned integer value and clears screen
*/
int get_menu_option(void) {
	int temp;
	scanf("%d", &temp);
	system("cls");
	return temp;
}

/*	Function: print_rules
*	Date: 10/17/21
*	Input: n/a
*	Precondition: menu_option == 1 and called through menu_action()
*	Postcondition: prints rules
*/
void print_rules(void) {
	printf("Rules:\n");
	printf("The scorecard used for Yahtzee is composed of two sections, upper and lower.\n");
	printf("A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\n");
	printf("The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
	printf("Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
	printf("If the sum of the scores in the upper section is greater than or equal to 63, then 35 bonus points are added to the players overall score.\n");
	printf("The lower section contains a number of poker like combinations:\n\n");
	printf("Three of a kind:\nCondition: three dice with the same face	Score: sum of all 5 faces\n\n");
	printf("Four of a kind:\nCondition: four dice with the same face		Score: sum of all 5 face\n\n");
	printf("Full House:\nCondition: one pair and three of a kind		Score: 25\n\n");
	printf("Small Straight:\nCondition: sequence of 4 faces(e.g. 1,2,3,4)	Score: 30\n\n");
	printf("Large Straight:\nCondition: sequence of 5 faces(e.g. 1,2,3,4,5)	Score: 40\n\n");
	printf("Yahtzee:\nCondition: five dice with the same face		Score: 50\n\n");
	printf("Chance:\nCondition: can be used whenever			Score: sum of all faces\n\n");
}