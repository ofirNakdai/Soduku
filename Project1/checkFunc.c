#include "checkFunc.h"

/*Checking and scanning functions*/
WinnersList scanTreeInOrder(ActiveTree activePlayersTree, ActiveList* activePlayersList)
{
	WinnersList newList;
	newList = createEmptyWinnersList();
	scanTreeInOrderRec(activePlayersTree.root, activePlayersList, &newList);
	return newList;
}
void scanTreeInOrderRec(ActiveTreeNode* root, ActiveList* activePlayersList, WinnersList* winnersList)
{
	int result = 0;
	ActiveListNode* prev;
	int row = 0, col = 0;
	if (root == NULL)
	{
		return;
	}
	else
	{
		scanTreeInOrderRec(root->left, activePlayersList, winnersList);
		if (root->data != NULL)
		{
			result = oneStage((*(root->data))->data.board.sudokuBoard, (*(root->data))->data.possibilitiesBoard, &row, &col);
			if (result == NOT_FINISH)
			{
				printf("player: %s\n", (*(root->data))->data.playerName);
				printBoard((*(root->data))->data.board.sudokuBoard);
				result = chooseToFill(&((*(root->data))->data), row, col);
			}
			if (result == FINISH_SUCCESS)
			{
				system("CLS");
				printf("SUCCESS\n");
				prev = findInActiveList(*activePlayersList, (*(root->data)));
				transferFromActiveToWinners(activePlayersList, prev, winnersList);
				root->data = NULL;
			}
			else if (result == FINISH_FAILURE)
			{
				system("CLS");
				printf("FAILED!\n");
				prev = findInActiveList(*activePlayersList, (*(root->data)));
				removeActiveNodeFromLocation(activePlayersList, prev);
				root->data = NULL;
			}
		}
		scanTreeInOrderRec(root->right, activePlayersList, winnersList);
	}
}
ActiveListNode* findInActiveList(ActiveList activePlayersList, ActiveListNode* toFind)
{
	ActiveListNode* prev = NULL;
	ActiveListNode* cur = activePlayersList.head;
	while (cur != toFind)
	{
		prev = cur;
		cur = cur->next;
	}
	return prev;
}
void findLowestPossibilities(short sudokuBoard[9][9], Array*** boardArray, int* x, int* y)
{
	int i, j;
	int min = 10;
	if (checkIfBoardFull(sudokuBoard))
	{
		*x = *y = -2;
		return;
	}
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1)
			{
				if (boardArray[i][j]->size < min)
				{
					*x = i;
					*y = j;
					min = boardArray[i][j]->size;
				}
			}
		}
	}
	if (min == 10)
	{
		*x = -1;
		*y = -1;
	}
}
bool checkForSingleOption(short sudokuBoard[9][9], Array*** boardArray)
{
	int i, j;
	Cell currentCell;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (boardArray[i][j] != NULL)
			{
				if (boardArray[i][j]->size == 1)
				{
					currentCell.row = i;
					currentCell.col = j;
					fill(sudokuBoard, boardArray, currentCell, boardArray[i][j]->arr[0]);
					return true;
				}
			}
		}
	}
	return false;
}
int checkBoardState(short sudokuBoard[9][9], Array*** boardArray, int* x, int* y)
{
	if (checkIfBoardFull(sudokuBoard))
	{
		return FINISH_SUCCESS;
	}
	else if (checkIfBoardLegal(sudokuBoard) == false)
	{
		return FINISH_FAILURE;
	}
	else
	{
		findLowestPossibilities(sudokuBoard, boardArray, x, y);
		if (*x == -1 && *y == -1)
		{
			return FINISH_FAILURE;
		}
		if (*x == -2 && *y == -2)
		{
			return FINISH_SUCCESS;
		}
		return NOT_FINISH;
	}
}
bool checkIfBoardFull(short sudokuBoard[9][9])
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1)
			{
				return false;
			}
		}
	}
	return true;
}
bool checkIfBoardLegal(short sudokuBoard[9][9])
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		if (checkIfRowLegal(sudokuBoard, i) == false || checkIfColLegal(sudokuBoard, i) == false)
		{
			return false;
		}
	}
	for (i = 0; i < 9; i += 3)
	{
		for (j = 0; j < 9; j += 3)
		{
			if (checkIfSquareLegal(sudokuBoard, i, j) == false)
			{
				return false;
			}
		}
	}
	return true;
}
bool checkIfSquareLegal(short sudokuBoard[9][9], int row, int col)
{
	int i, j;
	int arr[9] = { 0,0,0,0,0,0,0,0,0 };
	for (i = row; i < row + 3; i++)
	{
		for (j = col; j < col + 3; j++)
		{
			if (sudokuBoard[i][j] != -1)
			{
				arr[((sudokuBoard[i][j]) - 1)]++;
				if (arr[((sudokuBoard[i][j]) - 1)] > 1)
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool checkIfRowLegal(short sudokuBoard[9][9], int row)
{
	int i;
	int arr[9] = { 0,0,0,0,0,0,0,0,0 };
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[row][i] != -1)
		{
			arr[((sudokuBoard[row][i]) - 1)]++;
			if (arr[((sudokuBoard[row][i]) - 1)] > 1)
			{
				return false;
			}
		}
	}
	return true;
}
bool checkIfColLegal(short sudokuBoard[9][9], int col)
{
	int i;
	int arr[9] = { 0,0,0,0,0,0,0,0,0 };
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[i][col] != -1)
		{
			arr[((sudokuBoard[i][col]) - 1)]++;
			if (arr[((sudokuBoard[i][col]) - 1)] > 1)
			{
				return false;
			}
		}
	}
	return true;
}
void checkPossibleDigits(short sudokuBoard[9][9], Cell cell, Array* boardArray)
{
	checkSquare(sudokuBoard, cell, boardArray);
	checkRow(sudokuBoard, cell, boardArray);
	checkCol(sudokuBoard, cell, boardArray);
}
void checkSquare(short sudokuBoard[9][9], Cell cell, Array* boardArray)
{
	int i, j;
	int startRow, startCol;
	startRow = cell.row - (cell.row % 3);
	startCol = cell.col - (cell.col % 3);
	for (i = startRow; i < startRow + 3; i++)
	{
		for (j = startCol; j < startCol + 3; j++)
		{
			if (sudokuBoard[i][j] != -1)
			{
				removeNumFromArr(boardArray, sudokuBoard[i][j]);
			}
		}
	}
}
void checkRow(short sudokuBoard[9][9], Cell cell, Array* boardArray)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[cell.row][i] != -1)
		{
			removeNumFromArr(boardArray, sudokuBoard[cell.row][i]);
		}
	}
}
void checkCol(short sudokuBoard[9][9], Cell cell, Array* boardArray)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (sudokuBoard[i][cell.col] != -1)
		{
			removeNumFromArr(boardArray, sudokuBoard[i][cell.col]);
		}
	}
}
int playersCompare(Player player1, Player player2)
{
	int filledCells1 = 0, filledCells2 = 0;
	int isEqual = 0;
	filledCells1 = howManyFilledCells(player1);
	filledCells2 = howManyFilledCells(player2);
	if (filledCells1 == filledCells2)
	{
		isEqual = strcmp(player1.playerName, player2.playerName);
		if (isEqual < 0)
		{
			return -1;
		}
		else if (isEqual > 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (filledCells1 > filledCells2)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
int howManyFilledCells(Player player)
{
	int i = 0, j = 0;
	int count = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (player.board.sudokuBoard[i][j] != -1)
			{
				count++;
			}
		}
	}
	return count;
}
int newTreeSize(int size)
{
	double log = 0, temp = 0;
	int num = 0;
	log = log2(size + 1);
	num = (int)log;
	temp = log - num;
	if (temp > 0)
	{
		num += 1;
		num = (int)((pow(2, num)) - 1);
	}
	else
	{
		num = (int)((pow(2, num)) - 1);
	}
	return num;
}
