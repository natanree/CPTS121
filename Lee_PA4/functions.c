/*	Author: Yu Chung Lee
*	Class: Cpts 121 Lab Section 5
*	Date Created: 10/03/21
*	Description: Game of craps
*/

#include "functions.h"

/*	Function: adjust_bank_balance
*	Date: 10/10/21
*	Input: 2 doubles (bank balance + wager) and 1 int (add_or_subtract)
*	Precondition: game must have ended and add_or_subtract must be assigned a value
*	Postcondition: returns new balance after +- wager
*/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract) {
	if (add_or_subtract) {
		bank_balance += wager_amount;
	}
	else {
		bank_balance -= wager_amount;
	}
	return bank_balance;
}

/*	Function: get_wager_amount
*	Date:10/09/21
*	Input: n/a
*	Precondition: int wager must be initialized
*	Postcondition: returns a double that user inputs
*/
double get_wager_amount(void) {
	double wager;
	printf("Enter wager amount: ");
	scanf("%lf", &wager);
	return wager;
}

/*	Function: roll_die
*	Date: 10/10/21
*	Input: array and int
*	Precondition: srand must be declared
*	Postcondition: returns random int from 1 - 6
*/
int roll_die(void) {
	int die;
	die = rand() % 6 + 1;
	return die;
}


/*	Function: calculate_sum_dice
*	Date: 10/10/21
*	Input: 2 int values
*	Precondtion: roll_die used to assign random values to die1 and die2
*	Postcondition: returns sum of die1 and die2
*/
int calculate_sum_dice(int die1, int die2) {
	int sum_dice = die1 + die2;
	return sum_dice;
}

/*	Function: is_win_loss_or_point
*	Date: 10/10/21
*	Input: integer sum_dice
*	Precondition: sum_dice must be calculated
*	Postcondition: returns int -1, 0 or 1 depending on sum of dice
*/
int is_win_loss_or_point(int sum_dice) {
	if (sum_dice == 7 || sum_dice == 11) {
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12) {
		return 0;
	}
	else {
		return -1;
	}
}

/*	Function: is_point_loss_or_neither
*	Date: 10/10/21
*	Input: integer sum_dice
*	Precondition: sum_dice must be calculated, point must be assigned
*	Postcondition: returns int 0 or 1 depending on sum of dice
*/
int is_point_loss_or_neither(int sum_dice, int point_value) {
	if (point_value == sum_dice) {
		return 1;
	}
	else if (sum_dice == 7) {
		return 0;
	}
	else {
		return -1;
	}
}

/*	Function: main_menu
*	Date: 10/03/21
*	Input: n/a
*	Precondition: called into main
*	Postcondition: prints main menu, returns option value
*/
int main_menu(void) {
	int option = 0;
	do {
		printf("Welcome to Craps\n");
		printf("Choose an option:\n");
		printf("1. Game Rules\n");
		printf("2. Enter/add balance\n");
		printf("3. Start Game\n");
		printf("4. Exit\n");
		scanf("%d", &option);

	} while (option<1 || option>4);

	return option;
}

/*	Function: print_game_rules
*	Date: 10/03/21
*	Input: n/a
*	Precondition: player chooses print rule choice from main menu
*	Postcondition: prints rules
*/
void print_game_rules(void) {
	printf("You will roll two standard 6 sided dice");
	printf("\nyou will sum up the face up sides of both dices");
	printf("\nYou will win if you roll a total of 7 or 11 on the first throw");
	printf("\nThe house wins if you roll a total of 2, 3 or 12 on the first throw");
	printf("\nAny other total will become your point");
	printf("\nYou must then continue to roll the dice until you get your point again");
	printf("\nIf you roll a 7 before getting the point you lose\n\n");
}

/*	Function: get_bank_balance
*	Date: 10/03/21
*	Input: n/a
*	Precondition: player chooses balance option
*	Postcondition: returns amount player inputs
*/
double get_bank_balance(void) {
	double balance = 0;
	printf("Input balance: ");
	scanf("%lf", &balance);
	return balance;
}

/*	Function: chatter_messages
*	Date: 10/10/21
*	Input: 2 ints, 2 doubles
*	Precondition: must know roll number, game condition, bank balance
*	Postcondition: prints message from conditions
*/
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance) {
	int random = rand() % 4;
	double bank_difference = current_bank_balance - initial_bank_balance;
	if (win_loss_neither == 0) {
		switch (random) {
		case 0:
			printf("Game Over\n");
			break;
		case 1:
			printf("Better Luck Next Time!\n");
			break;
		case 2:
			printf("Don't Lose Hope!\n");
			break;
		case 3:
			printf("How did you manage to lose %lf\n", -1 * bank_difference);
		}
	}
	else if (win_loss_neither == 1) {
		switch (random) {
		case 0:
			printf("Congratulations\n");
			break;
		case 1:
			printf("You Won %lf\n", bank_difference);
			break;
		case 2:
			printf("You're Pretty Lucky\n");
			break;
		case 3:
			printf("The Luck Is Strong With You\n");
		}
	}
	else {
		switch (number_rolls) {
		case 1:
			printf("Unlucky, you still got this\n");
			break;
		case 2:
			printf("Don't worry, third times the charm\n");
			break;
		case 4:
			printf("*yawn* This is getting a bit tiring\n");
		}
	}
}

/*	Function: check_if_bank_balance_zero
*	Date: 10/10/21
*	Input: double value (bank balance)
*	Precondition: get_bank_balance() function must exist, bank_balance must be initialized
*	Postcondition: returns new bank_balance if player replies 'y' else returns same bank_balance of zero
*/
double check_if_bank_balance_zero(double bank_balance) {
	char add_balance;
	if (bank_balance == 0) {
		do {
			printf("Current bank balance is 0\n");
			printf("If you continue with 0 you will not be able to wager money\n");
			printf("Will you add money? y/n\n");
			scanf(" %c", &add_balance);
			if (add_balance == 'y') {
				bank_balance = get_bank_balance();
			}
		} while (add_balance != 'y' && add_balance != 'n');
	}
	return bank_balance;
}