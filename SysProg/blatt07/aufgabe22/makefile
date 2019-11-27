#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = test.o myunistd.o

#Linker-Regel
test: $(OBJ) 
	$(CC) $(LDFLAGS) $^ -o $@ 

#Compiler-Regeln
test.o: test.c
	$(CC) $(CFLAGS) $^ -c -o $@








