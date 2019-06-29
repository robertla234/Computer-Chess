#ifndef TYPES
#define TYPES
/*Header File*/

 /*As this is the Chess Piece Types Module,
 * the treestruct hierarchy for the
 * chess peices will be instantiated and
 * initalized in the Chess Piece
 * Hierarchy Module. The separation of these
 * two aspects of the chess pieces allows for
 * modification of this module if needed with
 * little to no effect on the hierarchy module.

 * This module should be relatively complete (not counting
 * the implementation of the hierarchy module). The open
 * space feature can already be determined from the
 * functions below. Legal moves and determining
 * whether or not a piece is in check will be
 * in a different module.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChessPieceHierarchy.h"

/*Used for finding the chess piece given the board position*/
int ChessLocator(char *CurrLocation, CPL *list);

/*Dealing with all the chess rules*/
int LegalMove(CPL *list, int *Current, int *Target);
int IsTherePieceHere(CPL *list, int *indices);
char *IndicesToPosition(int *indices);
int PawnMove(CPL *list, int *Current, int *Target);
int KingMove(CPL *list, int *Current, int *Target);
int QueenMove(CPL *list, int *Current, int *Target);
int KnightMove(CPL *list, int *Current, int *Target);
int RookMove(CPL *list, int *Current, int *Target);
int BishopMove(CPL *list, int *Current, int *Target);
int PlayerPawnPromotion(CPL *list, int *Current, int *Target);
int EnPassant(CPL *list, int *Current, int *Target);
int Castling(CPL *list, int *Current, int *Target);
#endif
