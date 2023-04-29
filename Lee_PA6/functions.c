/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/07/21
*		11/07/21
*			added init_stats
*			added init_board
*			added print_board
*			added welcome_screen
*			added choose_placement_method
*			added place_ships
*			added place_carrier-destroyer
*			added random_carrier-destroyer
*		11/08/21
*			added choose_starting_player
*			added check_if_ended
*			added bot_shoot
*			added check_if_sunken
*		11/10/21
*			revised print_board
*			added player_shoot
*			added calc_print_stats
*		11/11/21
*			revised place_carrier-destroyer
*	Description: battleship game (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA6.htm
*/

#include "functions.h"

/*	Function: welcome_screen
*	Date: 11/07/21
*	Input: n/a
*	Precondition: nothing on console
*	Postcondition: prints out welcome message and rules, clears screen after user input
*/
void welcome_screen(void) {
	printf("					Welcome to Battleship\n");
	printf("Rules of battleship:\n");
	printf("1.	This is a two player game\n");
	printf("2.	player 1 is you and player 2 is the computer\n");
	printf("3.	The Player to sink his/her enemy's fleet first wins\n");
	printf("4.	Both players' fleets consist of 5 ships that are hidden from the enemy\n");
	printf("5.	The Carrier (c) has 5 cells\n	Battleship (b) has 4 cells\n	Cruiser (r) has 3 cells\n	Submarine (s) has 3 cells\n	Destroyer (d) has 2 cells\n");
	printf("6.	Ships must be placed horizontally or vertically\n");
	system("pause");
	system("cls");
}

/*	Function: init_stats
*	Date: 11/07/21
*	Input: pointer to Stats
*	Preconition: datatype Stats must exist
*	Postcondition: initiallizes variables in Stats to 0
*/
void init_stats(Stats* stat, int player_num) {
	stat->hits = 0;
	stat->misses = 0;
	stat->shots = 0;
	stat->hit_miss_percent = 0;
	stat->player_num = player_num;
}

/*	Function: init_board
*	Date: 11/07/21
*	Input: pointer to Board struct
*	Precondition: struct of Board must exist
*	Postcondition: initializes Board struct
*/
void init_board(Board* the_board_ptr, int player_num) {
	int i = 0, j = 0;

	the_board_ptr->num_row = MAX_ROW;
	the_board_ptr->num_col = MAX_COL;

	if (player_num == 1) {
		the_board_ptr->bot_or_player = player;
	}
	else {
		the_board_ptr->bot_or_player = bot;
	}
	for (; i < the_board_ptr->num_row; ++i) {
		for (j = 0; j < the_board_ptr->num_col; ++j) {
			the_board_ptr->game_area[i][j].row = i;
			the_board_ptr->game_area[i][j].col = j;
			the_board_ptr->game_area[i][j].ships = none;
			the_board_ptr->game_area[i][j].is_hit = nothit;
		}
	}
}

/*	Function: print_board
*	Date: 11/07/21
*		11/10/21
*			revised structure with switch statement to include printing p2 board
*	Input: pointer to Board struct and the player num
*	Precondition: struct of Board must exist
*	Postcondition: displays the board state in console
*/
void print_board(const Board* the_board_ptr) {
	int i = 0, j = 0;
	printf("Player %d's Board:\n", the_board_ptr->bot_or_player);
	printf("	0	1	2	3	4	5	6	7	8	9\n");
	for (; i < the_board_ptr->num_row; ++i) {
		printf("%d	", i);
		for (j = 0; j < the_board_ptr->num_col; ++j) {
			switch (the_board_ptr->bot_or_player) {
			case bot:
				if (the_board_ptr->game_area[i][j].is_hit == hit) {
					if (the_board_ptr->game_area[i][j].ships == none) {
						printf("m	"); // print miss if cell has no ship and is hit
					}
					else {
						printf("*	"); // print hit if cell has ship and is hit
					}
				}
				else {
					printf("-	"); // print dash if cell is not hit
				}
				break;

			case player:
				if (the_board_ptr->game_area[i][j].is_hit == hit) {
					if (the_board_ptr->game_area[i][j].ships == none) {
						printf("m	"); // print miss if cell has no ship and is hit
					}
					else {
						printf("*	"); // print hit if cell has ship and is hit
					}
				}
				else {
					switch (the_board_ptr->game_area[i][j].ships) {
					case none:
						printf("-	");
						break;
					case destroyer:
						printf("d	");
						break;
					case submarine:
						printf("s	");
						break;
					case cruiser:
						printf("r	");
						break;
					case battleship:
						printf("b	");
						break;
					case carrier:
						printf("c	");
						break;
					}
				}
				break;
			}
		}
		printf("\n");
	}
}

/*	Function: choose_placement_method
*	Date: 11/07/21
*	Input: integer
*	Precondition: board initialized + user exited welcome screen
*	Postcondition: returns 1 or 2 from user input
*/
int choose_placement_method(int choice) {
	do {
		printf("Please select from the following options\n");
		printf("1. Place ships manually\n");
		printf("2. Place ships randomly\n");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 2);
	return choice;
}

/*	Function: place_ships
*	Date: 11/07/21
*	Input: choice of placement method, pointer to board
*	Precondition: player must have chosen placement method
*	Postcondition: changes values of Ship_type in Board
*/
void place_ships(int choice, Board* the_board_ptr) {
	system("cls");
	if (the_board_ptr->bot_or_player == player && choice == 1) {
		place_carrier(the_board_ptr);
		place_battleship(the_board_ptr);
		place_cruiser(the_board_ptr);
		place_submarine(the_board_ptr);
		place_destroyer(the_board_ptr);
	}
	else {
		random_carrier(the_board_ptr);
		random_battleship(the_board_ptr);
		random_cruiser(the_board_ptr);
		random_submarine(the_board_ptr);
		random_destroyer(the_board_ptr);
	}
}

/*	Function: place_carrier
*	Date: 11/07/21
*		11/11/21
*			changed from ranged input to individual coordinate input
*	Input: pointer to board
*	Precondition: player must have chosen manual placement method
*	Postcondition: changes values of Ship_type in Board to carrier
*/
void place_carrier(Board* the_board_ptr) {
	/*char orientation = '\0';
	int col_choice = 0, col2_choice = 0, row_choice = 0, row2_choice = 0, i = 0;
	do {
		printf("Will you place your carrier vertically or horizontally? v/h\n");
		scanf(" %c", &orientation);
	} while (orientation != 'v' && orientation != 'h');
	if (orientation == 'v') {
		do {
			printf("Choose column to place carrier in\n");
			scanf("%d", &col_choice);
		} while (col_choice < 0 || col_choice > 9);
		do {
			printf("Choose smallest and largest row to place carrier in");
			scanf("%d%d", &row_choice, &row2_choice);
		} while (row_choice > the_board_ptr->num_row - 5 || row_choice < 0 || row2_choice < the_board_ptr->num_row - 5);
		for (i = 0; i < 5; ++i) {
			the_board_ptr->game_area[row_choice + i][col_choice].ships = carrier;
		}
	}
	else {
		do {
			printf("Choose row to place carrier in (0-9)\n");
			scanf("%d", &row_choice);
		} while (row_choice < 0 || row_choice > 9);
		do {
			printf("Choose the smallest column your carrier starts on (0-9)");
		} while (col_choice > the_board_ptr->num_col - 4 || col_choice < 0);
		for (i = 0; i < 5; ++i) {
			the_board_ptr->game_area[row_choice][col_choice + i].ships = carrier;
		}
	}*/
	char orientation = '\0';
	int i = 0, j = 0, row = 0, col = 0, rows[10], cols[10], is_re_enter = 0, max = 0;
	do {
		for (i = 0; i < 10; ++i) { // initalizes/resets rows[] and cols[]
			rows[i] = 0;
			cols[i] = 0;
		}
		print_board(the_board_ptr);
		if (is_re_enter) { // reset message
			printf("Set of coordinates were not valid, please re-enter\n");
		}
		for (i = 1; i < 6; ++i) { // prompts user for coordinates
			do {
				printf("Enter coordinate %d for carrier\n", i);
				scanf("%d%d", &row, &col);
			} while (row < 0 || row > 9 || col < 0 || col > 9);
			rows[row] += 1;
			cols[col] += 1;
		}

		for (i = 0; i < 10; ++i) { // checks for whether coordinates have either same row or column
			if (rows[i] == 5) {
				orientation = 'h';
				is_re_enter = 0;
				break;
			}
			else if (cols[i] == 5) {
				orientation = 'v';
				is_re_enter = 0;
				break;
			}
			else {
				is_re_enter = 1;
			}
		}

		switch (orientation) { // if coordinates have same row/col, checks if adjacent coordiantes
		case 'h':
			for (i = 0; i < 6; ++i) {
				if (cols[i] == 1 && cols[i + 1] == 1 && cols[i + 2] == 1 && cols[i + 3] == 1 && cols[i + 4] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		case 'v':
			for (i = 0; i < 6; ++i) {
				if (rows[i] == 1 && rows[i + 1] == 1 && rows[i + 2] == 1 && rows[i + 3] == 1 && rows[i + 4] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		}

		if (is_re_enter) {
			orientation = '\0';
			system("cls");
		}
	} while (is_re_enter);

	switch (orientation) { // places ships
	case 'h':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		max = j + 5;
		for (;j < max; ++j) {
			the_board_ptr->game_area[i][j].ships = carrier;
		}
		break;
	case 'v':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		max = i + 5;
		for (;i < max; ++i) {
			the_board_ptr->game_area[i][j].ships = carrier;
		}
		break;
	}
	system("cls");
}

/*	Function: place_battleship
*	Date: 11/07/21
*		 11/11/21
*			changed from ranged input to individual coordinate input
*	Input: pointer to board
*	Precondition: player must have chosen manual placement method
*	Postcondition: changes values of Ship_type in Board to battleship
*/
void place_battleship(Board* the_board_ptr) {
	/*char orientation = '\0';
	int col_choice = 0, row_choice = 0, i = 0;
	do {
		printf("Will you place your battleship vertically or horizontally? v/h\n");
		scanf(" %c", &orientation);
	} while (orientation != 'v' && orientation != 'h');
	if (orientation == 'v') {
		do {
			printf("Choose column to place battleship in (0-9)\n");
			scanf("%d", &col_choice);
		} while (col_choice < 0 || col_choice > 9);
		do {
			printf("Choose the smallest row your battleship starts on (0-9)");
		} while (row_choice > the_board_ptr->num_row - 3 || row_choice < 0);
		for (i = 0; i < 4; ++i) {
			the_board_ptr->game_area[row_choice + i][col_choice].ships = battleship;
		}
	}
	else {
		do {
			printf("Choose row to place battleship in (0-9)\n");
			scanf("%d", &row_choice);
		} while (row_choice < 0 || row_choice > 9);
		do {
			printf("Choose the smallest column your battleship starts on (0-9)");
		} while (col_choice > the_board_ptr->num_col - 3 || col_choice < 0);
		for (i = 0; i < 4; ++i) {
			the_board_ptr->game_area[row_choice][col_choice + i].ships = battleship;
		}
	}*/
	char orientation = '\0';
	int i = 0, j = 0, row = 0, col = 0, rows[10], cols[10], is_re_enter = 0, max = 0;
	do {
		for (i = 0; i < 10; ++i) { // initalizes/resets rows[] and cols[]
			rows[i] = 0;
			cols[i] = 0;
		}
		print_board(the_board_ptr);
		if (is_re_enter) { // reset message
			printf("Set of coordinates were not valid, please re-enter\n");
		}
		for (i = 1; i < 5; ++i) { // prompts user for coordinates
			do {
				printf("Enter coordinate %d for battleship\n", i);
				scanf("%d%d", &row, &col);
			} while (row < 0 || row > 9 || col < 0 || col > 9);
			rows[row] += 1;
			cols[col] += 1;
		}

		for (i = 0; i < 10; ++i) { // checks for whether coordinates have either same row or column
			if (rows[i] == 4) {
				orientation = 'h';
				is_re_enter = 0;
				break;
			}
			else if (cols[i] == 4) {
				orientation = 'v';
				is_re_enter = 0;
				break;
			}
			else {
				is_re_enter = 1;
			}
		}

		switch (orientation) { // if coordinates have same row/col, checks if adjacent coordiantes
		case 'h':
			for (i = 0; i < 7; ++i) {
				if (cols[i] == 1 && cols[i + 1] == 1 && cols[i + 2] == 1 && cols[i + 3] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		case 'v':
			for (i = 0; i < 7; ++i) {
				if (rows[i] == 1 && rows[i + 1] == 1 && rows[i + 2] == 1 && rows[i + 3] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		}

		switch (orientation) { // checks for overlap
		case 'h':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = j + 4;
			for (;j < max; ++j) {
				if (the_board_ptr->game_area[i][j].ships != none)
				is_re_enter = 1;
				break;
			}
			break;
		case 'v':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = j + 4;
			for (;i < max; ++i) {
				if (the_board_ptr->game_area[i][j].ships != none) {
					is_re_enter = 1;
					break;
				}
			}
			break;
		}

		if (is_re_enter) {
			orientation = '\0';
			system("cls");
		}
	} while (is_re_enter);

	switch (orientation) { // places ships
	case 'h':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;j < max; ++j) {
			the_board_ptr->game_area[i][j].ships = battleship;
		}
		break;
	case 'v':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;i < max; ++i) {
			the_board_ptr->game_area[i][j].ships = battleship;
		}
		break;
	}
	system("cls");
}

/*	Function: place_cruiser
*	Date: 11/07/21
*		11/11/21
*			changed from ranged input to individual coordinate input
*	Input: pointer to board
*	Precondition: player must have chosen manual placement method
*	Postcondition: changes values of Ship_type in Board to cruiser
*/
void place_cruiser(Board* the_board_ptr) {
	/*char orientation = '\0';
	int col_choice = 0, row_choice = 0, i = 0;
	do {
		printf("Will you place your cruiser vertically or horizontally? v/h\n");
		scanf(" %c", &orientation);
	} while (orientation != 'v' && orientation != 'h');
	if (orientation == 'v') {
		do {
			printf("Choose column to place cruiser in (0-9)\n");
			scanf("%d", &col_choice);
		} while (col_choice < 0 || col_choice > 9);
		do {
			printf("Choose the smallest row your cruiser starts on (0-9)");
		} while (row_choice > the_board_ptr->num_row - 2 || row_choice < 0);
		for (i = 0; i < 3; ++i) {
			the_board_ptr->game_area[row_choice + i][col_choice].ships = cruiser;
		}
	}
	else {
		do {
			printf("Choose row to place cruiser in (0-9)\n");
			scanf("%d", &row_choice);
		} while (row_choice < 0 || row_choice > 9);
		do {
			printf("Choose the smallest column your cruiser starts on (0-9)");
		} while (col_choice > the_board_ptr->num_col - 2 || col_choice < 0);
		for (i = 0; i < 3; ++i) {
			the_board_ptr->game_area[row_choice][col_choice + i].ships = cruiser;
		}
	}*/
	char orientation = '\0';
	int i = 0, j = 0, row = 0, col = 0, rows[10], cols[10], is_re_enter = 0, max = 0;
	do {
		for (i = 0; i < 10; ++i) { // initalizes/resets rows[] and cols[]
			rows[i] = 0;
			cols[i] = 0;
		}
		print_board(the_board_ptr);
		if (is_re_enter) { // reset message
			printf("Set of coordinates were not valid, please re-enter\n");
		}
		for (i = 1; i < 4; ++i) { // prompts user for coordinates
			do {
				printf("Enter coordinate %d for cruiser\n", i);
				scanf("%d%d", &row, &col);
			} while (row < 0 || row > 9 || col < 0 || col > 9);
			rows[row] += 1;
			cols[col] += 1;
		}

		for (i = 0; i < 10; ++i) { // checks for whether coordinates have either same row or column
			if (rows[i] == 3) {
				orientation = 'h';
				is_re_enter = 0;
				break;
			}
			else if (cols[i] == 3) {
				orientation = 'v';
				is_re_enter = 0;
				break;
			}
			else {
				is_re_enter = 1;
			}
		}

		switch (orientation) { // if coordinates have same row/col, checks if adjacent coordiantes
		case 'h':
			for (i = 0; i < 8; ++i) {
				if (cols[i] == 1 && cols[i + 1] == 1 && cols[i + 2] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		case 'v':
			for (i = 0; i < 8; ++i) {
				if (rows[i] == 1 && rows[i + 1] == 1 && rows[i + 2] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		}

		switch (orientation) { // checks for overlap
		case 'h':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = j + 3;
			for (;j < max; ++j) {
				if (the_board_ptr->game_area[i][j].ships != none)
					is_re_enter = 1;
				break;
			}
			break;
		case 'v':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = i + 3;
			for (;i < max; ++i) {
				if (the_board_ptr->game_area[i][j].ships != none) {
					is_re_enter = 1;
					break;
				}
			}
			break;
		}

		if (is_re_enter) {
			orientation = '\0';
			system("cls");
		}
	} while (is_re_enter);

	switch (orientation) { // places ships
	case 'h':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;j < max; ++j) {
			the_board_ptr->game_area[i][j].ships = cruiser;
		}
		break;
	case 'v':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;i < max; ++i) {
			the_board_ptr->game_area[i][j].ships = cruiser;
		}
		break;
	}
	system("cls");
}

/*	Function: place_submarine
*	Date: 11/07/21
* 		11/11/21
*			changed from ranged input to individual coordinate input
*	Input: pointer to board
*	Precondition: player must have chosen manual placement method
*	Postcondition: changes values of Ship_type in Board to submarine
*/
void place_submarine(Board* the_board_ptr) {
	/*char orientation = '\0';
	int col_choice = 0, row_choice = 0, i = 0;
	do {
		printf("Will you place your submarine vertically or horizontally? v/h\n");
		scanf(" %c", &orientation);
	} while (orientation != 'v' && orientation != 'h');
	if (orientation == 'v') {
		do {
			printf("Choose column to place submarine in (0-9)\n");
			scanf("%d", &col_choice);
		} while (col_choice < 0 || col_choice > 9);
		do {
			printf("Choose the smallest row your submarine starts on (0-9)");
		} while (row_choice > the_board_ptr->num_row - 2 || row_choice < 0);
		for (i = 0; i < 3; ++i) {
			the_board_ptr->game_area[row_choice + i][col_choice].ships = submarine;
		}
	}
	else {
		do {
			printf("Choose row to place submarine in (0-9)\n");
			scanf("%d", &row_choice);
		} while (row_choice < 0 || row_choice > 9);
		do {
			printf("Choose the smallest column your submarine starts on (0-9)");
		} while (col_choice > the_board_ptr->num_col - 2 || col_choice < 0);
		for (i = 0; i < 3; ++i) {
			the_board_ptr->game_area[row_choice][col_choice + i].ships = submarine;
		}
	}*/
	char orientation = '\0';
	int i = 0, j = 0, row = 0, col = 0, rows[10], cols[10], is_re_enter = 0, max = 0;
	do {
		for (i = 0; i < 10; ++i) { // initalizes/resets rows[] and cols[]
			rows[i] = 0;
			cols[i] = 0;
		}
		print_board(the_board_ptr);
		if (is_re_enter) { // reset message
			printf("Set of coordinates were not valid, please re-enter\n");
		}
		for (i = 1; i < 4; ++i) { // prompts user for coordinates
			do {
				printf("Enter coordinate %d for submarine\n", i);
				scanf("%d%d", &row, &col);
			} while (row < 0 || row > 9 || col < 0 || col > 9);
			rows[row] += 1;
			cols[col] += 1;
		}

		for (i = 0; i < 10; ++i) { // checks for whether coordinates have either same row or column
			if (rows[i] == 3) {
				orientation = 'h';
				is_re_enter = 0;
				break;
			}
			else if (cols[i] == 3) {
				orientation = 'v';
				is_re_enter = 0;
				break;
			}
			else {
				is_re_enter = 1;
			}
		}

		switch (orientation) { // if coordinates have same row/col, checks if adjacent coordiantes
		case 'h':
			for (i = 0; i < 8; ++i) {
				if (cols[i] == 1 && cols[i + 1] == 1 && cols[i + 2] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		case 'v':
			for (i = 0; i < 8; ++i) {
				if (rows[i] == 1 && rows[i + 1] == 1 && rows[i + 2] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		}

		switch (orientation) { // checks for overlap
		case 'h':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = j + 3;
			for (;j < max; ++j) {
				if (the_board_ptr->game_area[i][j].ships != none)
					is_re_enter = 1;
				break;
			}
			break;
		case 'v':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = i + 3;
			for (;i < max; ++i) {
				if (the_board_ptr->game_area[i][j].ships != none) {
					is_re_enter = 1;
					break;
				}
			}
			break;
		}

		if (is_re_enter) {
			orientation = '\0';
			system("cls");
		}
	} while (is_re_enter);

	switch (orientation) { // places ships
	case 'h':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;j < max; ++j) {
			the_board_ptr->game_area[i][j].ships = submarine;
		}
		break;
	case 'v':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;i < max; ++i) {
			the_board_ptr->game_area[i][j].ships = submarine;
		}
		break;
	}
	system("cls");
}

/*	Function: place_destroyer
*	Date: 11/07/21
*		 11/11/21
*			changed from ranged input to individual coordinate input
*	Input: pointer to board
*	Precondition: player must have chosen manual placement method
*	Postcondition: changes values of Ship_type in Board to destroyer
*/
void place_destroyer(Board* the_board_ptr) {
	/*char orientation = '\0';
	int col_choice = 0, row_choice = 0, i = 0;
	do {
		printf("Will you place your destroyer vertically or horizontally? v/h\n");
		scanf(" %c", &orientation);
	} while (orientation != 'v' && orientation != 'h');
	if (orientation == 'v') {
		do {
			printf("Choose column to place destroyer in (0-9)\n");
			scanf("%d", &col_choice);
		} while (col_choice < 0 || col_choice > 9);
		do {
			printf("Choose the smallest row your destroyer starts on (0-9)");
		} while (row_choice > the_board_ptr->num_row - 1 || row_choice < 0);
		for (i = 0; i < 2; ++i) {
			the_board_ptr->game_area[row_choice + i][col_choice].ships = destroyer;
		}
	}
	else {
		do {
			printf("Choose row to place destroyer in (0-9)\n");
			scanf("%d", &row_choice);
		} while (row_choice < 0 || row_choice > 9);
		do {
			printf("Choose the smallest column your destroyer starts on (0-9)");
		} while (col_choice > the_board_ptr->num_col - 1 || col_choice < 0);
		for (i = 0; i < 2; ++i) {
			the_board_ptr->game_area[row_choice][col_choice + i].ships = destroyer;
		}
	}*/
	char orientation = '\0';
	int i = 0, j = 0, row = 0, col = 0, rows[10], cols[10], is_re_enter = 0, max = 0;
	do {
		for (i = 0; i < 10; ++i) { // initalizes/resets rows[] and cols[]
			rows[i] = 0;
			cols[i] = 0;
		}
		print_board(the_board_ptr);
		if (is_re_enter) { // reset message
			printf("Set of coordinates were not valid, please re-enter\n");
		}
		for (i = 1; i < 3; ++i) { // prompts user for coordinates
			do {
				printf("Enter coordinate %d for destroyer\n", i);
				scanf("%d%d", &row, &col);
			} while (row < 0 || row > 9 || col < 0 || col > 9);
			rows[row] += 1;
			cols[col] += 1;
		}

		for (i = 0; i < 10; ++i) { // checks for whether coordinates have either same row or column
			if (rows[i] == 2) {
				orientation = 'h';
				is_re_enter = 0;
				break;
			}
			else if (cols[i] == 2) {
				orientation = 'v';
				is_re_enter = 0;
				break;
			}
			else {
				is_re_enter = 1;
			}
		}

		switch (orientation) { // if coordinates have same row/col, checks if adjacent coordiantes
		case 'h':
			for (i = 0; i < 9; ++i) {
				if (cols[i] == 1 && cols[i + 1] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		case 'v':
			for (i = 0; i < 9; ++i) {
				if (rows[i] == 1 && rows[i + 1] == 1) {
					is_re_enter = 0;
					break;
				}
				else {
					is_re_enter = 1;
				}
			}
			break;
		}

		switch (orientation) { // checks for overlap
		case 'h':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = j + 2;
			for (;j < max; ++j) {
				if (the_board_ptr->game_area[i][j].ships != none)
					is_re_enter = 1;
				break;
			}
			break;
		case 'v':
			for (i = 0; i < 10; ++i) {
				if (rows[i] != 0) {
					break;
				}
			}
			for (j = 0;j < 10; ++j) {
				if (cols[j] != 0) {
					break;
				}
			}
			max = i + 2;
			for (;i < max; ++i) {
				if (the_board_ptr->game_area[i][j].ships != none) {
					is_re_enter = 1;
					break;
				}
			}
			break;
		}

		if (is_re_enter) {
			orientation = '\0';
			system("cls");
		}
	} while (is_re_enter);

	switch (orientation) { // places ships
	case 'h':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;j < max; ++j) {
			the_board_ptr->game_area[i][j].ships = destroyer;
		}
		break;
	case 'v':
		for (i = 0; i < 10; ++i) {
			if (rows[i] != 0) {
				break;
			}
		}
		for (j = 0;j < 10; ++j) {
			if (cols[j] != 0) {
				break;
			}
		}
		for (;i < max; ++i) {
			the_board_ptr->game_area[i][j].ships = destroyer;
		}
		break;
	}
	system("cls");
}

/*	Function: random_carrier
*	Date: 11/07/21
*	Input: pointer to board
*	Precondition: player must have chosen random placement method / bot placement
*	Postcondition: randomly changes values of Ship_type in Board to carrier
*/
void random_carrier(Board* the_board_ptr) {
	int i = 0, row_num = 0, col_num = 0, orientation = rand() % 2; // 0 = vertical, 1 = horizontal
	if (orientation == 0) {
		do {
			row_num = rand() % (the_board_ptr->num_row - 4);
			col_num = rand() % the_board_ptr->num_col;
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 1][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 2][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 3][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 4][col_num].ships != none);
		for (; i < 5; ++i) {
			the_board_ptr->game_area[row_num + i][col_num].ships = carrier;
		}
	}
	else {
		do {
			row_num = rand() % the_board_ptr->num_row;
			col_num = rand() % (the_board_ptr->num_col - 4);
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 1].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 2].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 3].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 4].ships != none);
		for (; i < 5; ++i) {
			the_board_ptr->game_area[row_num][col_num + i].ships = carrier;
		}
	}
}

/*	Function: random_battleship
*	Date: 11/07/21
*	Input: pointer to board
*	Precondition: player must have chosen random placement method / bot placement
*	Postcondition: randomly changes values of Ship_type in Board to battleship
*/
void random_battleship(Board* the_board_ptr) {
	int i = 0, row_num = 0, col_num = 0, orientation = rand() % 2; // 0 = vertical, 1 = horizontal
	if (orientation == 0) {
		do {
			row_num = rand() % (the_board_ptr->num_row - 3);
			col_num = rand() % the_board_ptr->num_col;
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 1][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 2][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 3][col_num].ships != none);
		for (; i < 4; ++i) {
			the_board_ptr->game_area[row_num + i][col_num].ships = battleship;
		}
	}
	else {
		do {
			row_num = rand() % the_board_ptr->num_row;
			col_num = rand() % (the_board_ptr->num_col - 3);
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 1].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 2].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 3].ships != none);
		for (; i < 4; ++i) {
			the_board_ptr->game_area[row_num][col_num + i].ships = battleship;
		}
	}
}

/*	Function: random_cruiser
*	Date: 11/07/21
*	Input: pointer to board
*	Precondition: player must have chosen random placement method / bot placement
*	Postcondition: randomly changes values of Ship_type in Board to cruiser
*/
void random_cruiser(Board* the_board_ptr) {
	int i = 0, row_num = 0, col_num = 0, orientation = rand() % 2; // 0 = vertical, 1 = horizontal
	if (orientation == 0) {
		do {
			row_num = rand() % (the_board_ptr->num_row - 2);
			col_num = rand() % the_board_ptr->num_col;
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 1][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 2][col_num].ships != none);
		for (; i < 3; ++i) {
			the_board_ptr->game_area[row_num + i][col_num].ships = cruiser;
		}
	}
	else {
		do {
			row_num = rand() % the_board_ptr->num_row;
			col_num = rand() % (the_board_ptr->num_col - 2);
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 1].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 2].ships != none);
		for (; i < 3; ++i) {
			the_board_ptr->game_area[row_num][col_num + i].ships = cruiser;
		}
	}
}

