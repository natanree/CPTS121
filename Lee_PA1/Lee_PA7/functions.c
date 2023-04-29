/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/24/21
*	Description: Poker Game 5 card draw ver. (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA7.htm
*/
#include "functions.h"

/*	Function: shuffle
*	Date: 11/24/21
*	Input: deck 2d array
*	Precondition: deck must be initialized
*	Postcondition: shuffles deck
*/
void shuffle(int wDeck[][13]) {
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	// resets deck to zero
	for (; row < 4; ++row) {
		for (column = 0; column < 13; ++column) {
			wDeck[row][column] = 0;
		}
	}

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++) {
		/* choose new random location until unoccupied slot found */
		do {
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/*	Function: deal
*	Date: 11/24/21
*	Input: deck array, face array, suit array
*	Precondition: deck must be shuffled
*	Postcondition: deals out cards in deck
*/
void deal(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* hand_ptr, int hand_size, int draw_size, int player_num) {
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 1;   /* card counter */
	int i = hand_size - draw_size;

	for (; card <= draw_size; card++, ++i) {
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++) {
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++) {
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card) {
					/*if (player_num == 1) {
						printf("%5s of %-8s\n", wFace[column], wSuit[row]);
					}*/
					hand_ptr->cards[i].face_index = column;
					hand_ptr->cards[i].suit_index = row;
				}
			}
		}
	}
	if (player_num == PLAYER1) {
		for (i = 0; i < hand_size; ++i) {
			printf("%d. %5s of %-8s\n", i + 1, wFace[hand_ptr->cards[i].face_index], wSuit[hand_ptr->cards[i].suit_index]);
		}
	}
	for (i = 1; i <= hand_size; ++i) {
		for (row = 0; row <= 3; row++) {
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++) {
				// puts card at bottom of deck
				if (wDeck[row][column] == 1) {
					wDeck[row][column] = 52;
				}
				else {
					wDeck[row][column] -= 1;
				}
			}
		}
	}
}

/*	Function: print_menu
*	Date: 11/24/21
*	Input: n/a
*	Precondition: game just launched/ended
*	Postcondition: prints out menu
*/
void print_menu(void) {
	printf("\t\t\tWelcome to Five Card Draw\n");
	printf("1. Rules\n");
	printf("2. Play Game\n");
	printf("3. Exit\n");
}

/*	Function: print_rules
*	Date: 11/24/21
*	Input: n/a
*	Precondition: player must have chosen rules option
*	Postcondition: prints rules
*/
void print_rules(void) {
	printf("1. This is a two player game, player 1 is you, player 2 is the computer\n");
	printf("2. Both players are given 5 cards\n");
	printf("3. Players can choose to redraw any amount of cards once\n");
	printf("4. Once both players are done redrawing their hands are analyzed and whoever has the higher ranked hand wins\n");
	printf("5. Card suits are all equal\n");
	printf("6. Card faces from lowest to highest are 2,3,4,5,6,7,8,9,10,J,Q,K,A\n");
	printf("7. Hand ranks (highest to lowest)\n");
	printf("\t1. Royal Flush\n");
	printf("\t\tconsists of the highest straight and a flush\n");
	printf("\t2. Straight Flush\n");
	printf("\t\tconsists of any straight and a flush\n");
	printf("\t3. Four of a Kind\n");
	printf("\t\tconsists of four cards with the same face\n");
	printf("\t4. Full House\n");
	printf("\t\tconsists of three of a kind and a pair\n");
	printf("\t\tvalued by face of three of a kind\n");
	printf("\t5. Flush\n");
	printf("\t\tconsists of five cards with the same suit\n");
	printf("\t6. Straight\n");
	printf("\t\tconsists of five cards in order(i.e. 2,3,4,5,6)\n");
	printf("\t\tace can be used as a 1 in straights\n");
	printf("\t\tvalued by last card (i.e. 2,3,4,5,6 would be valued by 6)\n");
	printf("\t7. Three of a Kind\n");
	printf("\t\tconsists of three cards with the same face\n");
	printf("\t8. Two Pair\n");
	printf("\t\tconsists of two pairs\n");
	printf("\t9. Pair\n");
	printf("\t\tconsists of two cards with the same face\n");
	printf("\t10. No Pair / High Card\n");
	printf("\t\tno combination, hand is valued by highest ranking card\n");
	printf("8. If players have the same hand type (i.e. both players have a four of a kind), the combination with the higher ranking card wins\n");
	printf("9. If both players have exact same hand (i.e. same combination with same value), game will end in a tie\n");
}

