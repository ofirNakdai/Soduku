#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdlib.h>
#include <Windows.h>
#include"define.h"
#include"structs.h"

/*Printing functions*/
void printBoard(short board[][9]);
void printPossibilities(Player* player, int row, int col);
void printWinnersList(WinnersList winners);
