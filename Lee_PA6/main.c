/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/07/21
*	Description: battleship game (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA6.htm
*/
#include "functions.h"

int main(void) {
	srand((unsigned int)time(NULL));

	Board p1_board, p2_board;
	Stats p1_stat, p2_stat;
	Gamecondition is_end = notended;
	int placement_choice = 0;
	Playertype player_num = 0;

	FILE* outfile = fopen("battleship.log", "w");

	init_stats(&p1_stat, player);
	init_stats(&p2_stat, bot);
	init_board(&p1_board, player);
	init_board(&p2_board, bot);

	welcome_screen();

	placement_choice = choose_placement_method(placement_choice);

	place_ships(placement_choice, &p1_board);
	place_ships(placement_choice, &p2_board);

	
	printf("Computer's board has been generated\n");

	player_num = choose_starting_player(player_num);
	
	do {
		switch (player_num) {
		case bot:
			print_board(&p1_board);
			print_board(&p2_board);
			bot_shoot(&p1_board, outfile);
			is_end = check_if_ended(&p1_board);
			player_num = player;
			break;
		case player:
			print_board(&p1_board);
			print_board(&p2_board);
			player_shoot(&p2_board, outfile);
			print_board(&p1_board);
			print_board(&p2_board);
			is_end = check_if_ended(&p2_board);
			player_num = bot;
			break;
		}
		if (is_end == notended) {
			system("pause");
			system("cls");
		}
	} while (is_end == notended);
	
	if (player_num == bot) {
		printf("Player1 Wins!\n");
		fprintf(outfile, "Player1 wins, Player2 loses\n\n");
	}
	else {
		printf("Player2 Wins!\n");
		fprintf(outfile, "Player2 wins, Player1 loses\n\n");
	}

	calc_print_stats(&p2_board, &p1_stat, outfile);
	calc_print_stats(&p1_board, &p2_stat, outfile);

	printf("Staticstics outputted to logfile successfully!\n");

	fclose(outfile);

	return 0;
}