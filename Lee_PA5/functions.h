/*	Author: Yu Chung Lee
*	Class: Cpts 121 Section 5
*	Date Created: 10/17/21
*	Description: Game of yahtzee, roll 5 die, choose one of 13 point calculations once, repeat 12 more times, highest score at end of game wins
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define PRINT_RULES 1
#define PLAY_GAME 2
#define EXIT 3

void print_menu(void);

int get_menu_option(void);

void menu_action(int menu_option);

void print_rules(void);

#endif