/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/24/21
*	Description: Poker Game 5 card draw ver. (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA7.htm
*/
#include "functions.h"

int main(void) {


	/* initialize suit array */
	const char* suit[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	/* initalize deck array */
	int deck[4][13] = { 0 };

	int main_menu_option = 0, reroll_num = 0, bot_reroll_num = 0;
	Hand p1_hand, p2_hand;
	Face p1_high_card, p2_high_card;
	Handtype p1_type, p2_type;
	init_hand(&p1_hand);
	init_hand(&p2_hand);
	srand((unsigned int)time(NULL)); /* seed random-number generator */

	do {
		do {
			print_menu();
			scanf("%d", &main_menu_option);
			system("cls");
		} while (main_menu_option < 1 || main_menu_option > 3);

		switch (main_menu_option) {
		case PRINT_RULES:
			print_rules();
			system("pause");
			system("cls");
			break;
		case PLAY_GAME:
			shuffle(deck);
			printf("Player1:\n");
			deal(deck, face, suit, &p1_hand, MAX_HAND_SIZE, 5, PLAYER1);
			deal(deck, face, suit, &p2_hand, MAX_HAND_SIZE, 5, PLAYER2);
			reroll_num = ask_for_reroll(&p1_hand);
			system("cls");
			if (reroll_num != 0) { // if player chooses to redraw cards
				system("cls");
				printf("Player 1 New Hand: \n");
				deal(deck, face, suit, &p1_hand, MAX_HAND_SIZE, reroll_num, PLAYER1);
				system("pause");
				system("cls");
			}
			p1_type = hand_value(&p1_hand, &p1_high_card); // determines p1 hand value
			p2_type = hand_value(&p2_hand, &p2_high_card); // determines p2 hand value
			bot_reroll_num = bot_reroll(&p2_hand, &p2_high_card, &p2_type); // gets num of cards to redraw
			deal(deck, face, suit, &p2_hand, MAX_HAND_SIZE, bot_reroll_num, PLAYER2); // redraws
			p2_type = hand_value(&p2_hand, &p2_high_card); // reevaluates hand
			determine_winner(&p1_type, &p2_type, &p1_high_card, &p2_high_card, face, suit, &p1_hand, &p2_hand); // prints both hands and winner

			system("pause");
			system("cls");
			break;
		case EXIT:
			printf("Thank you for playing!\n");
			break;
		}

	} while (main_menu_option != EXIT);
	return 0;
}