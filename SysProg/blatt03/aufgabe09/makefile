#PRG = Bonusaufgabe
CC = clang
SRC = Bonusaufgabe.c
OBJ = Bonusaufgabe.o
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address


# funktioniert nur richtig mit SRC im Gegensatz zur Vorgabe in makefile-pdf
gen: $(OBJ)
	$(CC) -o $(PRG) $(OBJ) $(SRC) $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
clear:
	rm $(OBJ)