/*	Function: random_submarine
*	Date: 11/07/21
*	Input: pointer to board
*	Precondition: player must have chosen random placement method / bot placement
*	Postcondition: randomly changes values of Ship_type in Board to submarine
*/
void random_submarine(Board* the_board_ptr) {
	int i = 0, row_num = 0, col_num = 0, orientation = rand() % 2; // 0 = vertical, 1 = horizontal
	if (orientation == 0) {
		do {
			row_num = rand() % (the_board_ptr->num_row - 2);
			col_num = rand() % the_board_ptr->num_col;
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 1][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 2][col_num].ships != none);
		for (; i < 3; ++i) {
			the_board_ptr->game_area[row_num + i][col_num].ships = submarine;
		}
	}
	else {
		do {
			row_num = rand() % the_board_ptr->num_row;
			col_num = rand() % (the_board_ptr->num_col - 2);
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 1].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 2].ships != none);
		for (; i < 3; ++i) {
			the_board_ptr->game_area[row_num][col_num + i].ships = submarine;
		}
	}
}

/*	Function: random_destroyer
*	Date: 11/07/21
*	Input: pointer to board
*	Precondition: player must have chosen random placement method / bot placement
*	Postcondition: randomly changes values of Ship_type in Board to destroyer
*/
void random_destroyer(Board* the_board_ptr) {
	int i = 0, row_num = 0, col_num = 0, orientation = rand() % 2; // 0 = vertical, 1 = horizontal
	if (orientation == 0) {
		do {
			row_num = rand() % (the_board_ptr->num_row - 1);
			col_num = rand() % the_board_ptr->num_col;
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num + 1][col_num].ships != none);
		for (; i < 2; ++i) {
			the_board_ptr->game_area[row_num + i][col_num].ships = destroyer;
		}
	}
	else {
		do {
			row_num = rand() % the_board_ptr->num_row;
			col_num = rand() % (the_board_ptr->num_col - 1);
		} while (the_board_ptr->game_area[row_num][col_num].ships != none ||
			the_board_ptr->game_area[row_num][col_num + 1].ships != none);
		for (; i < 2; ++i) {
			the_board_ptr->game_area[row_num][col_num + i].ships = destroyer;
		}
	}
}

