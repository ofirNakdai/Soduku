#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include"structs.h"
#include"checkFunc.h"
#include"editFunc.h"
#include"define.h"
#include"memory.h"



/*Creation functions*/
short* createArr();
void makeEmptyBoard(short board[9][9]);
Array*** CreateEmptyBoardArray();
ActiveList makeActivePlayersList();
CellList createCellList();
Player makeNewPlayer(int playerNum);
char* getPlayerName();
void makeRandomBoard(Player* newPlayer);
ActiveArray createActivePlayersArray(ActiveList list);
ActiveTree makeTreeFromArray(ActiveArray* arr, int size);
ActiveTree buildTree(ActiveListNode** arr, int size);
ActiveTreeNode* buildTreeRec(ActiveListNode** arr, int size);
