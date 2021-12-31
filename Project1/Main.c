#include "Main.h"

/* NAMES:  Omer Greental, Ofir Nakdai
*  ID:       318382827  ,  318382827
*/
void initializeGame(ActiveList* activePlayersList, ActiveArray* activePlayersArray, ActiveTree* activePlayersTree)
{
	int arraySize = 0;
	ActiveList lst;
	ActiveArray arr;
	ActiveTree tree;
	srand(1, 2, 3, 4, 5);
	lst = makeActivePlayersList();
	arr = createActivePlayersArray(lst);
	arraySize = activeListLength(lst);
	mergeSort(arr.activePlayers, arraySize);
	tree = makeTreeFromArray(&arr, arraySize);


	(*(activePlayersList)) = lst;
	(*(activePlayersArray)) = arr;
	(*(activePlayersTree)) = tree;
}

void gameSequence(ActiveList* activePlayersList, ActiveTree* activePlayersTree)
{
	WinnersList winners;
	winners = scanTreeInOrder(*activePlayersTree, activePlayersList);
	printWinnersList(winners);
	freeWinnersList(&winners);
}

void freeAll(ActiveList* activePlayersList, ActiveArray* activePlayersArray, ActiveTree* activePlayersTree)
{
	free(activePlayersArray->activePlayers);
	freeActiveList(activePlayersList);
	freeActiveTree(*activePlayersTree);
}


void main()
{
	int arraySize = 0;
	ActiveList activePlayers;
	ActiveArray activePlayersArr;
	ActiveTree activePlayersTree;
	initializeGame(&activePlayers, &activePlayersArr, &activePlayersTree);

	

	gameSequence(&activePlayers, &activePlayersTree);
	freeAll(&activePlayers, &activePlayersArr, &activePlayersTree);
}