/*	Function: choose_starting_player
*	Date: 11/08/21
*	Input: int variable of player num
*	Precondition: boards must be generated
*	Postcondition: assigns a value (1 or 2) to player_num and prints out who has been selected
*/
int choose_starting_player(int player_num) {
	player_num = rand() % 2 + 1;
	printf("Player %d has been randomly selected to go first\n", player_num);
	return player_num;
}

/*	Function: check_if_ended
*	Date: 11/08/21
*	Input: pointer to Board
*	Precondition: must be end of turn
*	Postcondition: returns notended or ended
*/
Gamecondition check_if_ended(Board* the_board_ptr) {
	int i = 0, j = 0, shipcells_hit = 0;
	Gamecondition is_end = notended;
	for (; i < the_board_ptr->num_row; ++i) {
		for (j = 0; j < the_board_ptr->num_col; ++j) {
			if (the_board_ptr->game_area[i][j].ships != none && the_board_ptr->game_area[i][j].is_hit == hit) {
				++shipcells_hit;
			}
		}
	}
	if (shipcells_hit == 17) {
		is_end = ended;
	}
	return is_end;
}

/*	Function: bot_shoot
*	Date: 11/08/21
*	Input: pointer to board
*	Precondition: boards are displayed
*	Postcondition: selects random nothit Cell in Board and changes to hit, displays shot message, echos shot message to log file
*/
void bot_shoot(Board* the_board_ptr, FILE* outfile) {
	int i = 0, j = 0;

	do {
		i = rand() % 10;
		j = rand() % 10;
	} while (the_board_ptr->game_area[i][j].is_hit == hit);

	the_board_ptr->game_area[i][j].is_hit = hit;

	printf("Computer selects: %d %d\n",i, j);
	if (the_board_ptr->game_area[i][j].ships == none) {
		printf("%d,%d is a miss!\n", i, j);
		fprintf(outfile, "Player2: %d,%d \"miss\"\n", i, j);
	}
	else {
		printf("%d,%d is a hit!", i, j);
		fprintf(outfile, "Player2: %d,%d \"hit\"", i, j);
		check_if_sunken(the_board_ptr, the_board_ptr->game_area[i][j].ships, outfile);
		printf("\n");
		fprintf(outfile, "\n");
	}
	
}

