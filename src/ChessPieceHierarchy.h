/* Header File */

#ifndef STRUCT
#define STRUCT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/*We need to make this similar to the ImageList in the PhotoLab from 22 */

/*This module will defined all the structs
 * we need. (They need to be pointers to structs
 * similar to the 22 PhotoLab). There also needs
 * to be a few functions to handle the structs:
 * 1. Instantiate and initialize all the structs.
 * 2. Delete a player piece struct
 * 3. Delete the main struct (and all "sub-structs")
 * 4. Create a player piece struct
 *   - If a pawn reaches the other side of the board,
	  the player can choose to bring in another piece.
	  It could be a second queen, or a third rook. In 
	  this case, the length of the Piece Type needs
	  to be increased.
 * 5. Sets the information for the player piece struct
 *	  for a "default game." 
 *	 - Basically hardcoding the currentloc values for each
	  piece to match the default board setup.
 * There could be other functions. Just add some if you think of
 * something and put it above :) */
 

typedef struct ChessPieceList CPL;
typedef struct ChessPiece CP;

struct ChessPieceList {
		CP *First;
		CP *Last;
		CP *CurrentPiece;
		CP *TargetPiece;
		CP *WhiteKing;
		CP *BlackKing;
		
		/*This is used to tell whether or not
		 this piece is the current piece or
		 the target piece. This will default to 0
		 so when calling the chess piece lookup
		 functions, call them on the current location
		 first, and then the target location for this to work.*/
		
		int selected_piece;
		
		/*This is used to keep track of the total number of pieces*/
		
		int num_pieces;
        char turn;

        int *WKingMoves;
        int *BKingMoves;
		
};

struct ChessPiece {
		char type[10];
		char currentloc[2];
		char targetloc[2];
		char side;
		int moves;
		/*int life;*/
		
		CP *Next;
		CP *Prev;
		CPL *List;
};

/*Creates Chess Piece List*/
CPL *CreateChessPieceList(void);

void DeleteChessPieceList(CPL *list);

CP *CreateChessPiece(void);

void DeleteChessPiece(CP *ChessPiece);

void AppendChessPiece(
	CPL *list, char *type, char *currentloc, char side, int moves);

CPL *DefaultChessGame(void);

void AppendPawn(CPL *list, char *currentloc, char side, int moves);

void AppendRook(CPL *list, char *currentloc, char side, int moves);

void AppendKnight(CPL *list, char *currentloc, char side, int moves);

void AppendBishop(CPL *list, char *currentloc, char side, int moves);

void AppendKing(CPL *list, char *currentloc, char side, int moves);

void AppendQueen(CPL *list, char *currentloc, char side, int moves);

int ListDebug(CPL *list);
#endif
