#include "GameBoardV2.h"

/*The menu can be the main module for now*/
	
	
CPL *StartUp(char side, int interactiveboard)
{	
  CPL *list = NULL;

  if (interactiveboard) list = CreativeBoard();
  else list = create_board();

  if (side == 'W') list->turn = side;
  else if (side == 'B') list->turn = side;

  update_board(list);

  //KingMoves(list);
	
  return list;
}


int *PositionLookUp(char *position)
{
 /* The position is given to this function (i.e. A4).
  * The second element of the char array is converted
  * into an int (ASCII value is given so -48 is needed).
  * The first element is checked in a switch case statement.
  * For each element, the corresponding row or column is
  * determined based on the position given. Since A8 is in
  * the top right of the board, subtracting 8 is necessary
  * to get the correct value. For the switch case statement,
  * the letters are just converted to their respected column. */
	
	int x,y;
	int *indices = malloc(sizeof(int) * 2);

	y = (int)position[1] - 48;

	for (x = 0; x < 9; x++)
		if ((8 - y) == x) indices[0] = x;

	switch(position[0])
	{
		case 'A':
			indices[1] = 0;
			break;
		case 'B':
			indices[1] = 1;
			break;
		case 'C':
			indices[1] = 2;
			break;
		case 'D':
			indices[1] = 3;
			break;
		case 'E':
			indices[1] = 4;
			break;
		case 'F':
			indices[1] = 5;
			break;
		case 'G':
			indices[1] = 6;
			break;
		case 'H':
			indices[1] = 7;
			break;
	}
	return indices;
}

int HandleMoves(CPL *list, char *CurrentLocation, char *TargetLocation)
{	
    //This is used if the target position is empty
    //May change process later

    /*Converting board positions to indices*/
    int *curr_indices = PositionLookUp(CurrentLocation);
    int *target_indices = PositionLookUp(TargetLocation);


	/*If this returns 0, that means the spot they selected
	 * does not have a piece there */

	if (!ChessLocator(CurrentLocation, list)) 
	{
		list->selected_piece = 0;
        printf("There is not a piece at %s!\n", CurrentLocation);
		return 0;
	} 
    
    if (list->turn != list->CurrentPiece->side) return 0;

	/*If there is a piece there, it will make the
	 *TargetPiece pointer in the list point to that
	 *piece. Otherwise, the pointer will be NULL*/

	if (IsTherePieceHere(list, target_indices)) ChessLocator(TargetLocation, list);
    else list->selected_piece = 0;

	/*Now calling Legal Move*/

	/*If the move is legal, this executes*/
	if (LegalMove(list, curr_indices, target_indices))
	{
        //Need to add check/checkmate features
		//The move is legal, so change the board position of the current piece
        if (list->TargetPiece != NULL)
        {
            strcpy(list->CurrentPiece->currentloc, list->TargetPiece->currentloc);
		    DeleteChessPiece(list->TargetPiece);
        }
        else
            strcpy(list->CurrentPiece->currentloc, TargetLocation);

        list->CurrentPiece->moves++;
        list->TargetPiece = NULL;
        list->CurrentPiece = NULL;
		 return 1;
	}	

    else
    {
        printf("Test\n");
        list->TargetPiece = NULL;
        list->CurrentPiece = NULL;
        return 0;
    }
}

CPL *CreativeBoard()
{
	/* This function allows the creation of a custom board.
	 * This can be used for testing other aspects of the game
	 * and its pieces. The user is asked to pick a side and
	 * piece before placement. Afterwards, the program will ask
	 * for a position on the board. Based on their input, the correct
	 * piece will be placed in the wanted position. The chess
	 * piece possibilties had to be hard coded since the strings
	 * are extremely high maintenance in C -- it was just easier.*/

	CPL *list = NULL;
	list = CreateChessPieceList();

	char piece[10];
	char color;
	char flag;
	char position[2];
	int wking = 0;
	int bking = 0;

	printf("\n");
	printf("Interactive Board Menu\n");
	printf("\n");

	while(1)
	{
		while(1)
		{
			printf("Choose a side before placing a piece (W or B): ");
			scanf(" %c", &color);

			if (color == 'W' || color == 'B')
				break;
			
			printf("That's not a side!\n");
		}

		while(1)
		{
			printf("Choose a game piece \n");
			printf("(Pawn, Knight, Bishop, Rook, Queen, King): ");
			scanf(" %s", piece);
			
			if ((strcmp(piece, "Pawn") == 0) || (strcmp(piece, "Knight") == 0)
					|| (strcmp(piece, "Bishop") == 0) || (strcmp(piece, "Rook") == 0)
					|| (strcmp(piece, "Queen") == 0) || (strcmp(piece, "King") == 0))
						break;

			printf("That's not a valid game piece!\n");
		}
			
		while(1)
		{
			printf("Choose a spot on the board (A4, B3, H7, etc.): ");
			scanf(" %s", position);
			
			if (position[0] >=65 && position[0] <= 72)
				if (position[1] >=49 && position[1] <= 57)
					break;
				
			printf("That's not a valid position!\n");
		}
			
		if (strcmp(piece, "Pawn") == 0)
			AppendPawn(list, position, color, 0);
		else if (strcmp(piece, "Rook") == 0)
			AppendRook(list, position, color, 0);
		else if (strcmp(piece, "Knight") == 0)
			AppendKnight(list, position, color, 0);
		else if (strcmp(piece, "Bishop") == 0)
		 	AppendBishop(list, position, color, 0);
		else if (strcmp(piece, "King") == 0)
		{
			if ((color == 'W' && wking == 1) || (color == 'B' && bking == 1))
				printf("You can only have one King!\n");
			else
			{
				if (color == 'W' && wking == 0)
				{
					AppendKing(list, position, color, 0);
					wking = 1;
				}
				if (color == 'B' && bking == 0)
				{
					AppendKing(list, position, color, 0);
					bking = 1;
				}
			}
		}
		else if (strcmp(piece, "Queen") == 0)
			AppendQueen(list, position, color, 0);
		else exit(10);

		printf("Would you like to place another piece? (Y or N): ");
		scanf(" %c", &flag);

		if (flag == 'N' || flag == 'n') break;
	}
	return list;
}