/*	Function: check_if_sunken
*	Date: 11/08/21
*	Input: pointer to Board and file, ship type (enum)
*	Precondition: a tile with ship must've been hit
*	Postcondition: prints out to console and file which ship has sunk
*/
void check_if_sunken(Board* the_board_ptr, Ship_type ships, FILE* outfile) {
	int i = 0, j = 0, cells_hit = 0;
	switch (ships) {
	case carrier:
		for (; i < the_board_ptr->num_row; ++i) {
			for (j = 0; j < the_board_ptr->num_col; ++j) {
				if (the_board_ptr->game_area[i][j].ships == carrier && the_board_ptr->game_area[i][j].is_hit == hit) {
					++cells_hit;
				}
			}
		}
		if (cells_hit == 5) {
			printf(" Sunk carrier!");
			fprintf(outfile, " Sunk carrier!");
		}
		break;
	case battleship:
		for (; i < the_board_ptr->num_row; ++i) {
			for (j = 0; j < the_board_ptr->num_col; ++j) {
				if (the_board_ptr->game_area[i][j].ships == battleship && the_board_ptr->game_area[i][j].is_hit == hit) {
					++cells_hit;
				}
			}
		}
		if (cells_hit == 4) {
			printf(" Sunk battleship!");
			fprintf(outfile, " Sunk battleship!");
		}
		break;
	case cruiser:
		for (; i < the_board_ptr->num_row; ++i) {
			for (j = 0; j < the_board_ptr->num_col; ++j) {
				if (the_board_ptr->game_area[i][j].ships == cruiser && the_board_ptr->game_area[i][j].is_hit == hit) {
					++cells_hit;
				}
			}
		}
		if (cells_hit == 3) {
			printf(" Sunk cruiser!");
			fprintf(outfile, " Sunk cruiser!");
		}
		break;
	case submarine:
		for (; i < the_board_ptr->num_row; ++i) {
			for (j = 0; j < the_board_ptr->num_col; ++j) {
				if (the_board_ptr->game_area[i][j].ships == submarine && the_board_ptr->game_area[i][j].is_hit == hit) {
					++cells_hit;
				}
			}
		}
		if (cells_hit == 3) {
			printf(" Sunk submarine!");
			fprintf(outfile, " Sunk submarine!");
		}
		break;
	case destroyer:
		for (; i < the_board_ptr->num_row; ++i) {
			for (j = 0; j < the_board_ptr->num_col; ++j) {
				if (the_board_ptr->game_area[i][j].ships == destroyer && the_board_ptr->game_area[i][j].is_hit == hit) {
					++cells_hit;
				}
			}
		}
		if (cells_hit == 2) {
			printf(" Sunk destroyer!");
			fprintf(outfile, " Sunk destroyer!");
		}
		break;
	}
	
}

