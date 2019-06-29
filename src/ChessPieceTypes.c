#include "ChessPieceTypes.h"

/*
int main()
{
 * The gameboard will give the two char arrays below
   *A pawn is used in this example at A4

   *We need to use N for knight (not KN)

   *This main can be used for debugging purposes
   *This will ultimately be "disabled" as a different
   *module will call the needed functions

   *You can change the PositionInfo and Position
   *to whatever you need to test stuff

    char Position[] = "A4";

    ChessLocator(Position);

}
*/

/* ChessLocator needs to be called first (twice -- one for current and 
   one for target) in GameBoard.c -- this will establish the current
   piece and targetpiece pointers. Then, we need to call the LegalMove 
   function in GameBoard.c */

  /*If this returns 1, call the update board function */
int LegalMove(CPL *list, int *Current, int *Target)
{
    int Legal = 0;
    

    if (strcmp(list->CurrentPiece->type, "Pawn") == 0)
		Legal = PawnMove(list, Current, Target);
    else if (strcmp(list->CurrentPiece->type, "Rook") == 0)
		Legal = RookMove(list, Current, Target);
    else if (strcmp(list->CurrentPiece->type, "Bishop") == 0)
		Legal = BishopMove(list, Current, Target);
    else if (strcmp(list->CurrentPiece->type, "Knight") == 0)
		Legal = KnightMove(list, Current, Target);
    else if (strcmp(list->CurrentPiece->type, "Queen") == 0)
		Legal = QueenMove(list, Current, Target);
    else if (strcmp(list->CurrentPiece->type, "King") == 0)
	    Legal = KingMove(list, Current, Target);
    else exit(20);
	
    if (Legal == 1) return 1;
    return 0;
}


int ChessLocator(char *CurrLocation, CPL *list)
{
  /*Since we are using a double linked list, I need to
    loop through every struct of that piece type and 
	check its current location for a match */
	
  /*This will return the piece type (or NULL if there is
	no piece at the location). This function also points
	to the current piece and the target piece. This will allow
	you to access all the data for both pieces (if there is a
	target piece).
	*/

	CP *curr = NULL;
	CP *prev = NULL;
	CP *next = NULL;
	
	curr = list->First;
	
	while(curr != NULL)
	{
		if (strcmp(CurrLocation, curr->currentloc) == 0)
		{
			/*This switches between the current and target pieces.
			 * Put the "current" piece first, then the "target" piece
			 * for this to work correctly.*/
			 
			if (curr->List->selected_piece == 0) 
			{
				curr->List->CurrentPiece = curr;
				curr->List->selected_piece = 1;
				return 1;
			}
			else if (curr->List->selected_piece == 1) 
			{
				curr->List->TargetPiece = curr;
				curr->List->selected_piece = 0;
				return 1;
			}
			else exit(15);
		}
		else 
		{	
		next = curr->Next;
		prev = curr;
		curr = next;
		}
	}
	return 0;
}

/*Add IsTherePieceHere function here
 * Needs to convert indices to board
 * positon (i.e. [0][0] to A8)
 * and then iterate through the 
 * chess piece list to see if any
 * piece is in that position*/

char *IndicesToPosition(int *indices)
{
    char *position = malloc(sizeof(position) * 3);

    position[2] = '\0';
    
    position[1] = 8 - indices[0] + 48;
    
    position[0] = indices[1] + 65;
    
    return position;
}
   
int IsTherePieceHere(CPL *list, int *indices)
{
    char *position = IndicesToPosition(indices);
 
    CP *curr = NULL;
    
    curr = list->First;
    
    while (curr != NULL)
    {
        if (strcmp(curr->currentloc, position) == 0) 
        {
            if (curr->moves == 99) return 0;
            else return 1;
	    }
        curr = curr->Next;
    }
    return 0;
}


/*Add the PawnMove function here */

/*This will return 1 if the target location is
 * a legal move from the current location. If
 * it returns 0, it is not legal. This function
 * will be called again, with the opposing king being
 * the target location. If this function returns 2,
 * the king is in check */

