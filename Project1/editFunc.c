#include "editFunc.h"


int chooseToFill(Player* player, int row, int col)
{
	int result = NOT_FINISH;
	while (result == NOT_FINISH)
	{
		printPossibilities(player, row, col);
		result = oneStage((*(player)).board.sudokuBoard, (*(player)).possibilitiesBoard, &row, &col);
	}
	return result;
}
void transferFromActiveToWinners(ActiveList* list, ActiveListNode* prev, WinnersList* winnersList)
{
	ActiveListNode* toTransfer = NULL;

	if (prev == NULL)
	{
		toTransfer = list->head;
		if (list->head != list->tail)
		{//head of list
			list->head = list->head->next;
		}
		else
		{//one object
			list->head = list->tail = NULL;
		}
	}
	else
	{
		toTransfer = prev->next;
		if (toTransfer->next == NULL)
		{//end of list
			list->tail = prev;
			prev->next = NULL;
		}
		else
		{// mid of list
			prev->next = toTransfer->next;
		}
	}
	insertNodeToEndWinnersList(winnersList, toTransfer);
}
Cell removeCellFromList(CellList* list, int cellLocation)
{
	int i = 0;
	Cell cellValue;
	CellListNode* curr, * prev;

	prev = NULL;
	curr = list->head;

	for (int i = 1; i < cellLocation; i++)
	{
		prev = curr;
		curr = curr->next;
	}

	cellValue.col = curr->data.col;
	cellValue.row = curr->data.row;

	removeCellNodeFromLocation(list, prev);
	return cellValue;
}
void copyBoard(short destination[9][9], short toCopy[9][9])
{
	int i = 0, j = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			destination[i][j] = toCopy[i][j];
		}
	}
}
void fill(short sudokuBoard[9][9], Array*** boardArray, Cell cell, short num)
{
	fillCell(sudokuBoard, cell, num);
	updateBoardArray(boardArray, cell, sudokuBoard);
}
void fillCell(short sudokuBoard[9][9], Cell cell, short num)
{
	sudokuBoard[cell.row][cell.col] = num;
}
void updateBoardArray(Array*** boardArray, Cell cell, short sudokuBoard[9][9])
{
	freeArray(boardArray[cell.row][cell.col]);
	boardArray[cell.row][cell.col] = NULL;
	updateSquare(boardArray, cell, sudokuBoard);
	updateRow(boardArray, cell, sudokuBoard);
	updateCol(boardArray, cell, sudokuBoard);
}
void updateSquare(Array*** boardArray, Cell cell, short sudokuBoard[9][9])
{
	int i, j;
	int startRow, startCol;
	startRow = cell.row - (cell.row % 3);
	startCol = cell.col - (cell.col % 3);
	for (i = startRow; i < startRow + 3; i++)
	{
		for (j = startCol; j < startCol + 3; j++)
		{
			if (sudokuBoard[i][j] == -1)
			{
				removeNumFromArr(boardArray[i][j], sudokuBoard[cell.row][cell.col]);
			}
		}
	}
}
void updateRow(Array*** boardArray, Cell cell, short sudokuBoard[9][9])
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[cell.row][i] == -1)
		{
			removeNumFromArr(boardArray[cell.row][i], sudokuBoard[cell.row][cell.col]);
		}
	}
}
void updateCol(Array*** boardArray, Cell cell, short sudokuBoard[9][9])
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[i][cell.col] == -1)
		{
			removeNumFromArr(boardArray[i][cell.col], sudokuBoard[cell.row][cell.col]);
		}
	}
}
void removeNumFromArr(Array* boardArray, short num)
{
	int i, j;
	int check = boardArray->size;
	if (boardArray->size > 1)
	{
		for (i = 0; i < boardArray->size; i++)
		{
			if (boardArray->arr[i] == num)
			{
				for (j = i; j < boardArray->size; j++)
				{
					boardArray->arr[j] = boardArray->arr[j + 1];
				}
				boardArray->size -= 1;
				break;
			}
		}
	}
	else
	{
		if (boardArray->arr[0] == num)
		{
			boardArray->size = 10;
		}
		else if (check > boardArray->size)
		{
			boardArray->arr = (short*)realloc(boardArray->arr, sizeof(short) * boardArray->size);
			checkMemoryAllocation(boardArray->arr);
		}
	}
}
void mergeSort(ActiveListNode** playersArray, int arrSize)
{
	ActiveListNode** mergedArray = NULL;
	if (arrSize <= 1)
	{
		return;
	}
	else
	{
		mergeSort(playersArray, (arrSize / 2));
		mergeSort(playersArray + (arrSize / 2), arrSize - (arrSize / 2));
		mergedArray = merge(playersArray, (arrSize / 2), playersArray + (arrSize / 2), arrSize - (arrSize / 2));
		copyActiveArr(playersArray, mergedArray, arrSize);
		free(mergedArray);
	}
}
ActiveListNode** merge(ActiveListNode** playersArr1, int arrSize1, ActiveListNode** playersArr2, int arrSize2)
{
	int i = 0;
	int count1 = 0, count2 = 0;
	int cmpResult = -2;
	ActiveListNode** mergedArray = NULL;
	mergedArray = (ActiveListNode**)malloc(sizeof(ActiveListNode*) * (arrSize1 + arrSize2));
	checkMemoryAllocation(mergedArray);

	for (i = 0; (count1 < arrSize1 && count2 < arrSize2); i++)
	{
		cmpResult = playersCompare(playersArr1[count1]->data, playersArr2[count2]->data);
		if (cmpResult == 1)
		{
			mergedArray[i] = playersArr2[count2];
			count2++;
		}
		else
		{
			mergedArray[i] = playersArr1[count1];
			count1++;
		}
	}
	while (count1 < arrSize1)
	{
		mergedArray[i] = playersArr1[count1];
		count1++;
		i++;
	}
	while (count2 < arrSize2)
	{
		mergedArray[i] = playersArr2[count2];
		count2++;
		i++;
	}
	return mergedArray;
}
void copyActiveArr(ActiveListNode** destination, ActiveListNode** toCopy, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		destination[i] = toCopy[i];
	}
}
