/*	Author: Yu Chung Lee
*	Class: Cpts 121 Lab Section 5
*	Date Created: 10/03/21
*	Description: Game of craps
*/

#include "functions.h"

int main(void) {
	srand((unsigned int)time(NULL));

	char game_continue = '\0', balance_zero = '\0';
	int option = 0, die1 = 0, die2 = 0, sum_dice = 0, point_value = 0, game_condition = 0, add_or_subtract = 0, roll_number = 1;
	double initial_bank_balance = 0.0, wager = 0.0, current_bank_balance = 0.0;

	do {
		option = main_menu();

		switch (option) {
		case DISPLAY_RULES:
			print_game_rules();
			break;
		case INPUT_BALANCE:
			current_bank_balance = get_bank_balance();
			break;
		case PLAY_GAME:
			// start of play game
			current_bank_balance = check_if_bank_balance_zero(current_bank_balance);

			printf("Current bank balance: %lf\n", current_bank_balance);
			wager = get_wager_amount();

			while (wager > current_bank_balance) {
				printf("You do not have enough money in your bank balance\n");
				wager = get_wager_amount();
			}

			system("pause");
			// first roll
			die1 = roll_die();
			die2 = roll_die();

			printf("Die 1: %d\n", die1);
			printf("Die 2: %d\n", die2);

			sum_dice = calculate_sum_dice(die1, die2);
			game_condition = is_win_loss_or_point(sum_dice);
			
			if (game_condition == 0) {
				add_or_subtract = 0; // loss
			}
			else if (game_condition == 1) {
				add_or_subtract = 1; // win
			}
			else {
				point_value = sum_dice;
				// point rolls (second roll and onwards)
				do {
					chatter_messages(roll_number, game_condition, initial_bank_balance, current_bank_balance);
					system("pause");
					die1 = roll_die();
					die2 = roll_die();
					roll_number++;
					printf("Die 1: %d\n", die1);
					printf("Die 2: %d\n", die2);

					sum_dice = calculate_sum_dice(die1, die2);
					game_condition = is_point_loss_or_neither(sum_dice, point_value);
					
					
				} while (game_condition == -1);
				if (game_condition == 0) {
					add_or_subtract = 0; // loss
				}
				else if (game_condition == 1) {
					add_or_subtract = 1; // win
				}
			}

			initial_bank_balance = current_bank_balance;
			current_bank_balance = adjust_bank_balance(current_bank_balance, wager, add_or_subtract);

			chatter_messages(roll_number, game_condition, initial_bank_balance, current_bank_balance);

			printf("Remaining bank balance: %lf\n", current_bank_balance);
			break;
			// end of play game
		case EXIT_GAME:
			printf("Thank you for playing!\n");
		}

	} while (option != EXIT_GAME);

	return 0;
}