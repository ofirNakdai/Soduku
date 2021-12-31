#pragma once
#include <stdlib.h>
#include <stdio.h>
#include"structs.h"

/*Memory functions*/
void freeBoardArray(Array*** boardArray);
void freeBoardArrayCell(Array** boardArrayCell);
void freeArray(Array* array);

void checkMemoryAllocation(void* ptr);