int RookMove(CPL *list, int *Current, int *Target) {
    /*
    int *Current = PositionLookUp(list->CurrentPiece->currentloc);
    int *Target = PositionLookUp(list->TargetPiece->currentloc);
    */
    int SpotCheck[2];
    //array PlaceHolder[2] = {0, 0};
    //Check for non-directly up-down or side moves

	if (list->TargetPiece != NULL)
    {
        if (list->CurrentPiece->side == list->TargetPiece->side) return 0;
    }

    if (Current[0] != Target[0] && Current[1] != Target[1]) return 0;
	
    //For Vertical movements
    if (Current[1] == Target[1]){
	int i = Current[0];
	 while ((i >= 0) && (i <= 7)){
        if (i == Target[0]) /*Scenario for when check reaches the target loc*/
            return 1;
	    if (i != Current[0])
		{
		    SpotCheck[0] = i;
		    SpotCheck[1] = Current[1];
		    if (IsTherePieceHere(list, SpotCheck)){
			list->TargetPiece = NULL;
			list->CurrentPiece = NULL;
			return 0;
		    }
	    }	
	    if (Current[0] < Target[0]) i++;
	    if (Current[0] > Target[0]) i--;
	}    	
     }

    //For Side movements
    if (Current[0] == Target[0]){
    	int i = Current[1];
    	while ((i >= 0) && (i <= 7)){
        if (i == Target[1]) //Scenario for when check reaches the target loc
            return 1;		
	    if (i != Current[1]){
		SpotCheck[0] = Current[0];
		SpotCheck[1] = i;
		if (IsTherePieceHere(list, SpotCheck)){
			list->TargetPiece = NULL;
			list->CurrentPiece = NULL;
			return 0;
	    	}
	    }	
	    if (Current[1] < Target[1]) i++;
	    if (Current[1] > Target[1]) i--;
        }
    }
    return 0;
}


int BishopMove(CPL *list, int *Current, int *Target) {
    /*
    int *Current = PositionLookUp(list->CurrentPiece->currentloc);
    int *Target = PositionLookUp(list->TargetPiece->currentloc);
    */
    int SpotCheck[2];
    //Check for directly up-down or side moves

    if (list->TargetPiece != NULL)
    {
        if (list->CurrentPiece->side == list->TargetPiece->side) return 0;
    }

    if (Current[0] == Target[0] || Current[1] == Target[1]){
        return 0;
    }

    //Check for Target Loc NOT in diagonal
    int DiagonalCheck = 0;
    int it, jt;
    for (it = Current[0], jt = Current[1]; it <= 7 && jt <= 7; it++, jt++)
        if (Target[0] == it && Target[1] == jt) DiagonalCheck = 1;
    for (it = Current[0], jt = Current[1]; it >= 0 && jt >= 0 && DiagonalCheck < 1; it--, jt--)
        if (Target[0] == it && Target[1] == jt) DiagonalCheck = 1;
    for (it = Current[0], jt = Current[1]; it <= 7 && jt >= 0 && DiagonalCheck < 1; it++, jt--)
        if (Target[0] == it && Target[1] == jt) DiagonalCheck = 1;
    for (it = Current[0], jt = Current[1]; it >= 0 && jt <= 7 && DiagonalCheck < 1; it--, jt++)
        if (Target[0] == it && Target[1] == jt) DiagonalCheck = 1;

    if (!DiagonalCheck)  return 0;
    
    //For Diagonal movements
	int i = Current[0];
	int j = Current[1];
	while( (j >= 0) && (j <= 7) && (i >= 0) && (i <= 7)){
		if (i == Target[0] && j == Target[1]) {
		    return 1;	
		}
		
		if (i != Current[0] && j != Current[1]){
			SpotCheck[0] = i;
			SpotCheck[1] = j;
			if (IsTherePieceHere(list, SpotCheck)){
				list->TargetPiece = NULL;
				list->CurrentPiece = NULL;
				return 0;}
		}
	
		if (Current[0]<Target[0]) i++;
		if (Current[0]>Target[0]) i--;
		if (Current[1]<Target[1]) j++;
		if (Current[1]>Target[1]) j--;
	}
    return 0;
}

