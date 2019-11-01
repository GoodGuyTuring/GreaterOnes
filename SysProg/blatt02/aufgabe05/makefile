PRG = springerproblem
CC = clang
SRC = springerproblem.c chessboard.c
OBJ = springerproblem.o chessboard.o
HEA = chessboard.h 
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address


# funktioniert nur richtig mit SRC im Gegensatz zur Vorgabe in makefile-pdf
$(PRG): $(OBJ)
	$(CC) -o $(PRG) $(OBJ) $(SRC) $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.h : %.c
	$(CC) -c 
	
clear:
	rm $(OBJ)
