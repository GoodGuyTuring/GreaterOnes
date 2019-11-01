CC = clang
SRC = main.c mystring.c
OBJ = main.o mystring.o
HEA = mystring.h mystddef.h
CFLAGS = -g -Wall -fsanitize=address
LDFLAGS = -g -Wall -fsanitize=address


# funktioniert nur richtig mit SRC im Gegensatz zur Vorgabe in makefile-pdf
prog: $(OBJ)
	$(CC) -o prog $(OBj) $(SRC) $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.h : %.c
	$(CC) -c $<