/*	Function: init_hand
*	Date: 11/24/21
*	Input: ptr to a Hand
*	Precondition: variable of Hand must exist
*	Postcondition: initializes f_index and s_index of Cards in Hand to 0
*/
void init_hand(Hand* hand_ptr) {
	int i = 0;
	for (; i < MAX_HAND_SIZE; ++i) {
		hand_ptr->cards[i].face_index = 0;
		hand_ptr->cards[i].suit_index = 0;
	}
}

/*	Function: ask_for_reroll
*	Date: 11/25/21
*	Input: ptr to a Hand
*	Precondition: cards must have been dealt
*	Postcondition: returns number of cards to be replaced
*/
int ask_for_reroll(Hand* hand_ptr) {
	int num = 0, option = 0, freq[MAX_HAND_SIZE] = { 0 }, i = 0, j = 0;
	Boolean is_invalid = false;
	do {
		printf("How many cards would you like to replace?\n");
		scanf("%d", &num);
	} while (num < 0 || num > 5);
	if (num != 0) {
		do {
			if (is_invalid == false) {
				printf("Which cards would you like to replace?\n");
			}
			else {
				printf("Invalid choice of cards, choose a new set of cards to replace\n");
			}
			is_invalid = false;
			for (i = 0; i < num; ++i) {
				do {
					scanf("%d", &option);
				} while (option < 1 || option > 5);
				freq[option - 1] += 1;
			}
			for (i = 0;i < MAX_HAND_SIZE; ++i) {
				if (freq[i] > 1) {
					is_invalid = true;
				}
			}
		} while (is_invalid == true);
	}
	// shift hand
	for (i = 0; i < MAX_HAND_SIZE; ++i) {
		rec_shift_hand(freq, hand_ptr, i);
	}
	
	return num;
}

/*	Function: rec_shift_hand
*	Date: 11/25/21
*	Input: pointer to frequncy array and Hand
*	Precondition: player chose to replace cards
*	Postcondition: shifts cards in hand, lower index = keep, higher index = replace
*/
void rec_shift_hand(int* freq_ptr, Hand* hand_ptr, int index) {
	int i = 0, temp_face = 0, temp_suit = 0, temp_freq = 0;
	if (*(freq_ptr + index) == 1) {
		*(freq_ptr + index) = 0;
		for (i = index; i < MAX_HAND_SIZE - 1; ++i) {
			temp_suit = hand_ptr->cards[i].suit_index;
			temp_face = hand_ptr->cards[i].face_index;
			temp_freq = *(freq_ptr + i);
			hand_ptr->cards[i].suit_index = hand_ptr->cards[i + 1].suit_index;
			hand_ptr->cards[i].face_index = hand_ptr->cards[i + 1].face_index;
			*(freq_ptr + i) = *(freq_ptr + i + 1);
			hand_ptr->cards[i + 1].suit_index = temp_suit;
			hand_ptr->cards[i + 1].face_index = temp_face;
			*(freq_ptr + i + 1) = temp_freq;
		}
		rec_shift_hand(freq_ptr, hand_ptr, index);
	}
}

