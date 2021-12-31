#pragma once
#include <stdlib.h>
#include <stdio.h>
#include"structs.h"
#include"checkFunc.h"
#include"editFunc.h"
#include"createFunc.h"

/*Side functions*/
Array*** possibleDigits(short sudokuBoard[9][9]);
int oneStage(short sudokuBoard[9][9], Array*** possibilities, int* x, int* y);
