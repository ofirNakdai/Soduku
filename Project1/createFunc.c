#include "createFunc.h"


short* createArr()
{
	short* arr = NULL;
	int i, j;
	arr = (short*)malloc(sizeof(short) * 9);
	for (i = 0; i < 9; i++)
	{
		arr[i] = (i + 1);
	}
	checkMemoryAllocation(arr);
	return arr;
}
void makeEmptyBoard(short board[9][9])
{
	int i = 0, j = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			board[i][j] = -1;
		}
	}
}
Array*** CreateEmptyBoardArray()
{
	Array*** boardArray = NULL;
	int i, j;
	boardArray = (Array***)malloc(sizeof(Array**) * 9);
	checkMemoryAllocation(boardArray);
	for (i = 0; i < 9; i++)
	{
		boardArray[i] = (Array**)malloc(sizeof(Array*) * 9);
		checkMemoryAllocation(boardArray[i]);
	}
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			boardArray[i][j] = (Array*)malloc(sizeof(Array) * 1);
			checkMemoryAllocation(boardArray[i][j]);
			boardArray[i][j]->arr = createArr();
			boardArray[i][j]->size = 9;
		}
	}
	return boardArray;
}
CellList createCellList()
{
	int i = 0, j = 0;
	CellList newList;
	Cell newCell;
	newList = createEmptyCellList();
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			newCell.row = i;
			newCell.col = j;
			insertDataToEndCellList(&newList, newCell);
		}
	}
	return newList;
}
ActiveList makeActivePlayersList()
{
	int i = 0;
	int listLength = 2;
	ActiveList newList;
	Player newPlayer;
	printf("Please enter the numbers of players:\n");
	scanf("%d", &listLength);
	getchar();
	newList = createEmptyActiveList();
	for (i = 0; i < listLength; i++)
	{
		newPlayer = makeNewPlayer(i + 1);
		insertDataToEndActiveList(&newList, newPlayer);
	}
	return newList;
}
Player makeNewPlayer(int playerNum)
{
	Player newPlayer;
	printf("insert name of player %d :\n", playerNum);
	newPlayer.playerName = getPlayerName(playerNum);
	makeRandomBoard(&newPlayer);
	return newPlayer;
}
char* getPlayerName()
{
	int phySize = 1, logSize = 0;
	char c = '\n';
	char* name = NULL;
	c = getchar();
	name = (char*)malloc(sizeof(char));
	checkMemoryAllocation(name);
	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			name = (char*)realloc(name, sizeof(char) * phySize);
			checkMemoryAllocation(name);
		}
		name[logSize] = c;
		logSize++;
		c = getchar();
	}
	name = (char*)realloc(name, sizeof(char) * (logSize + 1));
	checkMemoryAllocation(name);
	name[logSize] = '\0';
	return name;
}
void makeRandomBoard(Player* newPlayer)
{
	int i = 0;
	int startingCells = 0, numberInList = 0, indexInArr = 0, listLength = 81, cellRange = 0, cellValue = 0;
	CellList newList;
	Cell removedCell;
	short newBoard[9][9];
	Array*** newPossibilitiesBoard = NULL;
	newList = createCellList();
	makeEmptyBoard(newBoard);
	newPossibilitiesBoard = possibleDigits(newBoard);
	startingCells = (rand() % 20) + 1;


	for (i = 0; i < startingCells; i++)
	{
		numberInList = (rand() % listLength) + 1;
		listLength--;
		removedCell = removeCellFromList(&newList, numberInList);
		cellRange = newPossibilitiesBoard[removedCell.row][removedCell.col]->size;
		indexInArr = (rand() % (cellRange - 1));
		cellValue = newPossibilitiesBoard[removedCell.row][removedCell.col]->arr[indexInArr];
		fill(newBoard, newPossibilitiesBoard, removedCell, cellValue);
	}

	copyBoard(newPlayer->board.sudokuBoard, newBoard);
	newPlayer->possibilitiesBoard = newPossibilitiesBoard;
	freeCellList(&newList);
}
ActiveArray createActivePlayersArray(ActiveList list)
{
	int i = 0;
	int listLength = 0;
	ActiveArray playersArr;
	ActiveListNode* curr;
	listLength = activeListLength(list);
	playersArr.activePlayers = (ActiveListNode**)malloc(sizeof(ActiveListNode*) * listLength);
	checkMemoryAllocation(playersArr.activePlayers);
	curr = list.head;
	for (i = 0; i < listLength; i++)
	{
		playersArr.activePlayers[i] = curr;
		curr = curr->next;
	}
	return playersArr;
}
ActiveTree makeTreeFromArray(ActiveArray* arr, int size)
{
	int i = 0;
	int newSize = 0;
	ActiveTree newTree;
	newSize = newTreeSize(size);
	if (newSize != size)
	{
		(*arr).activePlayers = (ActiveListNode**)realloc((*arr).activePlayers, sizeof(ActiveListNode*) * newSize);
	}
	for (i = size; i < newSize; i++)
	{
		(*arr).activePlayers[i] = NULL;
	}
	newTree = buildTree((*arr).activePlayers, newSize);
	return newTree;
}
ActiveTree buildTree(ActiveListNode** arr, int size)
{
	ActiveTree newTree;
	newTree.root = buildTreeRec(arr, size);
	return newTree;
}
ActiveTreeNode* buildTreeRec(ActiveListNode** arr, int size)
{
	int middle = 0;
	ActiveTreeNode* left = NULL;
	ActiveTreeNode* right = NULL;
	if (size == 0)
	{
		return NULL;
	}
	else
	{
		middle = (size / 2);
		left = buildTreeRec(arr, middle);
		right = buildTreeRec(arr + middle + 1, size - middle - 1);

		if (arr[middle] != NULL)
		{
			return createNewTreeNode(&(arr[middle]), left, right);
		}
		else
		{
			return createNewTreeNode(NULL, left, right);
		}
	}
}