/*	Function: hand_value
*	Date: 11/26/21
*	Input: Hand ptr and Face ptr
*	Precondition: players must have given cards
*	Postcondition: returns the hand combination and changes value of high card
*/
Handtype hand_value(Hand* hand_ptr, Face* high_card_ptr) {
	int face_freq[13] = { 0 }, suit_freq[4] = { 0 }, i = 0, pair_count = 0;
	Boolean is_three = false, is_four = false, is_straight = false, is_flush = false;
	Handtype type;
	Face high_count = two;
	
	for (;i < MAX_HAND_SIZE; ++i) {
		face_freq[hand_ptr->cards[i].face_index]++;
		suit_freq[hand_ptr->cards[i].suit_index]++;
	}
	// checks for pairs
	for (i = 0; i < 13; ++i) {
		if (face_freq[i] == 2) {
			++pair_count;
			if (high_count < i) {
				high_count = i;
			}
		}
	}
	// checks for three of a kind
	// full house counts on three of a kind
	// so replacing high count after pairs is fine
	for (i = 0; i < 13; ++i) {
		if (face_freq[i] == 3) {
			is_three = true;
			high_count = i;
			break;
		}
	}
	// checks for four of a kind
	for (i = 0; i < 13; ++i) {
		if (face_freq[i] == 4) {
			is_four = true;
			high_count = i;
			break;
		}
	}
	// checks for A, 2, 3, 4, 5 straight
	if (face_freq[12] == 1 && face_freq[0] == 1 && face_freq[1] == 1 && face_freq[2] == 1 && face_freq[3] == 1) {
		is_straight = true;
		high_count = five;
	}
	else { // checks for every other straight
		for (i = 0; i < 9; ++i) {
			if (face_freq[i] == 1 && face_freq[i + 1] == 1 && face_freq[i + 2] == 1 && face_freq[i + 3] == 1 && face_freq[i + 4] == 1) {
				is_straight = true;
				high_count = i + 4;
			}
		}
	}
	// checks for flush
	for (i = 0; i < 4; ++i) {
		if (suit_freq[i] == 5) {
			is_flush = true;
		}
	}
	if (is_flush == true && is_straight == true && high_count == ace) {
		type = royal_flush;
	}
	else if (is_flush == true && is_straight == true) {
		type = straight_flush;
	}
	else if (is_four == true) {
		type = four_of_a_kind;
	}
	else if (is_three == true && pair_count == 1) {
		type = full_house;
	}
	else if (is_flush == true) {
		type = flush;
		for (i = 0; i < 13; ++i) {
			if (face_freq[i] > 0) {
				high_count = i;
			}
		}
	}
	else if (is_straight == true) {
		type = straight;
	}
	else if (is_three == true) {
		type = three_of_a_kind;
	}
	else if (pair_count == 2) {
		type = two_pair;
	}
	else if (pair_count == 1) {
		type = pair;
	}
	else {
		type = high_card;
		for (i = 0; i < 13; ++i) {
			if (face_freq[i] > 0) {
				high_count = i;
			}
		}
	}

	*high_card_ptr = high_count;

	return type;
}

