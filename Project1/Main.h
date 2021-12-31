#pragma once
#include <stdlib.h>
#include <stdio.h>
#include"structs.h"
#include"checkFunc.h"
#include"editFunc.h"
#include"createFunc.h"
#include"printFunc.h"
#include"memory.h"
#include"sideFunc.h"

/*Main functions*/
void initializeGame(ActiveList* activePlayersList, ActiveArray* activePlayersArray, ActiveTree* activePlayersTree);
void gameSequence(ActiveList* activePlayersList, ActiveTree* activePlayersTree);
void freeAll(ActiveList* activePlayersList, ActiveArray* activePlayersArray, ActiveTree* activePlayersTree);
