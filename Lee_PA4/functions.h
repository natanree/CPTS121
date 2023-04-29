/*	Author: Yu Chung Lee
*	Class: Cpts 121 Lab Section 5
*	Date Created: 10/03/21
*	Description: Game of craps
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISPLAY_RULES 1
#define INPUT_BALANCE 2
#define PLAY_GAME 3
#define EXIT_GAME 4

int roll_die(void);

int calculate_sum_dice(int die1, int die2);

int is_win_loss_or_point(int sum_dice);

int is_point_loss_or_neither(int sum_dice, int point_value);

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

void print_game_rules(void);

double get_bank_balance(void);

int main_menu(void);

double get_wager_amount(void);

void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);

double check_if_bank_balance_zero(double bank_balance);

#endif