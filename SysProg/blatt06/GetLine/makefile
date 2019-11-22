#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
HEADER = mystddef.h myunistd.h mystdlib.h
LIB = library.a 
OBJ = test.o mygetline.o

test: $(OBJ) $(LIB)
	$(CC) $(LDFLAGS) $^ -o $@ 

test.o: test.c 
	$(CC) $(CFLAGS) -c -o $@ $^

mygetline.o: mygetline.c 
	$(CC) $(CFLAGS) $^ -c -o $@ 






