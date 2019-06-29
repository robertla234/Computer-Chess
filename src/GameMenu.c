#include "GameMenu.h"

int main()
{
	while(1)
	{
		puts("\t\t        .-') _                                                       ('-.                               ");
		puts("\t\t       ( OO ) )                                                    _(  OO)                              ");
		puts("\t\t   ,--./ ,--,'  .-'),-----.          .-----. ,--.     ,--. ,--.   (,------.                             ");
		puts("\t\t   |   \\ |  |\\ \\( OO' .-.  '        '  .--./ |  |.-'\\) |  | |  |    |  .---'                        ");
		puts("\t\t   |    \\|  | )/   |  | |  |        |  |('-. |  | OO )|  | | .-')  |  |                                ");
		puts("\t\t   |  .     |/ \\_) |  |\\|  |       /_) |OO  )|  |`-' ||  |_|( OO )(|  '--.                            ");
		puts("\t\t   |  |\\    |    \\ |  | |  |       ||  |`-'|(|  '---.'|  | | `-' / |  .--'                            ");
		puts("\t\t   |  | \\   |     `'  '-'  '      (_'  '--'\\ |      |('  '-'(_.-'  |  `---.                           ");
		puts("\t\t   `--'  `--'       `-----'          `-----' `------'  `-----'     `------'                             ");
		puts("\t           _  .-')     ('-.    (`\\ .-') /`                  ('-. .-.   ('-.    .-')     .-')             ");
		puts("\t          ( \\( -O )  _(  OO)    `.( OO ),'                 ( OO )  / _(  OO)  ( OO ).  ( OO ).           ");
		puts("\t   .-----. ,------. (,------.,--./  .--.           .-----. ,--. ,--.(,------.(_)---\\_)(_)---\\_)         ");
		puts("\t  '  .--./ |   /`. ' |  .---'|      |  |          '  .--./ |  | |  | |  .---'/    _ | /    _ |            ");
		puts("\t  |  |('-. |  /  | | |  |    |  |   |  |,         |  |('-. |   .|  | |  |    \\  :` `. \\  :` `.          ");
		puts("\t /_) |OO  )|  |_.' |(|  '--. |  |.'.|  |_)       /_) |OO  )|       |(|  '--.  '..`''.) '..`''.)           ");
		puts("\t ||  |`-'| |  .  '.' |  .--' |         |         ||  |`-'| |  .-.  | |  .--' .-._)   \\.-._)   \\         ");
		puts("\t(_'  '--'\\ |  |\\  \\  |  `---.|   ,'.   |        (_'  '--'\\ |  | |  | |  `---.\\       /\\       /     ");
		puts("\t   `-----' `--' '--' `------''--'   '--'           `-----' `--' `--' `------' `-----'  `-----'            ");
		
		printf("\n");
		
		char side;
		int interactiveboard;
		int options;
		char restart;
		
		while(1)
		{
			printf("Please choose an option below: \n");
			printf("(1) - Player vs Player \n");
			printf("(2) - Player vs CPU \n");
			printf("(3) - Exit\n");
			scanf(" %d", &options);
			
			if (options == 1 || options == 2) break;
            else if (options == 3)exit(0);

			printf("Invalid Input. Please Try Again!\n");
		}

		while(1)
		{
			printf("Choose a Side (W or B): ");
			scanf(" %c", &side);
			
			if (side == 'B' || side =='W') break;
			printf("That's not an allowed side!\n");
		}

		while(1)
		{
			printf("Interactive Board? (1 for Yes, 0 for No)\n");
			scanf(" %d", &interactiveboard);
			
			if (interactiveboard == 0 || interactiveboard == 1) break;
			printf("That's not an allowed option!\n");
		}
		
		CPL *list = StartUp(side, interactiveboard);
		
		char CurrentLocation[3];
		char TargetLocation[3]; 
		
		while(1)
		{
			while(1)
			{
				if (list->turn == 'W') printf("It's Whites Turn!\n");
				if (list->turn == 'B') printf("It's Blacks Turn!\n");
				
				printf("To select a piece, enter its board position.\n");
				printf("To move a piece to a spot on the board, enter its board position.\n");
				printf("Select Piece (Board Position): ");
				scanf(" %s", CurrentLocation);
				CurrentLocation[2] = '\0';
				
				printf("\n");
				
				printf("Move Piece To (Board Position): ");
				scanf(" %s", TargetLocation);
				TargetLocation[2] = '\0';
				
				printf("\n");
				
				if (CurrentLocation[0] >=65 && CurrentLocation[0] <= 72)
					if (CurrentLocation[1] >=49 && CurrentLocation[1] <= 57)
						if (TargetLocation[0] >=65 && TargetLocation[0] <= 72)
							if (TargetLocation[1] >=49 && TargetLocation[1] <= 57)
								break;
							
				printf("The given board positions are not valid!");
			}

			if (HandleMoves(list, CurrentLocation, TargetLocation))
			{
				printf("%s to %s was successful!\n", CurrentLocation, TargetLocation);

				/*Check for checkmate*/
				
				//If in checkmate, break out of the loop
				
				//If not in checkmate, switching turns
				if (list->turn == 'B') list->turn = 'W';
				else list->turn = 'B';

                //Now we update the board
                update_board(list);
			}
			else
			{
				printf("%s to %s was not successful!\n", CurrentLocation, TargetLocation);
				update_board(list);
			}
		}	
		
		if (list->turn == 'W') printf("Congrats, White Wins!\n");
		if (list->turn == 'B') printf("Congrats, Black Wins!\n");
		
		printf("Play again? (Y or N): ");
		scanf(" %c", &restart);
		
		if (restart == 'N') break;
	}
return 1;
}