CPL *create_board()
{
	CPL *list = DefaultChessGame();
	return list;
}

void update_board(CPL *list)
{
  char *custom_game_board[8][8] = {
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""}
  };
 
 CP *curr = NULL;

 curr = list->First;

 while (curr != NULL)
 {
	 int *indices = PositionLookUp(curr->currentloc);
	 //printf("Piece Type: %s\n", curr->type);
	 //printf("Color of Piece: %c\n", curr->side);
	 if (curr->side == 'W')
		{
			if (curr->type[0] == 'P') custom_game_board[indices[0]][indices[1]] = "WP\0";
			else if (curr->type[0] == 'R') custom_game_board[indices[0]][indices[1]] = "WR\0";
			else if (curr->type[0] == 'B') custom_game_board[indices[0]][indices[1]] = "WB\0";
			else if (curr->type[0] == 'K')
			 {
				if (curr->type[1] == 'n') custom_game_board[indices[0]][indices[1]] = "WN\0";
				else if (curr->type[1] == 'i') custom_game_board[indices[0]][indices[1]] = "WK\0";
				else exit(10);
			 }
			else if (curr->type[0] == 'Q') custom_game_board[indices[0]][indices[1]] = "WQ\0";
			else exit(10);
		}
	 else if (curr->side == 'B')
		{
			if (curr->type[0] == 'P') custom_game_board[indices[0]][indices[1]] = "BP\0";
			else if (curr->type[0] == 'R') custom_game_board[indices[0]][indices[1]] = "BR\0";
			else if (curr->type[0] == 'B') custom_game_board[indices[0]][indices[1]] = "BB\0";
			else if (curr->type[0] == 'K')
			 {
				if (curr->type[1] == 'n') custom_game_board[indices[0]][indices[1]] = "BN\0";
				else if (curr->type[1] == 'i') custom_game_board[indices[0]][indices[1]] = "BK\0";
				else exit(10);
			 }
			else if (curr->type[0] == 'Q') custom_game_board[indices[0]][indices[1]] = "BQ\0";
			else exit(10);
		}
		else exit(10);

	 curr = curr->Next;
	}
	
  if (list->turn == 'W') print_board_white(custom_game_board);
  if (list->turn == 'B') print_board_black(custom_game_board);
}

void print_board_white(char *game_board[8][8])
{
	/*This is one way to print the board. The formatting of how the
   *board looks can always be changed. This is a good start for now*/
  int i, j = 0;
  int k = 8;

  printf("        *** Chess ***\n");
  printf("%d ", k);
  k -= 1;

  for (i = 0; i < 8; i++)
  {
    printf("|");
    for (j= 0; j < 8; j++)
    {
      if (strcmp(game_board[i][j],"") != 0) printf("%s|", game_board[i][j]);
      else printf("  |");
    }
    printf("\n");
    if (i < 7)
    {
      printf("%d ",k);
      k -= 1;
    }
  }
  printf("    A  B  C  D  E  F  G  H\n");
}

void print_board_black(char *game_board[8][8])
{
	/*This is one way to print the board. The formatting of how the
   *board looks can always be changed. This is a good start for now*/
	int i, j = 0;
  int k = 1;

  printf("        *** Chess ***\n");
  printf("%d ", k);
  k += 1;

  for (i = 7; i >= 0; i--)
	{
    printf("|");
//    for (j= o; j < 8; j++)
    for (j = 7; j >= 0; j--)
    {
     if (strcmp(game_board[i][j],"") != 0) printf("%s|", game_board[i][j]);
     else printf("  |");
    }
    printf("\n");
    if (i > 0)
    {
			printf("%d ",k);
      k += 1;
    }
  }
  printf("    H  G  F  E  D  C  B  A\n");
}