int QueenMove(CPL *list, int *Current, int *Target) {
    if (RookMove(list, Current, Target) || BishopMove(list, Current, Target)) return 1;
    return 0;
}

int KnightMove(CPL *list, int *Current, int *Target) {
        /**Check for directly up-down or side moves**/

        if (list->TargetPiece != NULL)
        {
            if (list->CurrentPiece->side == list->TargetPiece->side) return 0;
        }

        if (Current[0] == Target[0] || Current[1] == Target[1]){
                    return 0;
        }

        int xn2 = Current[0] - 2;
        int xn1 = Current[0] - 1;
        int xp1 = Current[0] + 1;
        int xp2 = Current[0] + 2;                            
        int yn2 = Current[1] - 2;
        int yn1 = Current[1] - 1;
        int yp1 = Current[1] + 1;
        int yp2 = Current[1] + 2;
                                            
        if (Target[0] == xn2) {
            if (Target[1] == yn1) return 1;
            else if (Target[1] == yp1) return 1;
        }
        else if (Target[0] == xn1) {
            if (Target[1] == yn2) return 1;
            else if (Target[1] == yp2) return 1;
        }
        else if (Target[0] == xp1) {
            if (Target[1] == yn2) return 1;
            else if (Target[1] == yp2) return 1;
        }
        else if (Target[0] == xp2) {
            if (Target[1] == yn1) return 1;
            else if (Target[1] == yp1) return 1;
        }                                                                                                                  
        return 0;
}

/*Player Pawn Promotion promotes Pawns to chosen piece*/
int PlayerPawnPromotion(CPL *list, int *Current, int *Target){
    CP *curr = NULL;
    
    char promotionType[10];
    int promotionConditional = 1;

    curr = list->First;

    while(curr != NULL){
        if(strcmp(curr->type,"Pawn") == 0){
            if((int)curr->currentloc[1]-48 == 8 || (int)curr->currentloc[1]-48==1){
                while(promotionConditional == 1){
                    printf("Promotion! Choose what to promote the pawn to! Type unit name: Rook, Bishop, Queen, Knight \n");
                    scanf(" %s",promotionType);
                    printf("\n");
                    if(strcmp(promotionType,"Rook")==0){
                            strcpy(curr->type, promotionType);
                            printf("Promoted to Rook!\n");
                            promotionConditional = 0;
                            return 1;
                    }
                    else if(strcmp(promotionType,"Bishop")==0){
                            strcpy(curr->type, promotionType);
                            printf("Promoted to Bishop\n");
                            promotionConditional = 0;
                            return 1;
                    }
                    else if(strcmp(promotionType,"Queen")==0){
                            strcpy(curr->type, promotionType);
                            ListDebug(list);
                            printf("Promoted to Queen!\n");
                            promotionConditional = 0;
                            return 1;
                    }
                    else if(strcmp(promotionType,"Knight")==0){
                            strcpy(curr->type, promotionType);
                            printf("Promoted to Knight!\n");
                            promotionConditional = 0;
                            return 1;
                    }
                    else{
                            printf("Invalid Promotion.  Try Again\n"); 
                    }                   
                }
            }
        } 
        curr = curr->Next;
    }
    return 0;
}

int InBounds(int *Current) {
    if ((Current[0] >= 0) && (Current[0] <= 7)) 
        if ((Current[1] >= 0) && (Current[1] <= 7))
            return 1;
    return 0;
}

int FindPieceSide(CPL *list, int *Index, char search) {
    char *position = IndicesToPosition(Index);

    CP *curr = list->First;
    while (curr) {
        if (!strcmp(curr->currentloc, position)) {
            if (curr->side == search)
                return 1;
        }
        curr = curr->Next;
    }
    return 0;
}

int FindPieceType(CPL *list, int *Index, char search[10]) {
    char *position = IndicesToPosition(Index);

    CP *curr = list->First;
    while (curr) {
        if (!strcmp(curr->currentloc, position)) {
            if (curr->type == search)
                return 1;
        }
        curr = curr->Next;
    }
    return 0;
}