/*	Function: bot_reroll
*	Date: 11/26/21
*	Input: Hand ptr
*	Precondition: bot must be assigned a hand
*	Postcondition: returns num of cards to be redrew, shifts hand
*/
int bot_reroll(Hand* hand_ptr, Face* high_card_ptr, Handtype* type_ptr) {
	int num = 0, freq[MAX_HAND_SIZE] = { 0 }, i = 0, j = 0, z = 0, x = 0,
		face_freq[13] = { 0 }, suit_freq[4] = { 0 };
	Boolean go_flush = false, go_straight = false;
	
	switch (*type_ptr) {
	// royal flush-straight is good(really low chance), no action needed
	case three_of_a_kind: // tries for full house
		num = 1;
		for (;i < MAX_HAND_SIZE; ++i) {
			if (hand_ptr->cards[i].face_index != *high_card_ptr) {
				freq[i]++;
				break;
			}
		}
		break;
	case two_pair: // tries for full house
		num = 1;
		for (; i < MAX_HAND_SIZE; ++i) {
			face_freq[hand_ptr->cards[i].face_index]++;
		}
		// finds which is stand alone card
		for (i = 0;i < 13; ++i) {
			if (face_freq[i] == 1) {
				break;
			}
		}
		// finds where stand alone card is in hand
		for (; j < MAX_HAND_SIZE; ++j) {
			if (hand_ptr->cards[j].face_index == i) {
				freq[j]++;
				break;
			}
		}
		break;
	case pair: // if one off tries for flush/straight (flush has priority) else two pair/full house
		for (; i < MAX_HAND_SIZE; ++i) {
			suit_freq[hand_ptr->cards[i].suit_index]++;
			face_freq[hand_ptr->cards[i].face_index]++;
		}
		// determines if hand has 4 card flush
		for (i = 0; i < 4; ++i) {
			if (suit_freq[i] == 4) {
				go_flush = true;
				break;
			}
		}
		switch (go_flush) {
		case true:
			num = 1;
			// find stand alone card
			for (i = 0; i < 4; ++i) {
				if (suit_freq[i] == 1) {
					break;
				}
			}
			// find where stand alone card is
			for (; j < MAX_HAND_SIZE; ++j) {
				if (hand_ptr->cards[j].suit_index == i) {
					freq[j]++;
					break;
				}
			}
			break;
		case false:
			// determines if hand has 4 card straight
			// checks A, 2, 3, 4
			if (face_freq[12] > 0 && face_freq[0] > 0 && face_freq[1] > 0 && face_freq[2] > 0) {
				go_straight = true;
			}
			else {
				for (i = 0; i < 10; ++i) {
					if (face_freq[i] > 0 && face_freq[i + 1] > 0 && face_freq[i + 2] > 0 && face_freq[i + 3] > 0) {
						go_straight = true;
						break;
					}
				}
			}
			switch (go_straight) {
			case true:
				num = 1;
				// find stand alone card
				for (i = 0; i < 13; ++i) {
					if (face_freq[i] > 1) {
						break;
					}
				}
				for (;j < MAX_HAND_SIZE; ++j) {
					if (hand_ptr->cards[j].face_index == i) {
						freq[j]++;
						break;
					}
				}
				break;
			case false:
				num = 2;
				// tries for two pair/full house by redrawing two
				for (i = 0; i < 13; ++i) {
					if (face_freq[i] == 1) {
						break;
					}
				}
				for (j = 0; j < 13; ++j) {
					if (face_freq[j] == 1 && j != i) {
						break;
					}
				}
				for (; z < MAX_HAND_SIZE; z++) {
					if (hand_ptr->cards[z].face_index == i) {
						freq[z]++;
						break;
					}
				}
				for (; z < MAX_HAND_SIZE; z++) {
					if (hand_ptr->cards[z].face_index == j) {
						freq[z]++;
						break;
					}
				}
				break;
			}
			break;
		}
		break;
	case high_card:
		for (; i < MAX_HAND_SIZE; ++i) {
			suit_freq[hand_ptr->cards[i].suit_index]++;
			face_freq[hand_ptr->cards[i].face_index]++;
		}
		// determines if hand has 4 card flush
		for (i = 0; i < 4; ++i) {
			if (suit_freq[i] == 4) {
				go_flush = true;
				break;
			}
		}
		switch (go_flush) {
		case true:
			num = 1;
			// find stand alone card
			for (i = 0; i < 4; ++i) {
				if (suit_freq[i] == 1) {
					break;
				}
			}
			// find where stand alone card is
			for (; j < MAX_HAND_SIZE; ++j) {
				if (hand_ptr->cards[j].suit_index == i) {
					freq[j]++;
					break;
				}
			}
			break;
		case false:
			num = 3;
			for (i = 0; i < 13; ++i) {
				if (face_freq[i] == 1) {
					break;
				}
			}
			for (j = 0; j < 13; ++j) {
				if (face_freq[j] == 1 && j != i) {
					break;
				}
			}
			for (z = 0; z < 13; ++z) {
				if (face_freq[z] == 1 && j != z && z != i) {
					break;
				}
			}
			for (x = 0; x < MAX_HAND_SIZE; ++x) {
				if (hand_ptr->cards[x].face_index == i) {
					freq[x]++;
				}
			}
			for (x = 0; x < MAX_HAND_SIZE; ++x) {
				if (hand_ptr->cards[x].face_index == j) {
					freq[x]++;
				}
			}
			for (x = 0; x < MAX_HAND_SIZE; ++x) {
				if (hand_ptr->cards[x].face_index == z) {
					freq[x]++;
				}
			}
		}
		break;
	}

	// shift hand
	for (i = 0; i < MAX_HAND_SIZE; ++i) {
		rec_shift_hand(freq, hand_ptr, i);
	}

	return num;
}

/*	Function: determine_winner
*	Date: 11/27/21
*	Input: ptr to p1 and p2 Handtype and Face(highcard)
*	Precondition: players redraw phase ended
*	Postcondition: prints both players hand and who wins (or a tie)
*/
void determine_winner(Handtype* p1_type_ptr, Handtype* p2_type_ptr, Face* p1_high_card_ptr, 
	Face* p2_high_card_ptr, char* wFace[], char* wSuit[], Hand* p1_hand_ptr, Hand* p2_hand_ptr) {
	int i = 0;
	printf("Player1\t\t\tPlayer2\n");
	for (; i < MAX_HAND_SIZE; ++i) {
		printf("% 5s of % -8s\t% 5s of % -8s\n", 
			wFace[p1_hand_ptr->cards[i].face_index], wSuit[p1_hand_ptr->cards[i].suit_index],
			wFace[p2_hand_ptr->cards[i].face_index], wSuit[p2_hand_ptr->cards[i].suit_index]);
	}
	
	if (*p1_type_ptr < *p2_type_ptr) {
		printf("Player1 Wins!\n");
	}
	else if (*p1_type_ptr > *p2_type_ptr) {
		printf("Player2 Wins!\n");
	}
	else if (*p1_high_card_ptr > *p2_high_card_ptr) {
		printf("Player 1 Wins!\n");
	}
	else if (*p2_high_card_ptr > *p1_high_card_ptr) {
		printf("Player 2 Wins!\n");
	}
	else {
		printf("It is a tie!\n");
	}
}