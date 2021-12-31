#include "structs.h"

/*ActivePlayersList functions*/
ActiveList createEmptyActiveList()
{
	ActiveList newList;
	newList.head = newList.tail = NULL;
	return newList;
}
ActiveListNode* createNewActiveListNode(Player data, ActiveListNode* next)
{
	ActiveListNode* newNode = NULL;
	newNode = (ActiveListNode*)malloc(sizeof(ActiveListNode));
	checkMemoryAllocation(newNode);
	newNode->data = data;
	newNode->next = next;
	return newNode;
}
void insertNodeToStartActiveList(ActiveList* list, ActiveListNode* newHead)
{
	if (isActiveListEmpty(*list))
	{
		list->head = list->tail = newHead;
	}
	else
	{
		newHead->next = list->head;
		list->head = newHead;
	}
}
void insertDataToStartActiveList(ActiveList* list, Player data)
{
	ActiveListNode* newHead = NULL;
	newHead = createNewActiveListNode(data, NULL);
	insertNodeToStartActiveList(list, newHead);
}
void insertNodeToEndActiveList(ActiveList* list, ActiveListNode* newTail)
{
	if (isActiveListEmpty(*list))
	{
		list->head = list->tail = newTail;
	}
	else
	{
		list->tail->next = newTail;
		list->tail = newTail;
	}
}
void insertDataToEndActiveList(ActiveList* list, Player data)
{
	ActiveListNode* newTail = NULL;
	newTail = createNewActiveListNode(data, NULL);
	insertNodeToEndActiveList(list, newTail);
}
void removeActiveNodeFromLocation(ActiveList* list, ActiveListNode* prev)
{
	ActiveListNode* toDelete = NULL;

	if (prev == NULL)
	{
		toDelete = list->head;
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
		toDelete = prev->next;
		if (toDelete->next == NULL)
		{//end of list
			list->tail = prev;
			prev->next = NULL;
		}
		else
		{// mid of list
			prev->next = toDelete->next;
		}
	}

	freePlayer(toDelete->data);
	free(toDelete);
}
int activeListLength(ActiveList list)
{
	if (isActiveListEmpty(list))
	{
		return 0;
	}
	else
	{
		return activeListLengthRec(list.head);
	}
}
int activeListLengthRec(ActiveListNode* head)
{
	if (head->next == NULL)
	{
		return 1;
	}
	else
	{
		return (activeListLengthRec(head->next) + 1);
	}
}
bool isActiveListEmpty(ActiveList list)
{
	if (list.head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void freeActiveList(ActiveList* list)
{
	freeActiveListRec(list->head);
}
void freeActiveListRec(ActiveListNode* head)
{
	if (head == NULL)
	{
		return;
	}
	else
	{
		freeActiveListRec(head->next);
		freePlayer(head->data);
		free(head);
	}
}

/*WinnersPlayersList functions*/
WinnersList createEmptyWinnersList()
{
	WinnersList newList;
	newList.head = newList.tail = NULL;
	return newList;
}
void insertNodeToEndWinnersList(WinnersList* list, ActiveListNode* newTail)
{
	newTail->next = NULL;
	if (isWinnersListEmpty(*list))
	{
		list->head = list->tail = newTail;
	}
	else
	{
		list->tail->next = newTail;
		list->tail = newTail;
	}
}
void insertDataToEndWinnersList(WinnersList* list, Player data)
{
	ActiveListNode* newTail = NULL;
	newTail = createNewActiveListNode(data, NULL);
	insertNodeToEndWinnersList(list, newTail);
}
bool isWinnersListEmpty(WinnersList list)
{
	if (list.head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void freeWinnersList(WinnersList* list)
{
	freeActiveListRec(list->head);
}

/*CellList functions*/
CellList createEmptyCellList()
{
	CellList newList;
	newList.head = newList.tail = NULL;
	return newList;
}
CellListNode* createNewCellListNode(Cell data, CellListNode* next)
{
	CellListNode* newNode = NULL;
	newNode = (CellListNode*)malloc(sizeof(CellListNode));
	checkMemoryAllocation(newNode);
	newNode->data = data;
	newNode->next = next;
	return newNode;
}
void insertNodeToStartCellList(CellList* list, CellListNode* newHead)
{
	if (isCellListEmpty(*list))
	{
		list->head = list->tail = newHead;
	}
	else
	{
		newHead->next = list->head;
		list->head = newHead;
	}
}
void insertDataToStartCellList(CellList* list, Cell data)
{
	CellListNode* newHead = NULL;
	newHead = createNewCellListNode(data, NULL);
	insertNodeToStartCellList(list, newHead);
}
void insertNodeToEndCellList(CellList* list, CellListNode* newTail)
{
	if (isCellListEmpty(*list))
	{
		list->head = list->tail = newTail;
	}
	else
	{
		list->tail->next = newTail;
		list->tail = newTail;
	}
}
void insertDataToEndCellList(CellList* list, Cell data)
{
	CellListNode* newTail = NULL;
	newTail = createNewCellListNode(data, NULL);
	insertNodeToEndCellList(list, newTail);
}
void removeCellNodeFromLocation(CellList* list, CellListNode* prev)
{
	CellListNode* toDelete = NULL;

	if (prev == NULL)
	{
		toDelete = list->head;
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
		toDelete = prev->next;
		if (toDelete->next == NULL)
		{//end of list
			list->tail = prev;
			prev->next = NULL;
		}
		else
		{// mid of list
			prev->next = toDelete->next;
		}
	}
	free(toDelete);
}
int cellListLength(CellList list)
{
	CellListNode* curr = list.head;
	int len = 0;

	while (curr != NULL)
	{
		len++;
		curr = curr->next;
	}

	return len;
}
int cellListLengthRec(CellListNode* head)
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		return (cellListLengthRec(head->next) + 1);
	}
}
bool isCellListEmpty(CellList list)
{
	if (list.head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void freeCellList(CellList* list)
{
	freeCellListRec(list->head);
}
void freeCellListRec(CellListNode* head)
{
	if (head == NULL)
		return;
	else
	{
		freeCellListRec(head->next);
		free(head);
	}
}

/*ActiveTree functions*/
ActiveTreeNode* createNewTreeNode(ActiveListNode** data, ActiveTreeNode* left, ActiveTreeNode* right)
{
	ActiveTreeNode* newNode = NULL;
	newNode = (ActiveTreeNode*)malloc(sizeof(ActiveTreeNode));
	checkMemoryAllocation(newNode);
	newNode->data = data;
	newNode->left = left;
	newNode->right = right;
	return newNode;
}
void printTreeInOrder(ActiveTree tr)
{
	printTreeInOrderRec(tr.root);
	printf("\n");
}
void printTreeInOrderRec(ActiveTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		printTreeInOrderRec(root->left);
		if (root->data == NULL)
		{
			printf("NULL! ");
		}
		else
		{
			printf("%s ", (*(root->data))->data.playerName);
		}
		printTreeInOrderRec(root->right);
	}
}
bool isActiveTreeEmpty(ActiveTree tr)
{
	if (tr.root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void freeActiveTree(ActiveTree tr)
{
	freeActiveTreeRec(tr.root);
}
void freeActiveTreeRec(ActiveTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		freeActiveTreeRec(root->left);
		freeActiveTreeRec(root->right);
		free(root);
	}
}


void freePlayer(Player player)
{
	free(player.playerName);
	freeBoardArray(player.possibilitiesBoard);
}
void freeBoardArray(Array*** boardArray)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		freeBoardArrayCell(boardArray[i]);
	}
	free(boardArray);
}