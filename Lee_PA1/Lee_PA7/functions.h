/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/24/21
*	Description: Poker Game 5 card draw ver. (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA7.htm
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HAND_SIZE 5
#define PRINT_RULES 1
#define PLAY_GAME 2
#define EXIT 3
#define PLAYER1 1
#define PLAYER2 2

typedef enum boolean {
	false, true
}Boolean;

typedef enum handtype {
	royal_flush, straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pair, pair, high_card
} Handtype;

typedef enum face {
	two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
} Face;

typedef struct card {
	int face_index;
	int suit_index;
}Card;

typedef struct hand {
	Card cards[MAX_HAND_SIZE];
}Hand;

void shuffle(int wDeck[][13]);
void deal(int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* hand_ptr, int hand_size, int draw_size, int player_num);
void print_menu(void);
void print_rules(void);
void init_hand(Hand* hand_ptr);
int ask_for_reroll(Hand* hand_ptr);
void rec_shift_hand(int* freq_ptr, Hand* hand_ptr, int index);
Handtype hand_value(Hand* hand_ptr, Face* high_card_ptr);
int bot_reroll(Hand* hand_ptr, Face* high_card_ptr, Handtype* type_ptr);
void determine_winner(Handtype* p1_type_ptr, Handtype* p2_type_tpr, Face* p1_high_card_ptr, 
	Face* p2_high_card_ptr, char* wFace[], char* wSuit[], Hand* p1_hand_ptr, Hand* p2_hand_ptr);
#endif