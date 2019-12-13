#Parameter für Compiler, Flags, etc.
CC=clang
CFLAGS = -g -Wall
LDFLAGS = -g -Wall
OBJ = bogo-merge-thread.o

#Linker-Regel
bogo-merge-thread: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ -lm -lpthread

#Compiler-Regeln
bogo-merge-thread.o: bogo-merge-thread.c
	$(CC) $(CFLAGS) $^ -c -o $@ 








