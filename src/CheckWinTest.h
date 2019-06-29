/*Header File*/

#ifndef WinTest
#define WinTest

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GameBoardV2.h"
#include "ChessPieceTypes.h"
#include "ChessPieceHierarchy.h"

int intlen(int x);
int KingMoves(CPL *list);
int AppendKingMoves(CPL *list, int num, int counter, int flag);
int ConvertKingMoves(CPL *list, int counter);
#endif
