/* Header File */


 /*This module still needs to be reworked. The menu features 
 * have been added to a separate module. The main function
 * will be called from there. I decided to send the
 * 2D Char Arrays directly in the function as this module should be the
 * only one needing them. Saving boards and the integration of chess pieces
 * is currently underway. Error checking has not been implemented yet
 * for user input (i.e. pieces and positions that don't exist*/

#ifndef GameBoardV2
#define GameBoardV2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChessPieceHierarchy.h"
#include "ChessPieceTypes.h"
#include "CheckWinTest.h"

CPL *StartUp(char side, int interactiveboard);
int *PositionLookUp(char *position);
int HandleMoves(CPL *list, char *CurrentLocation, char *TargetLocation);
CPL *CreativeBoard();
CPL *create_board();
void update_board(CPL *list);
void print_board_white(char *game_board[8][8]);
void print_board_black(char *game_board[8][8]);

#endif 