/*	Function: player_shoot
*	Date: 11/10/21
*	Input: pointer to Board and output ifle
*	Precondition: players turn
*	Postcondition: prompts user for input, shoots cell, prints message to console and file
*/
void player_shoot(Board* the_board_ptr, FILE* outfile) {
	int in_row = 0, in_col = 0;
	do {
		do {
			printf("Enter a target: ");
			scanf("%d%d", &in_row, &in_col);
		} while (in_row < 0 || in_row > 9 || in_col < 0 || in_col > 9);
	} while (the_board_ptr->game_area[in_row][in_col].is_hit == hit);
	system("cls");
	the_board_ptr->game_area[in_row][in_col].is_hit = hit;
	if (the_board_ptr->game_area[in_row][in_col].ships == none) {
		printf("%d,%d is a miss!\n", in_row, in_col);
		fprintf(outfile, "Player1: %d,%d \"miss\"\n", in_row, in_col);
	}
	else {
		printf("%d,%d is a hit!", in_row, in_col);
		fprintf(outfile, "Player1: %d,%d \"hit\"", in_row, in_col);
		check_if_sunken(the_board_ptr, the_board_ptr->game_area[in_row][in_col].ships, outfile);
		printf("\n");
		fprintf(outfile, "\n");
	}
}

/*	Function: calc_print_stats
*	Date: 11/10/21
*	Input: pointer to Board, Stats and file
*	Precondition: game must have ended
*	Postcondition: calculates stats of a player and prints to file
*/
void calc_print_stats(Board* the_board_ptr, Stats* stat_ptr, FILE* outfile) {
	int i = 0, j = 0, hits = 0, misses = 0, shots = 0, hit_miss_ratio = 0;
	for (; i < the_board_ptr->num_row; ++i) {
		for (j = 0; j < the_board_ptr->num_col; ++j) {
			if (the_board_ptr->game_area[i][j].is_hit == hit && the_board_ptr->game_area[i][j].ships != none) {
				stat_ptr->hits += 1;
				stat_ptr->shots += 1;
			}
			else if (the_board_ptr->game_area[i][j].is_hit == hit && the_board_ptr->game_area[i][j].ships == none) {
				stat_ptr->misses += 1;
				stat_ptr->shots += 1;
			}
		}
	}
	stat_ptr->hit_miss_percent = (stat_ptr->hits * 100) / stat_ptr->misses;

	fprintf(outfile, "*** Player%d Stats ***\n", stat_ptr->player_num);
	fprintf(outfile, "Number Hits: %d\n", stat_ptr->hits);
	fprintf(outfile, "Number Misses: %d\n", stat_ptr->misses);
	fprintf(outfile, "Total Shots: %d\n", stat_ptr->shots);
	fprintf(outfile, "Hit/Miss Ratio: %d%%\n\n", stat_ptr->hit_miss_percent);

}