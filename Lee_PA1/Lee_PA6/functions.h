/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 11/07/21
*	Description: battleship game (player vs computer)
*		https://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA6.htm
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PLAYER_1 0
#define PLAYER_2 1
#define MAX_ROW 10
#define MAX_COL 10

typedef enum hit_status {
	nothit,hit
}Hit_status;

typedef enum ship_type {
	none, destroyer, submarine, cruiser, battleship, carrier
}Ship_type;

typedef enum playertype {
	player = 1, bot
}Playertype;

typedef enum gamecondition {
	ended, notended
}Gamecondition;

typedef struct stats {
	int hits;
	int misses;
	int shots;
	int hit_miss_percent;
	Playertype player_num;
} Stats;

typedef struct cell {
	Hit_status is_hit;
	Ship_type ships;
	int row;
	int col;
}Cell;

typedef struct board {
	Cell game_area[MAX_ROW][MAX_COL];
	Playertype bot_or_player;
	int num_row;
	int num_col;
}Board;

void welcome_screen(void);
void init_stats(Stats* stat, int player_num);
void init_board(Board* the_board_ptr, int player_num);
void print_board(const Board* the_board_ptr);
int choose_placement_method(int choice);
void place_ships(int choice, Board* the_board_ptr);
void place_carrier(Board* the_board_ptr);
void place_battleship(Board* the_board_ptr);
void place_cruiser(Board* the_board_ptr);
void place_submarine(Board* the_board_ptr);
void place_destroyer(Board* the_board_ptr);
void random_carrier(Board* the_board_ptr);
void random_battleship(Board* the_board_ptr);
void random_cruiser(Board* the_board_ptr);
void random_submarine(Board* the_board_ptr);
void random_destroyer(Board* the_board_ptr);
int choose_starting_player(int player_num);
Gamecondition check_if_ended(Board* the_board_ptr);
void bot_shoot(Board* the_board_ptr, FILE* outfile);
void check_if_sunken(Board* the_board_ptr, Ship_type ships, FILE* outfile);
void player_shoot(Board* the_board_ptr, FILE* outfile);
void calc_print_stats(Board* the_board_ptr, Stats* stat_ptr, FILE* outfile);

#endif