int FindPieceMoves(CPL *list, int *Index, int search) {
    char *position = IndicesToPosition(Index);

    CP *curr = list->First;
    while (curr) {
        if (!strcmp(curr->currentloc, position)) {
            if (curr->moves == search)
                return 1;
        }
        curr = curr->Next;
    }
    return 0;
}

int PawnMove(CPL *list, int *Current, int *Target) {


    if (list->TargetPiece != NULL)
    {
        if (list->CurrentPiece->side == list->TargetPiece->side) return 0;
            if (PlayerPawnPromotion(list, Current, Target)) return 1;
    }
    
    //if (PlayerPawnPromotion(list, Current, Target)) return 1;

	if (InBounds(Target)) {
	    if (FindPieceSide(list, Current, 'B')) { // If piece is black
		    if (FindPieceMoves(list, Current, 0) && Current[0]+2 == Target[0] && Current[1] == Target[1] && !IsTherePieceHere(list, Target)) {  // If piece hasn't moved and if both spaces 2 down is empty, then move is valid
                Target[0] = Target[0] - 1;
                if (!IsTherePieceHere(list, Target)) 
                    return 1;
                else 
                    return 0;
            }
            else if ((Current[0]+1 == Target[0]) && (Current[1] == Target[1]))  // Move 1 down to empty space
                return 1;
            else if (Current[0]+1 == Target[0] && Current[1]+1 == Target[1] && FindPieceSide(list, Target, 'W'))    // Check if moving diagonal to take opponent piece
                return 1;
            else if (Current[0]+1 == Target[0] && Current[1]-1 == Target[1] && FindPieceSide(list, Target, 'W'))  
                return 1;  
            /*else if (EnPassant(list, Current, Target))
                return 1;*/
            else
            {
                return 0;
            }
		}
		else if (FindPieceSide(list, Current, 'W')) { // If piece is white
		    if (FindPieceMoves(list, Current, 0) && Current[0]-2 == Target[0] && Current[1] == Target[1] && !IsTherePieceHere(list, Target)) {  // If piece hasn't moved and if both spaces 2 up is empty, then move is valid
                Target[0] = Target[0] + 1;
                if (!IsTherePieceHere(list, Target)) 
                    return 1;
                else
                    return 0;
            }
            else if (Current[0]-1 == Target[0] && Current[1] == Target[1])   // Move 1 up to empty space
                return 1;
            else if (Current[0]-1 == Target[0] && Current[1]+1 == Target[1] && FindPieceSide(list, Target, 'B'))    // Check if moving diagonal to take opponent piece
                return 1;
            else if (Current[0]-1 == Target[0] && Current[1]-1 == Target[1] && FindPieceSide(list, Target, 'B')) 
                return 1;
            /*else if (EnPassant(list, Current, Target))
                return 1;*/
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;               
}

int KingMove(CPL *list, int *Current, int *Target) { 

    if (list->TargetPiece != NULL)
    {
        if (list->CurrentPiece->side == list->TargetPiece->side) return 0;
    }

    if (InBounds(Target)) {
        if (((Target[0] >= Current[0]-1 && Target[0] <= Current[0]+1) || (Target[1] >= Current[1]-1 && Target[1] <= Current[1]+1))) {
            if (!IsTherePieceHere(list, Target)) {
                return 1;
            }
        }
        else if (((Target[0] >= Current[0]-1 && Target[0] <= Current[0]+1) || (Target[1] >= Current[1]-1 && Target[1] <= Current[1]+1))) {
            if (FindPieceSide(list, Target, list->CurrentPiece->side))       
                return 1;
        }
        
        // castling part//
        /*else if (Side=='W' && ((Target[0]==7 && Target[1]==2) || (Target[0]==7 && Target[1]==6)))
        {
            return White_check_Castling(list,Target);
        }
        else if (Side=='B' && ((Target[0]==0 && Target[1]==2) || (Target[0]==0 && Target[1]==6)))
        {
            return Black_check_castling(list,Target);
        }*/
    }
    return 0;               
}

