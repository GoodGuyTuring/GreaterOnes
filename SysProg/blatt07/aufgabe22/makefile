#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = test.o mystdlib.o

#Linker-Regel
test: $(OBJ)
	$(CC) $(LDFLAGS) -lm $^ -o $@ 

#Compiler-Regeln
test.o: test.c
	$(CC) $(CFLAGS) $^  -lm -c -o $@ 

mystdlib.o: mystdlib.c
	$(CC) $(CFLAGS) -c -o $@ $^








