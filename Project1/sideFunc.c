#include "sideFunc.h"

Array*** possibleDigits(short sudokuBoard[9][9])
{
	Array*** boardArray = NULL;
	Cell currentCell;
	int i, j;
	boardArray = CreateEmptyBoardArray();
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1)
			{
				currentCell.row = i;
				currentCell.col = j;
				checkPossibleDigits(sudokuBoard, currentCell, boardArray[i][j]);
			}
			else
			{
				freeArray(boardArray[i][j]);
				boardArray[i][j] = NULL;
			}
		}
	}
	return boardArray;
}
int oneStage(short sudokuBoard[9][9], Array*** boardArray, int* x, int* y)
{
	int i, j;
	bool found = true;

	while (found == true)
	{
		found = checkForSingleOption(sudokuBoard, boardArray);
	}
	int res = checkBoardState(sudokuBoard, boardArray, x, y), res2 = FINISH_FAILURE;

	if (res != NOT_FINISH)
		return res;

	int size = boardArray[*x][*y]->size;
	for (int i = 0; i < size && res != res2; i++)
	{
		if ((boardArray[*x][*y]->arr)[i] >= 1 && (boardArray[*x][*y]->arr)[i] <= 9)
			res2 = res;
	}

	if (res2 == res)
		return res;
	else
		return res2;
}
