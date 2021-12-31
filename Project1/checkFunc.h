#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include"structs.h"
#include"define.h"
#include "editFunc.h"
#include "sideFunc.h"


/*Checking and scanning functions*/
WinnersList scanTreeInOrder(ActiveTree activePlayersTree, ActiveList* activePlayersList);
void scanTreeInOrderRec(ActiveTreeNode* root, ActiveList* activePlayersList, WinnersList* winnersList);
ActiveListNode* findInActiveList(ActiveList activePlayersList, ActiveListNode* toFind);
void findLowestPossibilities(short sudokuBoard[9][9], Array*** boardArray, int* x, int* y);
bool checkForSingleOption(short sudokuBoard[9][9], Array*** boardArray);
int checkBoardState(short sudokuBoard[9][9], Array*** boardArray, int* x, int* y);
bool checkIfBoardFull(short sudokuBoard[9][9]);
bool checkIfBoardLegal(short sudokuBoard[9][9]);
bool checkIfSquareLegal(short sudokuBoard[9][9], int row, int col);
bool checkIfRowLegal(short sudokuBoard[9][9], int row);
bool checkIfColLegal(short sudokuBoard[9][9], int col);
void checkPossibleDigits(short sudokuBoard[9][9], Cell cell, Array* boardArray);
void checkSquare(short sudokuBoard[9][9], Cell cell, Array* boardArray);
void checkRow(short sudokuBoard[9][9], Cell cell, Array* boardArray);
void checkCol(short sudokuBoard[9][9], Cell cell, Array* boardArray);
int playersCompare(Player player1, Player player2);
int howManyFilledCells(Player player);
int newTreeSize(int size);

