#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



/*PossibilitesArray - Contains an array of the possible values of a cell from the board.*/
typedef struct _Array
{
	short* arr;
	unsigned short size;
} Array;

/*Cell - Contains the row and colllumn of a cell.*/
typedef struct _Cell
{
	unsigned short row;
	unsigned short col;
} Cell;

/*CellListNode - A listNode with cell as data.*/
typedef struct _CellListNode
{
	Cell data;
	struct _CellListNode* next;
} CellListNode;

/*CellList - Contains the first and last node of a cell list.*/
typedef struct _CellList
{
	CellListNode* head;
	CellListNode* tail;
} CellList;

/*RandomBoard - Contains 9x9 shorts that represents a random sudoku board.*/
typedef struct _RandomBoard
{
	short sudokuBoard[9][9];
} RandomBoard;

/*Player - Contains a player's name, random board and and the possibilities board for the board.*/
typedef struct _Player
{
	char* playerName;
	RandomBoard board;
	Array*** possibilitiesBoard;
} Player;

/*ActivePlayersListNode - A list node with Player as data that represents the active players that are still playing the game.*/
typedef struct _ActivePlayersListNode
{
	Player data;
	struct _ActivePlayersListNode* next;
}ActiveListNode;

/*ActivePlayersList - Contains the first and last node of an active players list.*/
typedef struct _ActivePlayersList
{
	ActiveListNode* head;
	ActiveListNode* tail;
} ActiveList;

/*ActivePlayersArray - Contains an array of pointers to players that are still active.*/
typedef struct _ActivePlayersArray
{
	ActiveListNode** activePlayers;
} ActiveArray;

/*WinningsPlayersList - Contains the first and last node of a winning players list.*/
typedef struct _WinningPlayersList
{
	ActiveListNode* head;
	ActiveListNode* tail;
} WinnersList;

/*ActivePlayersTreeNode - A tree node with Player as data that represents the active players that are stil playing the game.*/
typedef struct _ActivePlayersTreeNode
{
	ActiveListNode** data;
	struct _ActivePlayersTreeNode* left;
	struct _ActivePlayersTreeNode* right;
}ActiveTreeNode;

/*ActivePlayersTree - Contains the root of the tree that represents the active players that are still playing the game.*/
typedef struct _ActivePlayersTree
{
	ActiveTreeNode* root;
}ActiveTree;

/*ActivePlayersList functions*/
ActiveList createEmptyActiveList();
ActiveListNode* createNewActiveListNode(Player data, ActiveListNode* next);
void insertNodeToStartActiveList(ActiveList* list, ActiveListNode* newHead);
void insertDataToStartActiveList(ActiveList* list, Player data);
void insertNodeToEndActiveList(ActiveList* list, ActiveListNode* newTail);
void insertDataToEndActiveList(ActiveList* list, Player data);
void removeActiveNodeFromLocation(ActiveList* list, ActiveListNode* prev);
int activeListLength(ActiveList list);
int activeListLengthRec(ActiveListNode* head);
bool isActiveListEmpty(ActiveList list);
void freeActiveList(ActiveList* list);
void freeActiveListRec(ActiveListNode* head);

/*WinnersPlayersList functions*/
WinnersList createEmptyWinnersList();
void insertNodeToEndWinnersList(WinnersList* list, ActiveListNode* newTail);
void insertDataToEndWinnersList(WinnersList* list, Player data);
bool isWinnersListEmpty(WinnersList list);
void freeWinnersList(WinnersList* list);

/*CellList functions*/
CellList createEmptyCellList();
CellListNode* createNewCellListNode(Cell data, CellListNode* next);
void insertNodeToStartCellList(CellList* list, CellListNode* newHead);
void insertDataToStartCellList(CellList* list, Cell data);
void insertNodeToEndCellList(CellList* list, CellListNode* newTail);
void insertDataToEndCellList(CellList* list, Cell data);
void removeCellNodeFromLocation(CellList* list, CellListNode* previousNode);
int cellListLength(CellList list);
int cellListLengthRec(CellListNode* head);
bool isCellListEmpty(CellList list);
void freeCellList(CellList* list);
void freeCellListRec(CellListNode* head);

/*ActiveTree functions*/
ActiveTreeNode* createNewTreeNode(ActiveListNode** data, ActiveTreeNode* left, ActiveTreeNode* right);
void printTreeInOrder(ActiveTree tr);
void printTreeInOrderRec(ActiveTreeNode* root);
bool isActiveTreeEmpty(ActiveTree tr);
void freeActiveTree(ActiveTree tr);
void freeActiveTreeRec(ActiveTreeNode* root);

void freePlayer(Player player);
void freeBoardArray(Array*** boardArray);