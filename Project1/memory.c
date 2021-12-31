#include"memory.h"


void freeBoardArrayCell(Array** boardArrayCell)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		freeArray(boardArrayCell[i]);
	}
	free(boardArrayCell);
}
void freeArray(Array* array)
{
	if (array != NULL)
	{
		free(array->arr);
		free(array);
	}
}
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}