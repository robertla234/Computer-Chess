#include "ChessPieceHierarchy.h"

/* Create a new chess piece entry */
CP *CreateChessPiece(void)
{
    CP *ChessPiece = (CP *)malloc(sizeof(CP));

	ChessPiece->Next = NULL;
	ChessPiece->Prev = NULL;
	ChessPiece->List = NULL;

	char type[10];
	char currentloc[3];
	char targetloc[3];
	char side = '\0';
	int moves = 0;

	ChessPiece->moves = moves;
	ChessPiece->side = side;
	
	memset(ChessPiece->type, '\0', sizeof(type));
	memset(ChessPiece->currentloc, '\0', sizeof(currentloc));
	memset(ChessPiece->targetloc, '\0', sizeof(targetloc));
	/*memset(ChessPiece->side, 0, 1);*/

    return ChessPiece;
}

/* Create a new chess piece list */
CPL *CreateChessPieceList(void)
{
    CPL *ChessPieceList = (CPL *)malloc(sizeof(CPL));

    ChessPieceList->First = NULL;
    ChessPieceList->Last = NULL;
    ChessPieceList->CurrentPiece = NULL;
    ChessPieceList->TargetPiece = NULL;
    ChessPieceList->WhiteKing = NULL;
    ChessPieceList->BlackKing = NULL;
	
    ChessPieceList->num_pieces = 0;
	ChessPieceList->selected_piece = 0;
    ChessPieceList->turn = '\0';

    ChessPieceList->WKingMoves = malloc(sizeof(int)*100);
    ChessPieceList->BKingMoves = malloc(sizeof(int)*100);

    return ChessPieceList;
}

/*Adds a chess piece to the list */

void AppendChessPiece(CPL *list, char *type, char *currentloc, char side, int moves)
{
	CP *ChessPiece = CreateChessPiece();
	ChessPiece->List = list;
	ChessPiece->Next =  NULL;
	
	strcpy(ChessPiece->type, type);
	strcpy(ChessPiece->currentloc, currentloc);

	ChessPiece->side = side;
	ChessPiece->moves = moves;

	/*strcpy(ChessPiece->side, side);*/
	
	if (list->Last)
	{
		ChessPiece->Prev = list->Last;
		list->Last->Next = ChessPiece;
		list->Last = ChessPiece;
	}
	else
	{
		ChessPiece->Prev = NULL;
		list->First = ChessPiece;
		list->Last = ChessPiece;
	}
	list->num_pieces++;

	if (strcmp(type, "King") == 0)
	{
		if (side == 'W') list->WhiteKing = ChessPiece;
		if (side == 'B') list->BlackKing = ChessPiece;
	}
}

/*These functions are all separate for the purpose of pawn
promotion. It allows us to call one of these functions based
on the piece that the user wants (and that is allowed) */

void AppendPawn(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "Pawn", currentloc, side, moves);
}

void AppendRook(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "Rook", currentloc, side, moves);
}

void AppendKnight(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "Knight", currentloc, side, moves);
}

void AppendBishop(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "Bishop", currentloc, side, moves);
}

void AppendKing(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "King", currentloc, side, moves);
}

void AppendQueen(CPL *list, char *currentloc, char side, int moves)
{
	AppendChessPiece(list, "Queen", currentloc, side, moves);
}

/*If a default game is selected, this function will run to put
all the pieces on the board in their correct positions */

CPL *DefaultChessGame(void)
{
	CPL *l = NULL;
	l = CreateChessPieceList();
	
	/*This is the white side*/
	
	AppendPawn(l, "A2\0", 'W', 0);
	AppendPawn(l, "B2\0", 'W', 0);
	AppendPawn(l, "C2\0", 'W', 0);
	AppendPawn(l, "D2\0", 'W', 0);
	AppendPawn(l, "E2\0", 'W', 0);
	AppendPawn(l, "F2\0", 'W', 0);
	AppendPawn(l, "G2\0", 'W', 0);
	AppendPawn(l, "H2\0", 'W', 0);
	AppendRook(l, "A1\0", 'W', 0);
	AppendRook(l, "H1\0", 'W', 0);
	AppendKnight(l, "B1\0", 'W', 0);
	AppendKnight(l, "G1\0", 'W', 0);
	AppendBishop(l, "C1\0", 'W', 0);
	AppendBishop(l, "F1\0", 'W', 0);
	AppendKing(l, "E1\0", 'W', 0);
	AppendQueen(l, "D1\0", 'W', 0);
	
	/*This is the black side*/
	
	AppendPawn(l, "A7\0", 'B', 0);
	AppendPawn(l, "B7\0", 'B', 0);
	AppendPawn(l, "C7\0", 'B', 0);
	AppendPawn(l, "D7\0", 'B', 0);
	AppendPawn(l, "E7\0", 'B', 0);
	AppendPawn(l, "F7\0", 'B', 0);
	AppendPawn(l, "G7\0", 'B', 0);
	AppendPawn(l, "H7\0", 'B', 0);
	AppendRook(l, "A8\0", 'B', 0);
	AppendRook(l, "H8\0", 'B', 0);
	AppendKnight(l, "B8\0", 'B', 0);
	AppendKnight(l, "G8\0", 'B', 0);
	AppendBishop(l, "C8\0", 'B', 0);
	AppendBishop(l, "F8\0", 'B', 0);
	AppendKing(l, "E8\0", 'B', 0);
	AppendQueen(l, "D8\0", 'B', 0);

return l;
}

/*Deletes the list and frees memory */

void DeleteChessPieceList(CPL *list)
{
	CP *curr, *next;
	
	assert(list);
	curr = list->First;
	while(curr)
	{
		next = curr->Next;
		DeleteChessPiece(curr);
		curr = next;
	}
    free(list->WKingMoves);
    free(list->BKingMoves);
	free(list);
}

/*Deletes the chess piece and frees its memory */

void DeleteChessPiece(CP *ChessPiece)
{
	assert(ChessPiece);
	
	if (ChessPiece->Next) ChessPiece->Next->Prev = ChessPiece->Prev;
	if (ChessPiece->Prev) ChessPiece->Prev->Next = ChessPiece->Next;

	ChessPiece->Next = NULL;
	ChessPiece->Prev = NULL;
	ChessPiece->List = NULL;
	
 memset(ChessPiece->type, '\0', sizeof(ChessPiece->type));
 memset(ChessPiece->currentloc, '\0', sizeof(ChessPiece->currentloc));
 memset(ChessPiece->targetloc, '\0', sizeof(ChessPiece->targetloc));

	ChessPiece->moves = 0;	
	ChessPiece->side = '\0';
	
	/*memset(ChessPiece->side, 0, 1);*/
	
	free(ChessPiece);
}

/*This is just used to make sure everything works*/
int ListDebug(CPL *list)
{
	CP *curr = NULL;
	CP *prev = NULL;
	CP *next = NULL;
	
	curr = list->First;
	
	while (curr != NULL) 
	{
		printf("Board Position: %s\n", curr->currentloc);
		printf("Piece Type: %s\n", curr->type);
		printf("Color of Piece: %c\n", curr->side);
		next = curr->Next;
		prev = curr;
		curr = next;
	}
	return 0;
}

