#include "CheckWinTest.h"

int KingMoves(CPL *list)
{
//This checks the allowed moves for both kings.
int target_indices[2];
int counter = 0;
//Put this back to 2 after testing
int flag = 1;
char temp[3];

int *king_check = PositionLookUp(list->WhiteKing->currentloc);

list->TargetPiece = list->WhiteKing;

    while(flag)
    {
        for (target_indices[0] = 0; target_indices[0] < 8; target_indices[0]++)
        {
            for(target_indices[1] = 0; target_indices[1] < 8; target_indices[1]++)
            {
                if (target_indices[0] == king_check[0] && target_indices[1] == king_check[1])
                {
                    temp[0] = (char)target_indices[0] + 48;
                    temp[1] = (char)target_indices[1] + 48;

                    if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                }
                else
                {
                    if (IsTherePieceHere(list, target_indices))
                    {
                        ChessLocator(IndicesToPosition(target_indices), list);
                        list->selected_piece = 0;

                        if (strcmp(list->CurrentPiece->type, "King") == 0)
                        {
                                //This would be the Black King
                                printf("Doing this later\n");

                        }
                        else if (strcmp(list->CurrentPiece->type, "Rook") == 0 
                                            && (list->TargetPiece->side != list->CurrentPiece->side))
                        {
                            int x = 0;
                            int y = 0;

                            //Down
                            while((x + target_indices[0]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                            }

                            x = -1;
                            y = 0;

                            //Up
                            while((x + target_indices[0]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                            }

                            x = 0;
                            y = 1;

                            //Right
                            while((y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                y++;
                            }

                            x = 0;
                            y = -1;

                            //Left
                            while((y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                y--;
                            }
                        }
                        else if (strcmp(list->CurrentPiece->type, "Bishop") == 0
                                            && (list->TargetPiece->side != list->CurrentPiece->side))
                        {
                            int x = 0;
                            int y = 0;

                            //Bottom Right Diagonal
                            while((x + target_indices[0]) < 8 && (y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                                y++;
                            }

                            x = -1;
                            y = -1;

                            //Top Left Diagonal
                            while((x + target_indices[0]) >= 0 && (y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                                y--;
                            }

                            x = 1;
                            y = -1;

                            //Bottom Left Diagonal
                            while((x + target_indices[0]) < 8 && (y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                                y--;
                            }

                            x = -1;
                            y = 1;

                            //Top Right Diagonal
                            while((x + target_indices[0]) >= 0 && (y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                                y++;
                            }
                        }
                        else if (strcmp(list->CurrentPiece->type, "Queen") == 0
                                            && (list->TargetPiece->side != list->CurrentPiece->side))
                        {
                            int x = 0;
                            int y = 0;

                            //Down
                            while((x + target_indices[0]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                            }

                            x = -1;
                            y = 0;

                            //Up
                            while((x + target_indices[0]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                            }

                            x = 0;
                            y = 1;

                            //Right
                            while((y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                y++;
                            }

                            x = 0;
                            y = -1;

                            //Left
                            while((y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                y--;
                            }
                            
                            x = 0;
                            y = 0;
                            
                            //Bottom Right Diagonal
                            while((x + target_indices[0]) < 8 && (y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                                y++;
                            }

                            x = -1;
                            y = -1;

                            //Top Left Diagonal
                            while((x + target_indices[0]) >= 0 && (y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                                y--;
                            }

                            x = 1;
                            y = -1;

                            //Bottom Left Diagonal
                            while((x + target_indices[0]) < 8 && (y + target_indices[1]) >= 0)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x++;
                                y--;
                            }

                            x = -1;
                            y = 1;

                            //Top Right Diagonal
                            while((x + target_indices[0]) >= 0 && (y + target_indices[1]) < 8)
                            {
                                if (!IsTherePieceHere(list, target_indices)) break;
                                temp[0] = (char)target_indices[0] + x + 48;
                                temp[1] = (char)target_indices[1] + y + 48;
                                if(AppendKingMoves(list, atol(temp), counter, flag)) counter++;
                                x--;
                                y++;
                            }
                        }
                        else
                        {
                            if (list->TargetPiece->side == list->CurrentPiece->side)
                            {
                                    temp[0] = (char)target_indices[0] + 48;
                                    temp[1] = (char)target_indices[1] + 48;

                                    AppendKingMoves(list, atol(temp), counter, flag);
                                    counter++;                              
                            }
                            else if (LegalMove(list, target_indices, king_check))
                            {

                                    temp[0] = (char)target_indices[0] + 48;
                                    temp[1] = (char)target_indices[1] + 48;

                                    AppendKingMoves(list, atol(temp), counter, flag);
                                    counter++;
                            }
                            else;
                        }
                    }
                }
            }
        }   
        
        ConvertKingMoves(list, counter);
    
        //Switching to the Black King now
        //king_check = PositionLookUp(list->BlackKing->currentloc);
        //list->TargetPiece = list->BlackKing;
        flag--;
    }
    //Just setting these pointers to NULL
    list->CurrentPiece = NULL;
    list->TargetPiece = NULL;
    
    return 0;
}


int intlen(int x) {
    if (x >= 10) return 2;
    return 1;
}

int AppendKingMoves(CPL *list, int num, int counter, int flag)
{
    for (int x = 0; x < counter; x++)
    {
        //Change this back to 2 after testing
        if (flag == 1)
        {
            if (list->WKingMoves[x] == num) 
                {
                    return 0;
                }
        }
        else
        {
            if (list->BKingMoves[x] == num) return 0;
        }   
    }
    //Change this back to 2 after testing
    if (flag == 1) list->WKingMoves[counter] = num;
    else list->BKingMoves[counter] = num;
    
    return 1;
}

int ConvertKingMoves(CPL *list, int counter)
{
    int indices[2];
    
    for (int i = 0; i < counter; i++)
    {
            if (intlen(list->WKingMoves[i]) == 1)
            {
                    indices[0] = 0;
                    indices[1] = list->WKingMoves[i];
            }
            else
            {
                    indices[1] = list->WKingMoves[i] % 10;
                    list->WKingMoves[i] /= 10;
                    indices[0] = list->WKingMoves[i];
            }

            char *position = IndicesToPosition(indices);
            printf("Board Position: %s\n", position);
    }
    return 0;
}
