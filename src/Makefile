#Makefile - Chess

#Variable Definitions
CC = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -Wall -ansi -std=c99 -g

all: ChessGame
test: ChessGame
tar: tar

clean:
	rm -f GameMenu.o
	rm -f GameBoardV2.o
	rm -f ChessPieceTypes.o
	rm -f ChessPieceHierarchy.o
	rm -f libfilter.a
	rm -f ChessGame
	rm -f CheckWinTest.o
	rm -f GameBoardV3.o

#Dependencies

tar: bin doc src INSTALL.txt README.txt Copyright.txt
	gtar cvzf Chess_Alpha_src.tar.gz bin doc src INSTALL.txt README.txt Copyright.txt

ChessGame: ChessPieceHierarchy.o libfilter.a
	$(CC) $(CFLAGS) ChessPieceHierarchy.o -L. -lfilter -o ChessGame

CheckWinTest.o: CheckWinTest.c CheckWinTest.h ChessPieceTypes.h GameBoardV2.h
		$(CC) $(CFLAGS) -c CheckWinTest.c -o CheckWinTest.o
GameMenu.o: GameMenu.h GameMenu.c ChessPieceHierarchy.h GameBoardV2.h
	$(CC) $(CFLAGS) -c GameMenu.c -o GameMenu.o
GameBoardV3.o: GameBoardV2.h GameBoardV3.c CheckWinTest.h ChessPieceTypes.h ChessPieceHierarchy.h
	$(CC) $(CFLAGS) -c GameBoardV3.c -o GameBoardV3.o
ChessPieceTypes.o: ChessPieceTypes.c ChessPieceTypes.h ChessPieceHierarchy.h
	$(CC) $(CFLAGS) -c ChessPieceTypes.c -o ChessPieceTypes.o
ChessPieceHierarchy.o: ChessPieceHierarchy.c ChessPieceHierarchy.h
	$(CC) $(CFLAGS) -c ChessPieceHierarchy.c -o ChessPieceHierarchy.o
libfilter.a: GameMenu.o GameBoardV3.o ChessPieceTypes.o CheckWinTest.o
	ar rc libfilter.a GameMenu.o GameBoardV3.o ChessPieceTypes.o CheckWinTest.o
	ranlib libfilter.a
