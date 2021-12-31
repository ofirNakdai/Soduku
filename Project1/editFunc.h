#pragma once
#include <stdlib.h>
#include <stdio.h>
#include"structs.h"
#include"checkFunc.h"
#include"createFunc.h"
#include "printFunc.h"

/*Editing functions*/
int chooseToFill(Player* player, int row, int col);
void transferFromActiveToWinners(ActiveList* list, ActiveListNode* prev, WinnersList* winnersList);
Cell removeCellFromList(CellList* list, int cellLocation);
void copyBoard(short destination[9][9], short toCopy[9][9]);
void fill(short sudokuBoard[9][9], Array*** boardArray, Cell cell, short num);
void fillCell(short sudokuBoard[9][9], Cell cell, short num);
void updateBoardArray(Array*** boardArray, Cell cell, short sudokuBoard[9][9]);
void updateSquare(Array*** boardArray, Cell cell, short sudokuBoard[9][9]);
void updateRow(Array*** boardArray, Cell cell, short sudokuBoard[9][9]);
void updateCol(Array*** boardArray, Cell cell, short sudokuBoard[9][9]);
void removeNumFromArr(Array* boardArray, short num);
void mergeSort(ActiveListNode** playersArray, int arrSize);
ActiveListNode** merge(ActiveListNode** playersArr1, int arrSize1, ActiveListNode** playersArr2, int arrSize2);
void copyActiveArr(ActiveListNode** destination, ActiveListNode** toCopy, int size);
