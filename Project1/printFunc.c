#include"printFunc.h"

void printBoard(short board[][9])
{
	int i, j;
	printf("     ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
	for (i = 0; i <= 8; i++)
	{
		printf("%2d  ", i);
	}
	for (j = 0; j <= 8; j++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
		printf("\n    +");
		for (i = 0; i <= 8; i++)
		{
			if (j % 3 == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
				printf("---+");
			}
			else
			{
				if (i % 3 == 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), REGULAR);
					printf("---");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
					printf("+");
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), REGULAR);
					printf("---+");
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
		printf("\n%2d  ", j);
		printf("|");
		for (i = 0; i <= 8; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
			if (board[j][i] != -1)
			{
				printf("%2d", board[j][i]);
			}
			else
			{
				printf("  ");
			}
			if (i % 3 == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
				printf(" |");
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), REGULAR);
				printf(" |");
			}
		}
	}
	printf("\n    +");
	for (i = 0; i <= 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), HIGHLIGHT);
		printf("---+");
	}

	putchar('\n');
}
void printPossibilities(Player* player, int row, int col)
{
	int i = 0;
	int size = 0;
	int choice = 0;
	Cell cell;
	cell.row = row;
	cell.col = col;
	if ((*(player)).possibilitiesBoard == NULL)
	{
		printf("yeah baby!\n");
		return;
	}
	size = (*(player)).possibilitiesBoard[row][col]->size;
	printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", row, col);

	for (i = 1; i <= size; i++)
	{
		printf("%d. %d\n", i, (*(player)).possibilitiesBoard[row][col]->arr[i - 1]);
	}
	while (choice < 1 || choice > size)
	{
		scanf("%d", &choice);
		if (choice < 1 || choice > size)
		{
			printf("invalid number, try aagain: \n");
		}
	}

	fill((*(player)).board.sudokuBoard, (*(player)).possibilitiesBoard, cell, (*(player)).possibilitiesBoard[row][col]->arr[choice - 1]);
	putchar('\n');
	printf("player: %s\n", (*(player)).playerName);
	printBoard((*(player)).board.sudokuBoard);
}
void printWinnersList(WinnersList winners)
{
	ActiveListNode* curr = winners.head;
	system("CLS");
	if (curr == NULL)
	{
		puts("No Winners!");
		return;
	}

	while (curr != NULL)
	{
		printf("WINNERS:\n");
		printf("Player Name: %s\n", curr->data.playerName);
		printBoard(curr->data.board.sudokuBoard);
		putchar('\n');
		curr = curr->next;
	}
}
